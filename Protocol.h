#if !defined(AFX_PROTOCOL_H__D47ABF00_BD7D_42BE_9E16_7150B1EEBF4A__INCLUDED_)
#define AFX_PROTOCOL_H__D47ABF00_BD7D_42BE_9E16_7150B1EEBF4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Protocol.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CProtocol 

class CProtocol : public CDialog
{
// Konstruktion
public:
	CProtocol(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CProtocol)
	enum { IDD = IDD_DIALOG4 };
	CString	m_Macro1;
	CString	m_Macro2;
	CString	m_Macro3;
	CString	m_Macro4;
	CString	m_Macro5;
	CString	m_Macro6;
	CString	m_Macro7;
	CString	m_Macro8;
	CString	m_Macro9;
	CString	m_Macro10;
	BOOL	m_CR;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CProtocol)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CProtocol)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdateEdit1();
	afx_msg void OnUpdateEdit2();
	afx_msg void OnUpdateEdit3();
	afx_msg void OnUpdateEdit4();
	afx_msg void OnUpdateEdit5();
	afx_msg void OnUpdateEdit6();
	afx_msg void OnUpdateEdit7();
	afx_msg void OnUpdateEdit8();
	afx_msg void OnUpdateEdit9();
	afx_msg void OnUpdateEdit10();
	afx_msg void OnCheck1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_PROTOCOL_H__D47ABF00_BD7D_42BE_9E16_7150B1EEBF4A__INCLUDED_
