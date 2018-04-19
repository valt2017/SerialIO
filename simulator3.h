// simulator3.h : Haupt-Header-Datei für die Anwendung SIMULATOR3
//

#if !defined(AFX_SIMULATOR3_H__22F7CD0A_3910_4DEF_8A62_6B8F8C15BA99__INCLUDED_)
#define AFX_SIMULATOR3_H__22F7CD0A_3910_4DEF_8A62_6B8F8C15BA99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // Hauptsymbole
#include "comport.h"


/////////////////////////////////////////////////////////////////////////////
// CSimulator3App:
// Siehe simulator3.cpp für die Implementierung dieser Klasse
//

class CSimulator3App : public CWinApp
{
public:
	CSimulator3App();
	CCOMPort ComPort;

	unsigned char	Cislo;
	bool			OpenPort;
	CStringArray	Macros;
	bool			Send_to_screen;
	bool			Receive_to_screen;
    bool            bSendCR;
	CStringArray	m_sPoleMien;	
	CString			csTimeStamp;
	CString			csOldPort;
	CString			csDefaultIniFilePath;

	int				iInterval;

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CSimulator3App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung
	//{{AFX_MSG(CSimulator3App)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CSimulator3App theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_SIMULATOR3_H__22F7CD0A_3910_4DEF_8A62_6B8F8C15BA99__INCLUDED_)
