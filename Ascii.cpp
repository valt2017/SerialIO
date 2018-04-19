// Ascii.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "simulator3.h"
#include "Ascii.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Ascii 

Ascii::Ascii(CWnd* pParent /*=NULL*/)
	: CDialog(Ascii::IDD, pParent)
{
	//{{AFX_DATA_INIT(Ascii)
	m_ASCII = _T("");
	//}}AFX_DATA_INIT
}


void Ascii::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Ascii)
	DDX_LBString(pDX, IDC_LIST3, m_ASCII);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Ascii, CDialog)
	//{{AFX_MSG_MAP(Ascii)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten Ascii 

BOOL Ascii::OnInitDialog() 
{
	CStringArray m_sPoleSkratiek;
	m_sPoleSkratiek.SetSize(32);

	m_sPoleSkratiek[0]="Ctrl+@";
	m_sPoleSkratiek[1]="Ctrl+A";
	m_sPoleSkratiek[2]="Ctrl+B";
	m_sPoleSkratiek[3]="Ctrl+C";
	m_sPoleSkratiek[4]="Ctrl+D";
	m_sPoleSkratiek[5]="Ctrl+E";
	m_sPoleSkratiek[6]="Ctlr+F";
	m_sPoleSkratiek[7]="Ctlr+G";
	m_sPoleSkratiek[8]="Ctlr+H"; 
	m_sPoleSkratiek[9]="Ctlr+I"; 
	m_sPoleSkratiek[10]="Ctlr+J";
	m_sPoleSkratiek[11]="Ctlr+K";
	m_sPoleSkratiek[12]="Ctlr+L";
	m_sPoleSkratiek[13]="Ctlr+M";
	m_sPoleSkratiek[14]="Ctlr+N";
	m_sPoleSkratiek[15]="Ctlr+O";
	m_sPoleSkratiek[16]="Ctlr+P";
	m_sPoleSkratiek[17]="Ctlr+Q";
	m_sPoleSkratiek[18]="Ctlr+R";
	m_sPoleSkratiek[19]="Ctlr+S";
	m_sPoleSkratiek[20]="Ctlr+T";
	m_sPoleSkratiek[21]="Ctlr+U";
	m_sPoleSkratiek[22]="Ctlr+V";
	m_sPoleSkratiek[23]="Ctlr+W";
	m_sPoleSkratiek[24]="Ctlr+X";
	m_sPoleSkratiek[25]="Ctlr+Y";
	m_sPoleSkratiek[26]="Ctlr+Y";
	m_sPoleSkratiek[27]="Ctlr+[";
	m_sPoleSkratiek[28]="Ctlr+\\";
	m_sPoleSkratiek[29]="Ctlr+]";
	m_sPoleSkratiek[30]="Ctlr+^";
	m_sPoleSkratiek[31]="Ctlr+_";


	CString riadok;
	CDialog::OnInitDialog();
	CListBox * pLB = (CListBox*) GetDlgItem(IDC_LIST3);
	riadok.Format("________________________________");
	pLB->InsertString(-1,riadok);
	riadok.Format("Non-printing Characters");
	pLB->InsertString(-1,riadok);
	riadok.Format("________________________________");
	pLB->InsertString(-1,riadok);

	riadok.Format("Decimal   Hexa   Shortcut   Name");
	pLB->InsertString(-1,riadok);

	for (int i=0;i<=31;i++)
	{
		riadok.Format("%03d         %02Xh       %s        %s",i,i,m_sPoleSkratiek[i],theApp.m_sPoleMien[i]);
		pLB->InsertString(-1,riadok);
	}
	riadok.Format("________________________________");
	pLB->InsertString(-1,riadok);
	riadok.Format("Printing Characters");
	pLB->InsertString(-1,riadok);
	riadok.Format("________________________________");
	pLB->InsertString(-1,riadok);

	riadok.Format("Decimal  Hexa  Char");
	pLB->InsertString(-1,riadok);
	
	for (int i=32;i<=127;i++)
	{
		riadok.Format("%03d         %02Xh       %c",i,i,i);
		pLB->InsertString(-1,riadok);
	}
	
	return TRUE;  
	              
}
