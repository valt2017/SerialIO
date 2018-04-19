// COMPort.h: interface for the CCOMPort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPORT_H__7EECAF70_89E3_4E8C_8C6C_AE4DE506BD0E__INCLUDED_)
#define AFX_COMPORT_H__7EECAF70_89E3_4E8C_8C6C_AE4DE506BD0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define  SIZE_OF_BUFF           1024

#define  ID_IO_REC_EVENT        WM_USER+1
#define  ID_IO_SND_EVENT        WM_USER+2
#define  ID_IO_DBG_EVENT        WM_USER+3

UINT uCheckSendEvent( LPVOID pParam );
UINT uCheckRecEvent( LPVOID pParam );

extern DWORD   BaudTable[];
extern BYTE    ParityTable[];
extern BYTE    StopBitsTable[];

class CCOMPort  
{
public:
	CCOMPort();
	virtual ~CCOMPort();

  CString	GetErrorText	(void);
  void		SetErrorText	(DWORD dwErrorCode);
  void		GetErrorText	(CString& strErrorText);
  void		vCreateCOMEvent	(void);
  void		SetCOMPort		(const CString& strCOMPort);
  CString	GetComPort		(void);
  CString	GetCOMSpeed		(void);
  void		SetCOMSpeed		(DWORD dwCOMSpeed);
  CString	GetCOMRTS		(void);
  void		SetCOMOutX		(BOOL bOutX);
  BOOL		GetCOMOutX		(void);
  void		SetCOMInX		(BOOL bInX);
  BOOL		GetCOMInX		(void);
  void		SetCOMRTS		(BYTE bCOMSRTS);
  CString	GetCOMDTR		(void);
  void		SetCOMDTR		(BYTE bCOMDTR);
  CString	GetCOMParity	(void);
  BYTE		bGetCOMParity	(void);
  void		SetCOMParity	(BYTE bCOMParity);
  CString	GetCOMDataB		(void);
  BYTE		bGetCOMDataB	(void);
  void		SetCOMDataB		(BYTE bCOMDataB);
  void		SetCOMStopB		(BYTE bCOMStopB);
  CString	GetCOMStopB		(void);
  BYTE		bGetCOMStopB	(void);
  BOOL		OpenPort		(void);
  void		ClosePort		(void);
  BOOL		SendBreak		(DWORD dwTime);
  BOOL		SendChar		(BYTE bSendData);
  BOOL		Write			(BYTE * bSendBuffer, DWORD dwBytesToSend);
  BOOL		Read			(BYTE * bRecBuffer, DWORD dwBytesToRead);
  BOOL		yStartIO		(HWND hWnd);
  void		vEndIO			(void);

protected:

private:

//Attributes
public:
	HWND          m_hSrcWnd;
	HANDLE        m_hPort;

	OVERLAPPED    m_xOverCommWait;
	OVERLAPPED    m_xOverCommRead;
	OVERLAPPED    m_xOverCommWrite;
	DWORD         m_EventMask;
	DWORD         m_dwReaded;
	BYTE          m_bReadBuffer[10];
	BOOL          m_yExitFromThread;
	CWinThread*   pReadThread;
	HANDLE		  hReadThread;
	CWinThread*   pWriteThread;
	HANDLE		  hWriteThread;

protected:
	CString       m_strErrorText;
private:
	CString       m_strCOMPort;
	DWORD         m_dwCOMSpeed;
	BYTE          m_bCOMParity;
	BYTE          m_bCOMStopBits;
	BYTE          m_bCOMByteSize;             
	BYTE		  m_bDTRControl;
	BYTE		  m_bRTSControl;
	BOOL		  m_bOutX;
	BOOL		  m_bInX;
	char*		  pc_SendBuffer;
	int			  m_iSendIndex;	  

};


#endif // !defined(AFX_COMPORT_H__7EECAF70_89E3_4E8C_8C6C_AE4DE506BD0E__INCLUDED_)
