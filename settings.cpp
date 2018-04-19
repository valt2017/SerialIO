// settings.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "simulator3.h"
#include "settings.h"
#include "comport.h"
#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Csettings 


Csettings::Csettings(CWnd* pParent /*=NULL*/)
	: CDialog(Csettings::IDD, pParent)
{
	//{{AFX_DATA_INIT(Csettings)
	m_Databits = 3;
	m_Stopbits = 0;
	m_Parity = 0;
	m_HWhandshake = 0;
	m_SWhandshake = 0;
	m_Stavportu = _T("");
	m_Baudrate = 3;
	//}}AFX_DATA_INIT
}


void Csettings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Csettings)
	DDX_Control(pDX, IDOK2, m_Closeport);
	DDX_Control(pDX, IDOK, m_Set);
	DDX_Radio(pDX, IDC_RADIO5, m_Databits);
	DDX_Radio(pDX, IDC_RADIO9, m_Stopbits);
	DDX_Radio(pDX, IDC_RADIO12, m_Parity);
	DDX_Radio(pDX, IDC_RADIO17, m_HWhandshake);
	DDX_Radio(pDX, IDC_RADIO19, m_SWhandshake);
	DDX_Text(pDX, IDC_EDIT1, m_Stavportu);
	DDX_CBIndex(pDX, IDC_COMBO1, m_Baudrate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Csettings, CDialog)
	//{{AFX_MSG_MAP(Csettings)
	ON_BN_CLICKED(IDOK2, OnOk2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten Csettings 

BOOL Csettings::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	return CDialog::Create(IDD, pParentWnd);
}

void Csettings::OnOK() 
{

	CString csPortToOpen;
	
	theApp.ComPort.ClosePort();
	theApp.ComPort.vEndIO();

	UpdateData(TRUE);
	m_Stavportu.Empty();

	CListBox * pLB = (CListBox*) GetDlgItem(IDC_LIST1);

	if(theApp.OpenPort==true)
	{
		theApp.ComPort.vEndIO();
		theApp.ComPort.ClosePort();
		theApp.OpenPort=false;
	}

	
	//Choose the new port to open
	pLB->GetText(pLB->GetCurSel(),csPortToOpen);
	theApp.ComPort.SetCOMPort(csPortToOpen);

	 m_Stavportu.Insert(0,theApp.ComPort.GetComPort()+" ");
	 theApp.ComPort.SetCOMDataB(m_Databits+5);
	 m_Stavportu.Insert(m_Stavportu.GetLength(),theApp.ComPort.GetCOMDataB()+" ");
	 theApp.ComPort.SetCOMStopB(StopBitsTable[m_Stopbits]);
     m_Stavportu.Insert(m_Stavportu.GetLength(),theApp.ComPort.GetCOMStopB()+" ");
     theApp.ComPort.SetCOMParity(ParityTable[m_Parity]);
	 m_Stavportu.Insert(m_Stavportu.GetLength(),theApp.ComPort.GetCOMParity()+" ");
	 theApp.ComPort.SetCOMSpeed(BaudTable[m_Baudrate]);
     m_Stavportu.Insert(m_Stavportu.GetLength(),theApp.ComPort.GetCOMSpeed());

	 switch(m_SWhandshake)
	 {
		case 0:
		  theApp.ComPort.SetCOMOutX(FALSE);
		  theApp.ComPort.SetCOMInX(FALSE);
  		break;
		case 1:
		  theApp.ComPort.SetCOMOutX(TRUE);
		  theApp.ComPort.SetCOMInX(TRUE);
		  m_Stavportu.Insert(m_Stavportu.GetLength()," SW");
		break;
	 }

	 switch(m_HWhandshake)
	 {
		case 0:
		  theApp.ComPort.SetCOMDTR(DTR_CONTROL_DISABLE);
		  theApp.ComPort.SetCOMRTS(RTS_CONTROL_DISABLE);
		break;
		case 1:
		  theApp.ComPort.SetCOMDTR(DTR_CONTROL_HANDSHAKE);
		  theApp.ComPort.SetCOMRTS(RTS_CONTROL_HANDSHAKE);
		  m_Stavportu.Insert(m_Stavportu.GetLength()," HW");
		break;
	 }

	 CString str;
	 CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;	
	 CStatusBar* pStatus = &pFrame->m_wndStatusBar;

	 if(!theApp.ComPort.OpenPort())
	 {
		theApp.OpenPort=false;
		m_Stavportu.Empty();
		m_Stavportu.Insert(m_Stavportu.GetLength(),theApp.ComPort.GetComPort()+" open error.");
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		GetDlgItem(IDOK2)->EnableWindow(FALSE);
		

	 }
	 else
	 {
		theApp.OpenPort=true;
		theApp.ComPort.yStartIO(pFrame->m_hWnd);
		GetDlgItem(IDOK)->EnableWindow(FALSE);
		GetDlgItem(IDOK2)->EnableWindow(TRUE);
		
	 }

    UpdateData(FALSE);
  	
    if (pStatus) 
	{
		pStatus->SetPaneText(1,m_Stavportu);
    }

}

BOOL Csettings::OnInitDialog() 
{
	m_Stavportu.Empty();
	CString csPortToOpen;

	CListBox * pLB = (CListBox*) GetDlgItem(IDC_LIST1);

	//If open port close it, remember old port
	if (theApp.OpenPort)
	{
		theApp.csOldPort.Format("%s",theApp.ComPort.GetComPort());
		theApp.ComPort.vEndIO();
		theApp.ComPort.ClosePort();
		theApp.OpenPort=false;
	}
	
	//Check COM ports available in system
	for (int i=1;i<=MAX_COM_PORTS;i++)
	{
		csPortToOpen.Format("COM%d",i);
		theApp.ComPort.SetCOMPort(csPortToOpen);
		if(theApp.ComPort.OpenPort())
		{
			theApp.ComPort.ClosePort();
			pLB->AddString(csPortToOpen);
			
		}
	}
	//Select old opened port
	pLB->SelectString(0,theApp.csOldPort);

	if(theApp.ComPort.GetCOMDataB()=="5")
			m_Databits=0;
	else if(theApp.ComPort.GetCOMDataB()=="6")
			m_Databits=1;
	else if(theApp.ComPort.GetCOMDataB()=="7")
			m_Databits=2;
	else if(theApp.ComPort.GetCOMDataB()=="8")
			m_Databits=3;
	else m_Databits=4;

	if(theApp.ComPort.GetCOMStopB()=="ONESTOPBIT")
			m_Stopbits=0;
	else if(theApp.ComPort.GetCOMStopB()=="ONE5STOPBITS")
			m_Stopbits=1;
	else if(theApp.ComPort.GetCOMStopB()=="TWOSTOPBITS")
			m_Stopbits=2;
	else m_Stopbits=0;

	if(theApp.ComPort.GetCOMParity()=="NOPARITY")
		m_Parity=0;
	else if(theApp.ComPort.GetCOMParity()=="EVENPARITY")
		m_Parity=1;
	else if(theApp.ComPort.GetCOMParity()=="ODDPARITY")
		m_Parity=2;
	else if(theApp.ComPort.GetCOMParity()=="MARKPARITY")
		m_Parity=3;
	else if(theApp.ComPort.GetCOMParity()=="SPACEPARITY")
		m_Parity=4;
	else m_Parity=0;

	if (theApp.OpenPort)
	{

		m_Stavportu.Insert(0,theApp.ComPort.GetComPort()+" ");
		m_Stavportu.Insert(m_Stavportu.GetLength(),theApp.ComPort.GetCOMDataB()+" ");
		m_Stavportu.Insert(m_Stavportu.GetLength(),theApp.ComPort.GetCOMStopB()+" ");
		m_Stavportu.Insert(m_Stavportu.GetLength(),theApp.ComPort.GetCOMParity()+" ");
		m_Stavportu.Insert(m_Stavportu.GetLength(),theApp.ComPort.GetCOMSpeed());
		if(theApp.ComPort.GetCOMDTR()=="DTR HANDSHAKE")
		m_Stavportu.Insert(m_Stavportu.GetLength()," HW");
		if(theApp.ComPort.GetCOMOutX())
		m_Stavportu.Insert(m_Stavportu.GetLength()," SW");
		GetDlgItem(IDOK)->EnableWindow(FALSE);
		GetDlgItem(IDOK2)->EnableWindow(TRUE);
		
	}
	else
	{
		m_Stavportu.Insert(m_Stavportu.GetLength(),"No open port.");
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		GetDlgItem(IDOK2)->EnableWindow(FALSE);
	}
	CDialog::OnInitDialog();
	return TRUE;  
}

void Csettings::OnCancel() 
{
	CDialog::OnCancel();
}

void Csettings::OnOk2() 
{
	theApp.ComPort.ClosePort();
	theApp.ComPort.vEndIO();
	theApp.OpenPort=false;
	UpdateData(TRUE);
	m_Stavportu.Empty();
	m_Stavportu.Insert(m_Stavportu.GetLength(),"No open port.");
	UpdateData(FALSE);

	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDOK2)->EnableWindow(FALSE);
	
	CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;	
	CStatusBar* pStatus = &pFrame->m_wndStatusBar;

	pFrame->KillTimer(1);
    if (pStatus) 
	{
		pStatus->SetPaneText(1,m_Stavportu);
    }
}
