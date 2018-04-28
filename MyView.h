#if !defined(AFX_MYVIEW_H__91868B4C_DDDD_4FF5_B430_A02D4BD9E95A__INCLUDED_)
#define AFX_MYVIEW_H__91868B4C_DDDD_4FF5_B430_A02D4BD9E95A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyView.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Ansicht CMyView 

class CMyView : public CEditView
{
private:
	CFont m_Font;

protected:
//	CMyView();           // Dynamische Erstellung verwendet geschützten Konstruktor
//	DECLARE_DYNCREATE(CMyView)
// Attribute
public:
	
// Operationen
public:
	CMyView();           // Dynamische Erstellung verwendet geschützten Konstruktor
	DECLARE_DYNCREATE(CMyView)

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CMyView)
	protected:
	virtual void OnDraw(CDC* pDC);      // Überschrieben zum Zeichnen dieser Ansicht
	//}}AFX_VIRTUAL

// Implementierung
protected:
	virtual ~CMyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(CMyView)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_MYVIEW_H__91868B4C_DDDD_4FF5_B430_A02D4BD9E95A__INCLUDED_
