// MyView.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "simulator3.h"
#include "MyView.h"
#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyView

IMPLEMENT_DYNCREATE(CMyView, CEditView)

CMyView::CMyView()
{

}

CMyView::~CMyView()
{
	m_Font.DeleteObject();
}


BEGIN_MESSAGE_MAP(CMyView, CEditView)
	//{{AFX_MSG_MAP(CMyView)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Zeichnung CMyView 

void CMyView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// ZU ERLEDIGEN: Code zum Zeichnen hier einfügen
}

/////////////////////////////////////////////////////////////////////////////
// Diagnose CMyView

#ifdef _DEBUG
void CMyView::AssertValid() const
{
	CEditView::AssertValid();
}

void CMyView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CMyView 

void CMyView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (theApp.Send_to_screen)
	{
	    theApp.Send_to_screen=false;
		CEditView::OnChar(nChar, nRepCnt, nFlags);
	}
	else
	{
		CEditView::OnChar(nChar, nRepCnt, nFlags);
		theApp.ComPort.SendChar(nChar);
	}
}


void CMyView::OnInitialUpdate()
{
	CEditView::OnInitialUpdate();
	// Creates a font
	m_Font.CreatePointFont(theApp.iFontSize, _T("Consolas"));
	// With a member variable associated to the static control
	SetFont(&m_Font);
}
