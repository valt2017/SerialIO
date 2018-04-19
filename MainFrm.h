// MainFrm.h : Schnittstelle der Klasse CMainFrame
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__11933E8E_F0E1_4BA4_87BB_F4913544B45A__INCLUDED_)
#define AFX_MAINFRM_H__11933E8E_F0E1_4BA4_87BB_F4913544B45A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CFrameWnd
{
	
protected: // Nur aus Serialisierung erzeugen
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attribute
public:
//received
	BOOL m_bDecimal;
	BOOL m_bHexa;
	BOOL m_bASCII;
	
public:
   void vSendMacro(int iMacro);
   void vSaveConfig(CString csIniFile);
   void vLoadConfig(CString csIniFile);
   void UpdateStatusBar(CString data);
       // Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL
   afx_msg void OnViewStatusBar();
   afx_msg LRESULT OnRecIoEvent(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnSndIoEvent(WPARAM wParam, LPARAM lParam);
   
   // Implementierung
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CComboBox   m_wndComboBox;

protected:  // Eingebundene Elemente der Steuerleiste
	CReBar         m_wndReBar;
	CDialogBar	   m_wndDlgBar;
	CSplitterWnd   m_wndSplitter;

	CBitmap m_OpenBitmap;
	CBitmap m_CheckBitmap;
	CBitmap m_UnCheckBitmap;
	CBitmap m_AboutBitmap;
	CBitmap m_DebugBitmap;
	CBitmap m_ExitBitmap;
	CBitmap m_SettingsBitmap;
	CBitmap m_CountersBitmap;
	CBitmap m_ComBitmap;
	CBitmap m_NewBitmap;

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSettings();
	afx_msg void OnViewAsciitable();
	afx_msg void OnAboutAplicationinfo();
	afx_msg void OnUpdateViewAscii(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewHexa(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewDecimal(CCmdUI* pCmdUI);
	afx_msg void OnViewAscii();
	afx_msg void OnViewHexa();
	afx_msg void OnViewDecimal();
	afx_msg void OnDecimal();
	afx_msg void OnAscii();
	afx_msg void OnHexa();
	afx_msg void OnUpdateAscii(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDecimal(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHexa(CCmdUI* pCmdUI);
	afx_msg void OnSettingsProtocol();
	afx_msg void OnSendMacro1();
	afx_msg void OnSendMacro10();
	afx_msg void OnSendMacro2();
	afx_msg void OnSendMacro3();
	afx_msg void OnSendMacro4();
	afx_msg void OnSendMacro5();
	afx_msg void OnSendMacro6();
	afx_msg void OnSendMacro7();
	afx_msg void OnSendMacro8();
	afx_msg void OnSendMacro9();
	afx_msg void OnUpdateSendMacro1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSendMacro10(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSendMacro2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSendMacro3(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSendMacro4(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSendMacro5(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSendMacro6(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSendMacro7(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSendMacro8(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSendMacro9(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSendSendhexfile(CCmdUI* pCmdUI);
	afx_msg void OnSendSendhexfile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MAINFRM_H__11933E8E_F0E1_4BA4_87BB_F4913544B45A__INCLUDED_)
