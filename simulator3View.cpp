// simulator3View.cpp : Implementierung der Klasse CSimulator3View
//

#include "stdafx.h"
#include "simulator3.h"
#include "simulator3Doc.h"
#include "simulator3View.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimulator3View

IMPLEMENT_DYNCREATE(CSimulator3View,CEditView)

BEGIN_MESSAGE_MAP(CSimulator3View, CEditView)
	//{{AFX_MSG_MAP(CSimulator3View)
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard-Druckbefehle
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimulator3View Konstruktion/Destruktion

CSimulator3View::CSimulator3View()
{

}

CSimulator3View::~CSimulator3View()
{
}

BOOL CSimulator3View::PreCreateWindow(CREATESTRUCT& cs)
{
	
	return CEditView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSimulator3View Zeichnen

void CSimulator3View::OnDraw(CDC* pDC)
{
}

/////////////////////////////////////////////////////////////////////////////
// CSimulator3View Diagnose

#ifdef _DEBUG
void CSimulator3View::AssertValid() const
{
	CEditView::AssertValid();
}

void CSimulator3View::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CSimulator3Doc* CSimulator3View::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSimulator3Doc)));
	return (CSimulator3Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSimulator3View Nachrichten-Handler

void CSimulator3View::OnInitialUpdate() 
{
	CEditView::OnInitialUpdate();
	
}

void CSimulator3View::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	CEditView::OnPrint(pDC, pInfo);
}


void CSimulator3View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (theApp.Receive_to_screen)
	{
	    theApp.Receive_to_screen=false;
	}
	CEditView::OnChar(nChar, nRepCnt, nFlags);
}

void CSimulator3View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CEditView::OnLButtonDown(nFlags, point);
}

//void CSimulator3View::UpdateReceive(WPARAM wParam)
//{
	
//}
