#if !defined(AFX_SETTINGS_H__98E0F817_6E54_4A6A_8D4A_F114BA8548AE__INCLUDED_)
#define AFX_SETTINGS_H__98E0F817_6E54_4A6A_8D4A_F114BA8548AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// settings.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Csettings 
#define	MAX_COM_PORTS 15

class Csettings : public CDialog
{
// Konstruktion
public:
	Csettings(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(Csettings)
	enum { IDD = IDD_DIALOG1 };
	CButton	m_Closeport;
	CButton	m_Set;
	int		m_Portnumber;
	int		m_Databits;
	int		m_Stopbits;
	int		m_Parity;
	int		m_HWhandshake;
	int		m_SWhandshake;
	CString	m_Stavportu;
	int		m_Baudrate;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(Csettings)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(Csettings)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnOk2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SETTINGS_H__98E0F817_6E54_4A6A_8D4A_F114BA8548AE__INCLUDED_
