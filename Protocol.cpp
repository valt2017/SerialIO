// Protocol.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "simulator3.h"
#include "Protocol.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CProtocol 


CProtocol::CProtocol(CWnd* pParent /*=NULL*/)
	: CDialog(CProtocol::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProtocol)
	m_Macro1 = _T("");
	m_Macro2 = _T("");
	m_Macro3 = _T("");
	m_Macro4 = _T("");
	m_Macro5 = _T("");
	m_Macro6 = _T("");
	m_Macro7 = _T("");
	m_Macro8 = _T("");
	m_Macro9 = _T("");
	m_Macro10 = _T("");
	m_CR = FALSE;
	//}}AFX_DATA_INIT
}


void CProtocol::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProtocol)
	DDX_Text(pDX, IDC_EDIT1, m_Macro1);
	DDX_Text(pDX, IDC_EDIT2, m_Macro2);
	DDX_Text(pDX, IDC_EDIT3, m_Macro3);
	DDX_Text(pDX, IDC_EDIT4, m_Macro4);
	DDX_Text(pDX, IDC_EDIT5, m_Macro5);
	DDX_Text(pDX, IDC_EDIT6, m_Macro6);
	DDX_Text(pDX, IDC_EDIT7, m_Macro7);
	DDX_Text(pDX, IDC_EDIT8, m_Macro8);
	DDX_Text(pDX, IDC_EDIT9, m_Macro9);
	DDX_Text(pDX, IDC_EDIT10, m_Macro10);
	DDX_Check(pDX, IDC_CHECK1, m_CR);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProtocol, CDialog)
	//{{AFX_MSG_MAP(CProtocol)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdateEdit1)
	ON_EN_UPDATE(IDC_EDIT2, OnUpdateEdit2)
	ON_EN_UPDATE(IDC_EDIT3, OnUpdateEdit3)
	ON_EN_UPDATE(IDC_EDIT4, OnUpdateEdit4)
	ON_EN_UPDATE(IDC_EDIT5, OnUpdateEdit5)
	ON_EN_UPDATE(IDC_EDIT6, OnUpdateEdit6)
	ON_EN_UPDATE(IDC_EDIT7, OnUpdateEdit7)
	ON_EN_UPDATE(IDC_EDIT8, OnUpdateEdit8)
	ON_EN_UPDATE(IDC_EDIT9, OnUpdateEdit9)
	ON_EN_UPDATE(IDC_EDIT10, OnUpdateEdit10)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CProtocol 

void CProtocol::OnOK() 
{
	CDialog::OnOK();
}

BOOL CProtocol::OnInitDialog() 
{
	m_Macro1.Insert(0,theApp.Macros[0]);
	m_Macro2.Insert(0,theApp.Macros[1]);
	m_Macro3.Insert(0,theApp.Macros[2]);
	m_Macro4.Insert(0,theApp.Macros[3]);
	m_Macro5.Insert(0,theApp.Macros[4]);
	m_Macro6.Insert(0,theApp.Macros[5]);
	m_Macro7.Insert(0,theApp.Macros[6]);
	m_Macro8.Insert(0,theApp.Macros[7]);
	m_Macro9.Insert(0,theApp.Macros[8]);
	m_Macro10.Insert(0,theApp.Macros[9]);

    if(theApp.bSendCR)
        m_CR=theApp.bSendCR;
	CDialog::OnInitDialog();
	return TRUE;  
}


void CProtocol::OnUpdateEdit1() 
{
	UpdateData(TRUE); 
	theApp.Macros[0]=m_Macro1;
	UpdateData(FALSE); 
}

void CProtocol::OnUpdateEdit2() 
{
	UpdateData(TRUE); 
	theApp.Macros[1]=m_Macro2;
	UpdateData(FALSE); 
}

void CProtocol::OnUpdateEdit3() 
{
	UpdateData(TRUE); 
	theApp.Macros[2]=m_Macro3;
	UpdateData(FALSE); 
}

void CProtocol::OnUpdateEdit4() 
{
	UpdateData(TRUE); 
	theApp.Macros[3]=m_Macro4;
	UpdateData(FALSE); 
}

void CProtocol::OnUpdateEdit5() 
{
	UpdateData(TRUE); 
	theApp.Macros[4]=m_Macro5;
	UpdateData(FALSE); 
}

void CProtocol::OnUpdateEdit6() 
{
	UpdateData(TRUE); 
	theApp.Macros[5]=m_Macro6;
	UpdateData(FALSE); 
	
}

void CProtocol::OnUpdateEdit7() 
{
	UpdateData(TRUE); 
	theApp.Macros[6]=m_Macro7;
	UpdateData(FALSE); 	
}


void CProtocol::OnUpdateEdit8() 
{
	UpdateData(TRUE); 
	theApp.Macros[7]=m_Macro8;
	UpdateData(FALSE); 
}

void CProtocol::OnUpdateEdit9() 
{
	UpdateData(TRUE); 
	theApp.Macros[8]=m_Macro9;
	UpdateData(FALSE); 
}

void CProtocol::OnUpdateEdit10() 
{
	UpdateData(TRUE); 
	theApp.Macros[9]=m_Macro10;
	UpdateData(FALSE); 
}

void CProtocol::OnCheck1() 
{
    if(theApp.bSendCR)
      theApp.bSendCR=false;
    else
      theApp.bSendCR=true;
}
