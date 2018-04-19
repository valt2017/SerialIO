// simulator3.cpp : Legt das Klassenverhalten für die Anwendung fest.
//
#include "stdafx.h"
#include "simulator3.h"
#include "MainFrm.h"
#include "simulator3Doc.h"
#include "simulator3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimulator3App

BEGIN_MESSAGE_MAP(CSimulator3App, CWinApp)
	//{{AFX_MSG_MAP(CSimulator3App)
	//}}AFX_MSG_MAP
	// Dateibasierte Standard-Dokumentbefehle
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard-Druckbefehl "Seite einrichten"
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimulator3App Konstruktion

CSimulator3App::CSimulator3App()
{
	theApp.iInterval=10;
	theApp.m_sPoleMien.SetSize(32);
	theApp.m_sPoleMien[0]="NUL";
	theApp.m_sPoleMien[1]="SOH";
	theApp.m_sPoleMien[2]="STX";
	theApp.m_sPoleMien[3]="ETX";
	theApp.m_sPoleMien[4]="EOT";
	theApp.m_sPoleMien[5]="ENQ";
	theApp.m_sPoleMien[6]="ACK";
	theApp.m_sPoleMien[7]="BEL";
	theApp.m_sPoleMien[8]="BS"; 
	theApp.m_sPoleMien[9]="HT"; 
	theApp.m_sPoleMien[10]="LF";
	theApp.m_sPoleMien[11]="VT";
	theApp.m_sPoleMien[12]="FF";
	theApp.m_sPoleMien[13]="CR";
	theApp.m_sPoleMien[14]="SO";
	theApp.m_sPoleMien[15]="SI";
	theApp.m_sPoleMien[16]="DLE";
	theApp.m_sPoleMien[17]="DC1";
	theApp.m_sPoleMien[18]="DC2";
	theApp.m_sPoleMien[19]="DC3";
	theApp.m_sPoleMien[20]="DC4";
	theApp.m_sPoleMien[21]="NAK";
	theApp.m_sPoleMien[22]="SYN";
	theApp.m_sPoleMien[23]="ETB";
	theApp.m_sPoleMien[24]="CAN";
	theApp.m_sPoleMien[25]="EM";
	theApp.m_sPoleMien[26]="SUB";
	theApp.m_sPoleMien[27]="ESC";
	theApp.m_sPoleMien[28]="FS";
	theApp.m_sPoleMien[29]="GS";
	theApp.m_sPoleMien[30]="RS";
	theApp.m_sPoleMien[31]="US";

	theApp.csTimeStamp=__TIMESTAMP__;
}

/////////////////////////////////////////////////////////////////////////////
// Das einzige CSimulator3App-Objekt

CSimulator3App theApp;

/////////////////////////////////////////////////////////////////////////////
// CSimulator3App Initialisierung

BOOL CSimulator3App::InitInstance()
{
	AfxEnableControlContainer();

	// Standardinitialisierung
	// Wenn Sie diese Funktionen nicht nutzen und die Größe Ihrer fertigen 
	//  ausführbaren Datei reduzieren wollen, sollten Sie die nachfolgenden
	//  spezifischen Initialisierungsroutinen, die Sie nicht benötigen, entfernen.

#ifdef _AFXDLL
	Enable3dControls();			// Diese Funktion bei Verwendung von MFC in gemeinsam genutzten DLLs aufrufen
#else
	Enable3dControlsStatic();	// Diese Funktion bei statischen MFC-Anbindungen aufrufen
#endif

	// Ändern des Registrierungsschlüssels, unter dem unsere Einstellungen gespeichert sind.
	// ZU ERLEDIGEN: Sie sollten dieser Zeichenfolge einen geeigneten Inhalt geben
	// wie z.B. den Namen Ihrer Firma oder Organisation.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings();  // Standard INI-Dateioptionen laden (einschließlich MRU)
	// Dokumentvorlagen der Anwendung registrieren. Dokumentvorlagen
	//  dienen als Verbindung zwischen Dokumenten, Rahmenfenstern und Ansichten.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSimulator3Doc),
		RUNTIME_CLASS(CMainFrame),       // Haupt-SDI-Rahmenfenster
		RUNTIME_CLASS(CSimulator3View));
	AddDocTemplate(pDocTemplate);

	// Befehlszeile parsen, um zu prüfen auf Standard-Umgebungsbefehle DDE, Datei offen
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Verteilung der in der Befehlszeile angegebenen Befehle
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Das einzige Fenster ist initialisiert und kann jetzt angezeigt und aktualisiert werden.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	
	return TRUE;
}


