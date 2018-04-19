// MainFrm.cpp : Implementierung der Klasse CMainFrame
//

#include "stdafx.h"
#include "simulator3.h"
#include "MainFrm.h"
#include "Comport.h"
#include "settings.h"
#include "Simulator3Doc.h"
#include "Simulator3View.h"
#include "Ascii.h"
#include "About.h"
#include "MyView.h"
#include "Protocol.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_SETTINGS, OnSettings)
	ON_COMMAND(ID_VIEW_ASCIITABLE, OnViewAsciitable)
	ON_COMMAND(ID_ABOUT_APLICATIONINFO, OnAboutAplicationinfo)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ASCII, OnUpdateViewAscii)
	ON_UPDATE_COMMAND_UI(ID_VIEW_HEXA, OnUpdateViewHexa)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DECIMAL, OnUpdateViewDecimal)
	ON_COMMAND(ID_VIEW_ASCII, OnViewAscii)
	ON_COMMAND(ID_VIEW_HEXA, OnViewHexa)
	ON_COMMAND(ID_VIEW_DECIMAL, OnViewDecimal)
	ON_COMMAND(ID_DECIMAL, OnDecimal)
	ON_COMMAND(ID_ASCII, OnAscii)
	ON_COMMAND(ID_HEXA, OnHexa)
	ON_UPDATE_COMMAND_UI(ID_ASCII, OnUpdateAscii)
	ON_UPDATE_COMMAND_UI(ID_DECIMAL, OnUpdateDecimal)
	ON_UPDATE_COMMAND_UI(ID_HEXA, OnUpdateHexa)
	ON_COMMAND(ID_SETTINGS_PROTOCOL, OnSettingsProtocol)
	ON_COMMAND(ID_SEND_MACRO1, OnSendMacro1)
	ON_COMMAND(ID_SEND_MACRO10, OnSendMacro10)
	ON_COMMAND(ID_SEND_MACRO2, OnSendMacro2)
	ON_COMMAND(ID_SEND_MACRO3, OnSendMacro3)
	ON_COMMAND(ID_SEND_MACRO4, OnSendMacro4)
	ON_COMMAND(ID_SEND_MACRO5, OnSendMacro5)
	ON_COMMAND(ID_SEND_MACRO6, OnSendMacro6)
	ON_COMMAND(ID_SEND_MACRO7, OnSendMacro7)
	ON_COMMAND(ID_SEND_MACRO8, OnSendMacro8)
	ON_COMMAND(ID_SEND_MACRO9, OnSendMacro9)
	ON_UPDATE_COMMAND_UI(ID_SEND_MACRO1, OnUpdateSendMacro1)
	ON_UPDATE_COMMAND_UI(ID_SEND_MACRO10, OnUpdateSendMacro10)
	ON_UPDATE_COMMAND_UI(ID_SEND_MACRO2, OnUpdateSendMacro2)
	ON_UPDATE_COMMAND_UI(ID_SEND_MACRO3, OnUpdateSendMacro3)
	ON_UPDATE_COMMAND_UI(ID_SEND_MACRO4, OnUpdateSendMacro4)
	ON_UPDATE_COMMAND_UI(ID_SEND_MACRO5, OnUpdateSendMacro5)
	ON_UPDATE_COMMAND_UI(ID_SEND_MACRO6, OnUpdateSendMacro6)
	ON_UPDATE_COMMAND_UI(ID_SEND_MACRO7, OnUpdateSendMacro7)
	ON_UPDATE_COMMAND_UI(ID_SEND_MACRO8, OnUpdateSendMacro8)
	ON_UPDATE_COMMAND_UI(ID_SEND_MACRO9, OnUpdateSendMacro9)
	ON_UPDATE_COMMAND_UI(ID_SEND_SENDHEXFILE, OnUpdateSendSendhexfile)
	ON_COMMAND(ID_SEND_SENDHEXFILE, OnSendSendhexfile)
	//}}AFX_MSG_MAP
ON_WM_MENUSELECT( )
	ON_MESSAGE(ID_IO_REC_EVENT, OnRecIoEvent)
	ON_MESSAGE(ID_IO_SND_EVENT, OnSndIoEvent)

  	
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,       
	ID_SEPARATOR,       
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame Konstruktion/Zerstörung

CMainFrame::CMainFrame()
{
	m_bDecimal=false;
	m_bHexa=false;
	m_bASCII=true;
	theApp.Receive_to_screen=false;
	theApp.Send_to_screen=false;
    theApp.bSendCR=true;
	theApp.csTimeStamp=__TIMESTAMP__;
}

CMainFrame::~CMainFrame()
{
  if (m_CheckBitmap.m_hObject)		m_CheckBitmap.DeleteObject();
  if (m_UnCheckBitmap.m_hObject)	m_UnCheckBitmap.DeleteObject();
}

void CMainFrame::UpdateStatusBar(CString data)
{
	 m_wndStatusBar.SetPaneText(1,data);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CString csStatus;
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this) ||!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Toolbar creating error.\n");
		return -1;      
	}
	else
	{
	}

	if (!m_wndStatusBar.Create(this) ||!m_wndStatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT)))
		{
			TRACE0("Statusbar creating error.\n");
			return -1;
		}
	else
		{
			m_wndStatusBar.SetPaneInfo(0,0,0,300);		
		}
	
		theApp.OpenPort=false;
		m_wndStatusBar.SetPaneText(1,"No port opened.");

		char * pcBuffer= new char[100];
		CString csCheck;

		GetCurrentDirectory(100,pcBuffer);
		theApp.csDefaultIniFilePath.Format("%s",pcBuffer);
		theApp.csDefaultIniFilePath.Insert(theApp.csDefaultIniFilePath.GetLength(),"\\Serial.ini");

		CFile myFile;
		CFileException theException;

		if(!myFile.Open(theApp.csDefaultIniFilePath,CFile::modeRead,&theException))
		{
		  //File not found exception
		  if(theException.m_cause == CFileException::fileNotFound)
		  MessageBox("Configuration file not found.",theApp.csDefaultIniFilePath,0);
		  //File access denied exception
		  if(theException.m_cause == CFileException::accessDenied) 
		  MessageBox("Configuration file acessDenied.",theApp.csDefaultIniFilePath,0);

		  CFileDialog Fdlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"Ini Files (*.ini)|*.ini|All Files (*.*)|*.*||",NULL);
		  static char szTitle[] = _T ("Select configuration file to load");
		  Fdlg.m_ofn.lpstrTitle = szTitle;

		  if(Fdlg.DoModal()==IDOK)
		  {
			vLoadConfig(Fdlg.GetPathName());
			theApp.csDefaultIniFilePath=Fdlg.GetPathName();
		  }
		}
		else
		{ 
		  //File open successfull
		  myFile.Close();
		  //try to load configuration file else use default values
  	      vLoadConfig(theApp.csDefaultIniFilePath);
		}
	
	 //IF not open port
	 if(!theApp.ComPort.OpenPort())
	 {
		theApp.OpenPort=false;
		csStatus.Empty();
		csStatus.Insert(csStatus.GetLength(),theApp.ComPort.GetComPort()+" open error.");
		m_wndStatusBar.SetPaneText(1,csStatus);
	 }
	 // Start COM threads, openport,Starttimer for application purposes
	 else
	 {
		theApp.OpenPort=true;
		theApp.ComPort.yStartIO(this->m_hWnd);
		//SetTimer(1,1000,NULL);
		csStatus.Insert(0,theApp.ComPort.GetComPort()+" ");
	    csStatus.Insert(csStatus.GetLength(),theApp.ComPort.GetCOMDataB()+" ");
	    csStatus.Insert(csStatus.GetLength(),theApp.ComPort.GetCOMStopB()+" ");
        csStatus.Insert(csStatus.GetLength(),theApp.ComPort.GetCOMParity()+" ");
	    csStatus.Insert(csStatus.GetLength(),theApp.ComPort.GetCOMSpeed());
		m_wndStatusBar.SetPaneText(1,csStatus);
	 }
//		CString buff;
//		buff.Format("%02d:%02d",theApp.iMinuty,theApp.iSekundy);
//		m_wndStatusBar.SetPaneText(3,buff);
		
		// Load bitmaps from resource. Both m_CheckBitmap and m_UnCheckBitmap
		// are member variables of CMainFrame class of type CBitmap.
		m_CheckBitmap.LoadBitmap(IDB_CHECKED);
		m_UnCheckBitmap.LoadBitmap(IDB_UNCHECKED);
		m_OpenBitmap.LoadBitmap(IDB_OPEN);
		m_NewBitmap.LoadBitmap(IDB_NEW);
		m_CountersBitmap.LoadBitmap(IDB_ASCII);
		m_DebugBitmap.LoadBitmap(IDB_COM);

		// Associate bitmaps...
		CMenu* mmenu = GetMenu();
		CMenu* submenu = mmenu->GetSubMenu(4);

		submenu->SetMenuItemBitmaps(ID_VIEW_DECIMAL, MF_BYCOMMAND,&m_UnCheckBitmap, &m_CheckBitmap);
		submenu->SetMenuItemBitmaps(ID_VIEW_HEXA, MF_BYCOMMAND,&m_UnCheckBitmap, &m_CheckBitmap);
		submenu->SetMenuItemBitmaps(ID_VIEW_ASCII, MF_BYCOMMAND,&m_UnCheckBitmap, &m_CheckBitmap);
		submenu->SetMenuItemBitmaps(ID_VIEW_TOOLBAR, MF_BYCOMMAND,&m_UnCheckBitmap, &m_CheckBitmap);
		submenu->SetMenuItemBitmaps(ID_VIEW_STATUS_BAR, MF_BYCOMMAND,&m_UnCheckBitmap, &m_CheckBitmap);
		submenu->SetMenuItemBitmaps(ID_WINDOW_SPLIT, MF_BYCOMMAND,&m_UnCheckBitmap, &m_CheckBitmap);
		submenu->SetMenuItemBitmaps(ID_VIEW_ASCIITABLE, MF_BYCOMMAND,&m_CountersBitmap, &m_CountersBitmap);

		submenu=mmenu->GetSubMenu(2);
		submenu->SetMenuItemBitmaps(ID_SETTINGS, MF_BYCOMMAND,&m_DebugBitmap, &m_DebugBitmap);
		
		submenu=mmenu->GetSubMenu(0);
		submenu->SetMenuItemBitmaps(ID_FILE_OPEN, MF_BYCOMMAND,&m_OpenBitmap, &m_OpenBitmap);
		submenu->SetMenuItemBitmaps(ID_FILE_NEW, MF_BYCOMMAND,&m_NewBitmap, &m_NewBitmap);

		CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;	
		return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.x=0;
	cs.y=100;
	cs.x=300;
	cs.y=300;
	if(!CFrameWnd::PreCreateWindow(cs))
	return FALSE;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame Diagnose

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame Nachrichten-Handler

void CMainFrame::OnDestroy() 
{
    vSaveConfig(theApp.csDefaultIniFilePath);
	CFrameWnd::OnDestroy();
	theApp.ComPort.vEndIO();
	theApp.ComPort.ClosePort();
}

void CMainFrame::OnSettings() 
{
  Csettings dlgSettings;
  dlgSettings.DoModal();
}

LRESULT CMainFrame::OnRecIoEvent(WPARAM wParam, LPARAM lParam)
{
	// Poslat do horneho okna splittera
	CEditView* pView = (CEditView*)m_wndSplitter.GetPane(0, 0);
		//prevod z 0..255 a postupne posle cislice
		//ako desiatkove...
		if (m_bDecimal)
		{
			unsigned char pom=0;
				pView->SendMessage(WM_CHAR,wParam/100+48,1);
				pom=wParam%100;
				pView->SendMessage(WM_CHAR,pom/10+48,1);
				pom=pom%10;
				pView->SendMessage(WM_CHAR,pom+48,1);
				pView->SendMessage(WM_CHAR,' ',1);

		}
		//prevod z 0..255 a postupne posle cislice
		//ako hexa...
		if (m_bHexa)
		{
			unsigned char pom=0;
				switch (wParam/16)
				{
					case 0:
					case 1:
					case 2:
					case 3:
					case 4:
					case 5:
					case 6:
					case 7:
					case 8:
					case 9:
						pView->SendMessage(WM_CHAR,wParam/16+48,1);
					break;
					case 10:
						pView->SendMessage(WM_CHAR,'A',1);
					break;
					case 11:
						pView->SendMessage(WM_CHAR,'B',1);
					break;
					case 12:
						pView->SendMessage(WM_CHAR,'C',1);
					break;
					case 13:
						pView->SendMessage(WM_CHAR,'D',1);
					break;
					case 14:
						pView->SendMessage(WM_CHAR,'E',1);
					break;
					case 15:
						pView->SendMessage(WM_CHAR,'F',1);
					break;
				}
				pom=wParam%16;
				switch (pom)
				{
					case 0:
					case 1:
					case 2:
					case 3:
					case 4:
					case 5:
					case 6:
					case 7:
					case 8:
					case 9:
						pView->SendMessage(WM_CHAR,pom+48,1);
					break;
					case 10:
						pView->SendMessage(WM_CHAR,'A',1);
					break;
					case 11:
						pView->SendMessage(WM_CHAR,'B',1);
					break;
					case 12:
						pView->SendMessage(WM_CHAR,'C',1);
					break;
					case 13:
						pView->SendMessage(WM_CHAR,'D',1);
					break;
					case 14:
						pView->SendMessage(WM_CHAR,'E',1);
					break;
					case 15:
						pView->SendMessage(WM_CHAR,'F',1);
					break;
				}
				pView->SendMessage(WM_CHAR,' ',1);


		}
		//len posle znak
		//ak je len riadiaci <32 tak vypise v zatvorkach nazov znaku
		if (m_bASCII)
		{
			if(wParam<32)
			{
				//if ((wParam!='\n') && (wParam!='\r'))
				if (wParam!='\n')
				{
					pView->SendMessage(WM_CHAR,'<',1);
					for(int i=0;i<theApp.m_sPoleMien[wParam].GetLength();i++)
						pView->SendMessage(WM_CHAR,theApp.m_sPoleMien[wParam][i],1);
					pView->SendMessage(WM_CHAR,'>',1);
				}
				else
					pView->SendMessage(WM_CHAR,wParam,1);
			}
			else
				pView->SendMessage(WM_CHAR,wParam,1);
		}
		return 0;
}

LRESULT CMainFrame::OnSndIoEvent(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

void CMainFrame::OnViewStatusBar() 
{
    m_wndStatusBar.ShowWindow((m_wndStatusBar.GetStyle() & WS_VISIBLE) == 0);
    RecalcLayout();
}

void CMainFrame::OnViewAsciitable() 
{
	Ascii dlgAscii;
	dlgAscii.DoModal();
}

void CMainFrame::OnAboutAplicationinfo() 
{
	CAbout dlgAbout;
	dlgAbout.DoModal();
}

void CMainFrame::OnUpdateViewAscii(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bASCII);			
}

void CMainFrame::OnUpdateViewHexa(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bHexa);			
}

void CMainFrame::OnUpdateViewDecimal(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_bDecimal);			
}

void CMainFrame::OnViewAscii() 
{
	if(!m_bASCII)
	{ 
		m_bASCII=true;
		m_bHexa=false;
		m_bDecimal=false;
	}
}

void CMainFrame::OnViewHexa() 
{
	if(!m_bHexa)
	{   
		m_bASCII=false;
		m_bHexa=true;
		m_bDecimal=false;
	}
}

void CMainFrame::OnViewDecimal() 
{
	if(!m_bDecimal)
	{
		m_bASCII=false;
		m_bHexa=false;
		m_bDecimal=true;
	}
		
}

void CMainFrame::OnDecimal() 
{
	if(!m_bDecimal)
	{
		m_bASCII=false;
		m_bHexa=false;
		m_bDecimal=true;
	}
	
}

void CMainFrame::OnAscii() 
{
	if(!m_bASCII)
	{ 
		m_bASCII=true;
		m_bHexa=false;
		m_bDecimal=false;
	}
	
}

void CMainFrame::OnHexa() 
{
	if(!m_bHexa)
	{   
		m_bASCII=false;
		m_bHexa=true;
		m_bDecimal=false;
	}
}

void CMainFrame::OnUpdateAscii(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_bASCII);				
}

void CMainFrame::OnUpdateDecimal(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_bDecimal);				
}

void CMainFrame::OnUpdateHexa(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_bHexa);					
}

void CMainFrame::OnSettingsProtocol() 
{
	CProtocol dlgProtocol;
	dlgProtocol.DoModal();
}

void CMainFrame::OnSendMacro1() 
{
	vSendMacro(0);
}

void CMainFrame::OnSendMacro10() 
{
	vSendMacro(9);
}

void CMainFrame::OnSendMacro2() 
{
	vSendMacro(1);
}

void CMainFrame::OnSendMacro3() 
{
	vSendMacro(2);
}

void CMainFrame::OnSendMacro4() 
{
	vSendMacro(3);
}

void CMainFrame::OnSendMacro5() 
{
	vSendMacro(4);
}

void CMainFrame::OnSendMacro6() 
{
	vSendMacro(5);
}

void CMainFrame::OnSendMacro7() 
{
	vSendMacro(6);
}

void CMainFrame::OnSendMacro8() 
{
	vSendMacro(7);
}

void CMainFrame::OnSendMacro9() 
{
	vSendMacro(8);
}

void CMainFrame::OnUpdateSendMacro1(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(theApp.OpenPort);
}

void CMainFrame::OnUpdateSendMacro10(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(theApp.OpenPort);
}

void CMainFrame::OnUpdateSendMacro2(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(theApp.OpenPort);	
}

void CMainFrame::OnUpdateSendMacro3(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(theApp.OpenPort);	
}

void CMainFrame::OnUpdateSendMacro4(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(theApp.OpenPort);	
}

void CMainFrame::OnUpdateSendMacro5(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(theApp.OpenPort);	
}

void CMainFrame::OnUpdateSendMacro6(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(theApp.OpenPort);	
}

void CMainFrame::OnUpdateSendMacro7(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(theApp.OpenPort);	
}

void CMainFrame::OnUpdateSendMacro8(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(theApp.OpenPort);	
}

void CMainFrame::OnUpdateSendMacro9(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(theApp.OpenPort);	
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	VERIFY(m_wndSplitter.CreateStatic(this, 2, 1));
    VERIFY(m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CSimulator3View),CSize(100, 250), pContext));
    VERIFY(m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CMyView),CSize(100, 50), pContext));
	return TRUE;
}

void CMainFrame::OnUpdateSendSendhexfile(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(theApp.OpenPort);	
}

void CMainFrame::OnSendSendhexfile() 
{
	CFileDialog Fdlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"All Files (*.*)|*.*||",NULL);
	
	if(Fdlg.DoModal()==IDOK)
		{
			if(MessageBox(Fdlg.GetPathName(),"File to download:",MB_OKCANCEL)==IDOK)
				{
					CFile myFile(Fdlg.GetPathName(),CFile::modeReadWrite);
					myFile.Seek(0,CFile::begin);
					
					char * buffer = new char[myFile.GetLength()];

					unsigned int pocet=myFile.Read(buffer,myFile.GetLength());
					if(pocet==myFile.GetLength())
					{
						CEditView* pView =(CEditView*) ((CFrameWnd*) AfxGetMainWnd ())->GetActiveView();

						if(GetActiveView()->IsKindOf(RUNTIME_CLASS(CSimulator3View)))
							{
								SetActiveView((CView*)m_wndSplitter.GetPane(1,0));
								pView=(CEditView*) ((CFrameWnd*) AfxGetMainWnd ())->GetActiveView();
							}

						for(unsigned int i=0;i<myFile.GetLength();i++)
							{
								theApp.Send_to_screen=false;
								pView->SendMessage(WM_CHAR,buffer[i],1);
							}
					}
					else
						MessageBox("File read error.","Error",MB_OK);

					myFile.Close();
				}
			
		}
}

/////////////////////////////////////////////////////////////////////////////
// Save configuration 	 											       //
/////////////////////////////////////////////////////////////////////////////
void CMainFrame::vSaveConfig(CString csIniFile)
{
	CString buffer;
	buffer.Empty();
	//PORT
	buffer.Insert(0,theApp.ComPort.GetComPort());
	WritePrivateProfileString("PORT","Comport",buffer,csIniFile);
	buffer.Empty();
	buffer.Insert(0,theApp.ComPort.GetCOMDataB());
	WritePrivateProfileString("PORT","Databytes",buffer,csIniFile);
	buffer.Empty();
	buffer.Insert(0,theApp.ComPort.GetCOMParity());
	WritePrivateProfileString("PORT","Parity",buffer,csIniFile);
	buffer.Empty();
	buffer.Insert(0,theApp.ComPort.GetCOMSpeed());
	WritePrivateProfileString("PORT","Speed",buffer,csIniFile);
	buffer.Empty();
	buffer.Insert(0,theApp.ComPort.GetCOMStopB());
	WritePrivateProfileString("PORT","Stopbit",buffer,csIniFile);
	//APPLICATION

	//MACROS
	for (int i = 0; i < theApp.Macros.GetCount(); i++)
	{
		buffer = theApp.Macros[i];
		CString index;
		index.Format("%d",i+1);
		WritePrivateProfileString("MACROS", index.GetBuffer(), buffer, csIniFile);
	}
}
/////////////////////////////////////////////////////////////////////////////
// Load configuration 	 											       //
/////////////////////////////////////////////////////////////////////////////
void CMainFrame::vLoadConfig(CString csIniFile)
{
	const int BUF_SIZE = 100;
	char buffer[BUF_SIZE];
	//APPLICATION
	//COMPORT
	GetPrivateProfileString("PORT","Comport","COM1",buffer,5,csIniFile);
	theApp.ComPort.SetCOMPort(buffer);
	GetPrivateProfileString("PORT","Databytes","8",buffer,3,csIniFile);
	theApp.ComPort.SetCOMDataB(atoi(buffer));
	//GetPrivateProfileString("PORT", "Parity", buffer,3,csIniFile);
	//theApp.ComPort.SetCOMParity()
	//buffer.Empty();
	//buffer.Insert(0, theApp.ComPort.GetCOMSpeed());
	GetPrivateProfileString("PORT", "Speed", "9600", buffer, 7, csIniFile);
	theApp.ComPort.SetCOMSpeed(atoi(buffer));
	//buffer.Empty();
	//buffer.Insert(0, theApp.ComPort.GetCOMStopB());
	//WritePrivateProfileString("PORT", "Stopbit", buffer, csIniFile);
	
	theApp.Macros.SetSize(10);

	for (int i = 0; i < theApp.Macros.GetCount(); i++)
	{
		CString index;
		index.Format("%d", i + 1);
		GetPrivateProfileString("MACROS", index.GetBuffer(), index.GetBuffer(), buffer, BUF_SIZE, csIniFile);
		theApp.Macros[i] = buffer;
	}
}

BOOL CMainFrame::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CMainFrame::vSendMacro(int iMacro) 
{
	CEditView* pView = (CEditView*)m_wndSplitter.GetPane(0, 0);

	if (iMacro < theApp.Macros.GetCount())
	{
		for (int i = 0; i<theApp.Macros[iMacro].GetLength(); i++)
			pView->SendMessage(WM_CHAR, theApp.Macros[iMacro][i], 1);
		if (theApp.bSendCR)
		{
			pView->SendMessage(WM_CHAR, 13, 1);
			pView->SendMessage(WM_CHAR, 10, 1);
		}
	}
}
