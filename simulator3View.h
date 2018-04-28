// simulator3View.h : Schnittstelle der Klasse CSimulator3View
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMULATOR3VIEW_H__A8A8E595_9249_49A5_BE6C_A3FD1C342FC3__INCLUDED_)
#define AFX_SIMULATOR3VIEW_H__A8A8E595_9249_49A5_BE6C_A3FD1C342FC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSimulator3View :	public CEditView

{
private:
	CRect m_rectPrint;
	CFont m_Font;
protected: // Nur aus Serialisierung erzeugen
	
// Attribute
public:
	CSimulator3Doc* GetDocument();
	CSimulator3View();
	DECLARE_DYNCREATE(CSimulator3View)

// Operationen
public:
	
// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CSimulator3View)
	public:
	virtual void OnDraw(CDC* pDC);  // überladen zum Zeichnen dieser Ansicht
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL
// Implementierung
public:
	virtual ~CSimulator3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	void UpdateReceive(WPARAM wParam);
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CSimulator3View)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in simulator3View.cpp
inline CSimulator3Doc* CSimulator3View::GetDocument()
   { return (CSimulator3Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_SIMULATOR3VIEW_H__A8A8E595_9249_49A5_BE6C_A3FD1C342FC3__INCLUDED_)
