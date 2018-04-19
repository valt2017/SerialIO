#if !defined(AFX_ABOUT_H__908952D3_F796_471E_A2D2_5D2056EF7053__INCLUDED_)
#define AFX_ABOUT_H__908952D3_F796_471E_A2D2_5D2056EF7053__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// About.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CAbout 

class CAbout : public CDialog
{
// Konstruktion
public:
	CAbout(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CAbout)
	enum { IDD = IDD_DIALOG2 };
	CString	m_TimeStamp;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CAbout)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CAbout)
		// HINWEIS: Der Klassen-Assistent fügt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_ABOUT_H__908952D3_F796_471E_A2D2_5D2056EF7053__INCLUDED_
