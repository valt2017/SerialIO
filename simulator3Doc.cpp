// simulator3Doc.cpp : Implementierung der Klasse CSimulator3Doc
//

#include "stdafx.h"
#include "simulator3.h"
#include "mainfrm.h"
#include "simulator3Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimulator3Doc

IMPLEMENT_DYNCREATE(CSimulator3Doc, CDocument)
BEGIN_MESSAGE_MAP(CSimulator3Doc, CDocument)
	//{{AFX_MSG_MAP(CSimulator3Doc)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimulator3Doc Konstruktion/Destruktion

CSimulator3Doc::CSimulator3Doc()
{
}

CSimulator3Doc::~CSimulator3Doc()
{
}

BOOL CSimulator3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);
	m_stringArray.SetSize(10);
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSimulator3Doc Serialisierung

void CSimulator3Doc::Serialize(CArchive& ar)
{
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
	
}

/////////////////////////////////////////////////////////////////////////////
// CSimulator3Doc Diagnose

#ifdef _DEBUG
void CSimulator3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSimulator3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSimulator3Doc Befehle

void CSimulator3Doc::OnFileOpen() 
{
	CFileDialog Fdlg(TRUE,NULL,NULL,NULL,"Simulator files (*.sim)|*.sim");
	if (Fdlg.DoModal()==IDOK)
		AfxGetApp()->OpenDocumentFile(Fdlg.GetPathName());
}

BOOL CSimulator3Doc::SaveModified() 
{
	return 1;
	//return CDocument::SaveModified();
}
