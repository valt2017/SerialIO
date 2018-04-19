#if !defined(AFX_ASCII_H__09A982B7_A3E1_4BEB_8461_04D74C491CF6__INCLUDED_)
#define AFX_ASCII_H__09A982B7_A3E1_4BEB_8461_04D74C491CF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Ascii.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Ascii 

class Ascii : public CDialog
{
// Konstruktion
public:
	Ascii(CWnd* pParent = NULL);   // Standardkonstruktor
	
// Dialogfelddaten
	//{{AFX_DATA(Ascii)
	enum { IDD = IDD_DIALOG3 };
	CString	m_ASCII;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(Ascii)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(Ascii)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_ASCII_H__09A982B7_A3E1_4BEB_8461_04D74C491CF6__INCLUDED_
