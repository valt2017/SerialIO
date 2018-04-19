/////////////////////////////////////////////////////////////////////////////
// ComPort.cpp: implementation of the CComPort class.					   //
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "COMPort.h"
/////////////////////////////////////////////////////////////////////////////
// BaudRate table														   //
/////////////////////////////////////////////////////////////////////////////
DWORD    BaudTable[] =
         {
            CBR_1200, CBR_2400, CBR_4800, CBR_9600, CBR_14400, CBR_19200, 
			CBR_38400, CBR_57600, CBR_115200
         } ;
/////////////////////////////////////////////////////////////////////////////
// Parity table															   //
/////////////////////////////////////////////////////////////////////////////
BYTE     ParityTable[] =
         {
            NOPARITY, EVENPARITY, ODDPARITY, MARKPARITY, SPACEPARITY
         } ;
/////////////////////////////////////////////////////////////////////////////
// Stop bit table														   //
/////////////////////////////////////////////////////////////////////////////
BYTE     StopBitsTable[] =
         {
            ONESTOPBIT, ONE5STOPBITS, TWOSTOPBITS
         } ;
/////////////////////////////////////////////////////////////////////////////
// Constructor															   //
/////////////////////////////////////////////////////////////////////////////
CCOMPort::CCOMPort()
{
  m_strCOMPort    = "COM1";
  m_hPort		  =	INVALID_HANDLE_VALUE;
  m_strErrorText  = "";
  m_dwCOMSpeed    = CBR_9600;
  m_bCOMParity    = NOPARITY;
  m_bCOMStopBits  = ONESTOPBIT;
  m_bCOMByteSize  = 8;             
  m_bDTRControl	  = DTR_CONTROL_DISABLE;
  m_bRTSControl   = RTS_CONTROL_DISABLE;
  m_bOutX		  = FALSE;
  m_bInX		  = FALSE;
  pc_SendBuffer   = new char[512];
  m_iSendIndex	  = 0;
}
/////////////////////////////////////////////////////////////////////////////
// Destructor															   //
/////////////////////////////////////////////////////////////////////////////
CCOMPort::~CCOMPort()
{
	ClosePort();
	delete [] pc_SendBuffer;
}
/////////////////////////////////////////////////////////////////////////////
// GetCOMOutX															   //
/////////////////////////////////////////////////////////////////////////////
BOOL CCOMPort::GetCOMOutX()
{
	return m_bOutX;
}
/////////////////////////////////////////////////////////////////////////////
// GetCOMInX															   //
/////////////////////////////////////////////////////////////////////////////
BOOL CCOMPort::GetCOMInX()
{
	return m_bInX;
}
/////////////////////////////////////////////////////////////////////////////
// SetCOMInX															   //
/////////////////////////////////////////////////////////////////////////////
void CCOMPort::SetCOMInX(BOOL bInX)
{
	m_bInX=bInX;
}
/////////////////////////////////////////////////////////////////////////////
// SetCOMOutX															   //
/////////////////////////////////////////////////////////////////////////////
void CCOMPort::SetCOMOutX(BOOL bOutX)
{
	m_bOutX=bOutX;
}
/////////////////////////////////////////////////////////////////////////////
// SetCOMDTR															   //
/////////////////////////////////////////////////////////////////////////////
void CCOMPort::SetCOMDTR(BYTE bCOMDTR)
{
	m_bDTRControl=bCOMDTR;
}
/////////////////////////////////////////////////////////////////////////////
// SetCOMRTS															   //
/////////////////////////////////////////////////////////////////////////////
void CCOMPort::SetCOMRTS(BYTE bCOMRTS)
{
	m_bRTSControl=bCOMRTS;
}
/////////////////////////////////////////////////////////////////////////////
// GetCOMDTR															   //
/////////////////////////////////////////////////////////////////////////////
CString CCOMPort::GetCOMDTR(void)
{
  switch(m_bDTRControl)
  {
    case DTR_CONTROL_DISABLE:
	  return "DTR DISABLE";
    break;

    case DTR_CONTROL_ENABLE:
	  return "DTR ENABLE";
    break;

    case DTR_CONTROL_HANDSHAKE:
	  return "DTR HANDSHAKE";
    break;

    default:
      return "DTR DISABLE";
    break;
  }
}
/////////////////////////////////////////////////////////////////////////////
// GetCOMRTS															   //
/////////////////////////////////////////////////////////////////////////////
CString CCOMPort::GetCOMRTS(void)
{
  switch(m_bRTSControl)
  {
    case RTS_CONTROL_DISABLE:
	  return "RTS DISABLE";
    break;

    case RTS_CONTROL_ENABLE:
	  return "RTS ENABLE";
    break;

    case RTS_CONTROL_HANDSHAKE:
	  return "RTS HANDSHAKE";
    break;

    case RTS_CONTROL_TOGGLE:
	  return "RTS TOGGLE";
    break;

    default:
      return "RTS DISABLE";
    break;
  }
}
/////////////////////////////////////////////////////////////////////////////
// GetErrorText															   //
/////////////////////////////////////////////////////////////////////////////
CString CCOMPort::GetErrorText(void)
{
	return m_strErrorText;
}
/////////////////////////////////////////////////////////////////////////////
// GetCOMParity															   //
/////////////////////////////////////////////////////////////////////////////
BYTE CCOMPort::bGetCOMParity(void) 
{
	return m_bCOMParity;
}

CString CCOMPort::GetCOMParity(void)
{
  switch(m_bCOMParity)
  {
    case NOPARITY:
	  return "NOPARITY";
    break;

    case EVENPARITY:
	  return "EVENPARITY";
    break;

    case ODDPARITY:
	  return "ODDPARITY";
    break;

    case MARKPARITY:
	  return "MARKPARITY";
    break;

    case SPACEPARITY:
	  return "SPACEPARITY";
    break;

    default:
      return "NOPARITY";
    break;
  }
}
/////////////////////////////////////////////////////////////////////////////
// GetCOMDataB															   //
/////////////////////////////////////////////////////////////////////////////
BYTE CCOMPort::bGetCOMDataB(void)
{
	return m_bCOMByteSize;
}

CString CCOMPort::GetCOMDataB(void)
{
	CString db;
	db.Format("%d", m_bCOMByteSize);
	return db;
}
/////////////////////////////////////////////////////////////////////////////
// GetCOMStopB															   //
/////////////////////////////////////////////////////////////////////////////
BYTE CCOMPort::bGetCOMStopB(void)
{
	return m_bCOMStopBits;
}

CString CCOMPort::GetCOMStopB(void)
{
 switch(m_bCOMStopBits)
  {
    case ONESTOPBIT:
	  return "ONESTOPBIT";
    break;

    case ONE5STOPBITS:
	  return "ONE5STOPBITS";
    break;

    case TWOSTOPBITS:
	  return "TWOSTOPBITS";
    break;

    default:
      return "ONESTOPBIT";
    break;
  }
}
/////////////////////////////////////////////////////////////////////////////
// GetCOMSpeed															   //
/////////////////////////////////////////////////////////////////////////////
CString CCOMPort::GetCOMSpeed(void)
{
	CString Sp;
	Sp.Format("%d", m_dwCOMSpeed);
	return Sp;
}
/////////////////////////////////////////////////////////////////////////////
// vCreateCOMEvent														   //
/////////////////////////////////////////////////////////////////////////////
void CCOMPort::vCreateCOMEvent(void)
{
   CString EvtName;
   WORD    wCounter;

    for(wCounter = 0; wCounter < 100; wCounter++){

      EvtName.Format("SerComEventRead_%u",wCounter);

      m_xOverCommRead.hEvent = CreateEvent(
        NULL,               // pointer to security attributes
        true,               // flag for manual-reset event: i want manual reset
        false,              // flag for initial state: init in nonsignaled state
        (LPCTSTR)EvtName    // pointer to event-object name
        );
      if(GetLastError() != ERROR_ALREADY_EXISTS){
        break;
      }
    }

    for(wCounter = 0; wCounter < 100; wCounter++){

      EvtName.Format("SerComEventWrite_%u",wCounter);

      m_xOverCommWrite.hEvent = CreateEvent(
        NULL,               // pointer to security attributes
        true,               // flag for manual-reset event: i want manual reset
        false,              // flag for initial state: init in nonsignaled state
        (LPCTSTR)EvtName    // pointer to event-object name
        );
      if(GetLastError() != ERROR_ALREADY_EXISTS){
        break;
      }
    }
}
/////////////////////////////////////////////////////////////////////////////
// GetComPort															   //
/////////////////////////////////////////////////////////////////////////////
CString CCOMPort::GetComPort(void)
{
	return m_strCOMPort;
}
/////////////////////////////////////////////////////////////////////////////
// SetCOMPort															   //
/////////////////////////////////////////////////////////////////////////////
void CCOMPort::SetCOMPort(const CString& strCOMPort)
{
	m_strCOMPort = strCOMPort;
}
/////////////////////////////////////////////////////////////////////////////
// SetCOMSpeed															   //
/////////////////////////////////////////////////////////////////////////////
void CCOMPort::SetCOMSpeed(DWORD dwCOMSpeed)
{
	m_dwCOMSpeed = dwCOMSpeed;
}
/////////////////////////////////////////////////////////////////////////////
// SetCOMParity															   //
/////////////////////////////////////////////////////////////////////////////
void CCOMPort::SetCOMParity(BYTE bCOMParity)
{
	m_bCOMParity = bCOMParity;
}
/////////////////////////////////////////////////////////////////////////////
// SetCOMDataB															   //
/////////////////////////////////////////////////////////////////////////////
void CCOMPort::SetCOMDataB(BYTE bCOMDataB)
{
	m_bCOMByteSize = bCOMDataB;
}
/////////////////////////////////////////////////////////////////////////////
// SetCOMStopB															   //
/////////////////////////////////////////////////////////////////////////////
void CCOMPort::SetCOMStopB(BYTE bCOMStopB)
{
	m_bCOMStopBits = bCOMStopB;
}
/////////////////////////////////////////////////////////////////////////////
// SetErrorText															   //
/////////////////////////////////////////////////////////////////////////////
void CCOMPort::SetErrorText(DWORD dwErrorCode = 0)
{
	DWORD dwError = (dwErrorCode == 0) ? GetLastError() : dwErrorCode;
	LPVOID lpMsgBuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, dwError, 0,(LPTSTR) &lpMsgBuf, 0, NULL);

	m_strErrorText = (LPCTSTR) lpMsgBuf;
	LocalFree(lpMsgBuf);
}
/////////////////////////////////////////////////////////////////////////////
//	ClosePort															   //
/////////////////////////////////////////////////////////////////////////////
void CCOMPort::ClosePort()
{
	if(m_hPort != INVALID_HANDLE_VALUE)
	{
      CloseHandle(m_hPort);
	  m_hPort = INVALID_HANDLE_VALUE;
	}
    
	if(m_xOverCommRead.hEvent!= INVALID_HANDLE_VALUE)
	{
      CloseHandle(m_xOverCommRead.hEvent);
	  m_xOverCommRead.hEvent = INVALID_HANDLE_VALUE;
	}

	if(m_xOverCommWrite.hEvent!=INVALID_HANDLE_VALUE)
	{
      CloseHandle(m_xOverCommWrite.hEvent);
	  m_xOverCommWrite.hEvent = INVALID_HANDLE_VALUE;
    }
}
/////////////////////////////////////////////////////////////////////////////
// OpenPort																   //
/////////////////////////////////////////////////////////////////////////////
BOOL CCOMPort::OpenPort()
{
	BOOL Result = FALSE;
	
	if(m_strCOMPort.IsEmpty())
	{
		m_strErrorText.LoadString(IDS_NO_COM_PORT);
		return FALSE;
	}

    vCreateCOMEvent();

    m_hPort = CreateFile(m_strCOMPort,GENERIC_READ | GENERIC_WRITE, 0,NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
    SetErrorText();

	if(m_hPort == INVALID_HANDLE_VALUE) 
	{
	 goto End;
	}

	if(!SetupComm(m_hPort, SIZE_OF_BUFF, SIZE_OF_BUFF)) goto End;
    PurgeComm(m_hPort,PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);

	COMMTIMEOUTS CommTimeouts;

	CommTimeouts.ReadIntervalTimeout = 0;
	CommTimeouts.ReadTotalTimeoutMultiplier = 0;
	//CommTimeouts.ReadTotalTimeoutConstant = 0;
	CommTimeouts.ReadTotalTimeoutConstant = 10000;
	CommTimeouts.WriteTotalTimeoutMultiplier = 1;
	//CommTimeouts.WriteTotalTimeoutMultiplier = 0;
	CommTimeouts.WriteTotalTimeoutConstant = 1000;
	//CommTimeouts.WriteTotalTimeoutConstant = 0;

	if(!SetCommTimeouts(m_hPort, &CommTimeouts)) goto End;

	DCB dcb;
	dcb.DCBlength = sizeof(dcb);
	if(!GetCommState(m_hPort, &dcb)) goto End;

    ZeroMemory(&dcb,sizeof(dcb));

    dcb.BaudRate = m_dwCOMSpeed;
	dcb.fBinary = TRUE;
	dcb.fParity = FALSE;
	dcb.fOutxCtsFlow = FALSE;
	dcb.fOutxDsrFlow = FALSE;
	dcb.fDtrControl = m_bDTRControl;
	dcb.fDsrSensitivity = FALSE;
	dcb.fTXContinueOnXoff = FALSE;
	dcb.fOutX = m_bOutX;
	dcb.fInX = m_bInX;
	dcb.fErrorChar = FALSE;
	dcb.fNull = FALSE;
	dcb.fRtsControl = m_bRTSControl;
	dcb.fAbortOnError = FALSE;
	dcb.wReserved = 0;
	dcb.XonLim = 0;
	dcb.XoffLim = 0;
	dcb.ByteSize = m_bCOMByteSize;
	dcb.Parity = m_bCOMParity;
	dcb.StopBits = m_bCOMStopBits;
	dcb.XonChar = 0;
	dcb.XoffChar = 0;
	dcb.ErrorChar = 0;
	dcb.EofChar = 0;
	dcb.EvtChar = 0;

	if(!SetCommState(m_hPort, &dcb)) goto End;

	Result = TRUE;

End:
	if(!Result)
	{
		SetErrorText();
		//ClosePort();
	}
	return Result;
}
/////////////////////////////////////////////////////////////////////////////
// SendBreak															   //
/////////////////////////////////////////////////////////////////////////////
BOOL CCOMPort::SendBreak(DWORD dwTime)
{
	BOOL Result = FALSE;

	if(!SetCommBreak(m_hPort)) goto End;
	Sleep(dwTime);
	if(!ClearCommBreak(m_hPort)) goto End;
	Result = TRUE;

End:
	return Result;
}
/////////////////////////////////////////////////////////////////////////////
// Write																   //
/////////////////////////////////////////////////////////////////////////////
BOOL CCOMPort::Write(BYTE * bSendBuffer, DWORD dwBytesToSend)
{
	BOOL Result = FALSE;
	DWORD dwWritten;

	if(!WriteFile(m_hPort,bSendBuffer,dwBytesToSend,&dwWritten, NULL))
	{
		SetErrorText(IDS_ERROR_WRITE);
		TRACE("Error writting");
		goto End;
	}

	if(dwWritten != dwBytesToSend)
	{
		m_strErrorText.LoadString(IDS_ERROR_WRITE);
		goto End;
	}

	Result = TRUE;

End:
	return Result;
}
/////////////////////////////////////////////////////////////////////////////
// SendChar																   //
/////////////////////////////////////////////////////////////////////////////
BOOL CCOMPort::SendChar(BYTE bSendData)
{
//	COMSTAT					xComStat;	
	BOOL					Result = FALSE;
	DWORD					dwWritten;
//	DWORD					zErrorFlags;	
	BOOL					yWriteStat;					

/*
	ResetEvent(m_xOverCommWrite.hEvent);
    ClearCommError(m_hPort,&zErrorFlags,&xComStat);	

	if (zErrorFlags > 0)		
	{							
		return 1;
	}																
*/
	if(m_iSendIndex++>=511) m_iSendIndex=0;
	pc_SendBuffer[m_iSendIndex]=bSendData;

	yWriteStat = WriteFile(m_hPort,&pc_SendBuffer[m_iSendIndex],1,&dwWritten,&m_xOverCommWrite);				

	if (!yWriteStat)													
		{																
			if (GetLastError() == ERROR_IO_PENDING)						
			{															
				return 0;
			}															
			else														
			{															
				return 1;							
			}													
		}

	return 0;	
}
/////////////////////////////////////////////////////////////////////////////
// Read																	   //
/////////////////////////////////////////////////////////////////////////////
BOOL CCOMPort::Read(BYTE * bRecBuffer, DWORD dwBytesToRead)
{
	BOOL Result = FALSE;
	m_dwReaded = 0;
	Result = ReadFile(m_hPort, bRecBuffer, dwBytesToRead, &m_dwReaded, &m_xOverCommRead);
	return Result;
}
/////////////////////////////////////////////////////////////////////////////
//	Start IO															   //
/////////////////////////////////////////////////////////////////////////////
BOOL CCOMPort::yStartIO(HWND hWnd)
{
  BOOL   Result = FALSE;
  m_hSrcWnd = hWnd;

  if(m_hPort == INVALID_HANDLE_VALUE)
  {
	TRACE("Threads start error.\n");
    Result = false;
    return (Result);
  }

  m_yExitFromThread = false;
  Result = true;

  pReadThread=AfxBeginThread( uCheckRecEvent,this );
  hReadThread=pReadThread->m_hThread;

  pWriteThread=AfxBeginThread( uCheckSendEvent,this );
  hWriteThread=pWriteThread->m_hThread;

  return Result;
}
/////////////////////////////////////////////////////////////////////////////
//	ENDIO																   //
/////////////////////////////////////////////////////////////////////////////
void CCOMPort::vEndIO(void)
{

  unsigned long dwExitCode=0;
  m_yExitFromThread = true;

  SetEvent(m_xOverCommRead.hEvent);
  SetEvent(m_xOverCommWrite.hEvent);

  //JOKR
  //Sleep(200);

  if(hReadThread!=NULL)
  if(WaitForSingleObject (hReadThread, 1000)!=WAIT_OBJECT_0)
  {
	TRACE("Read thread error :%d\n",GetLastError());
  }

  if(hWriteThread!=NULL)
  if(WaitForSingleObject (hWriteThread, 1000)!=WAIT_OBJECT_0)
  {
	TRACE("Write thread error :%d\n",GetLastError());
  }
}
/////////////////////////////////////////////////////////////////////////////
//	Send EVENT															   //
/////////////////////////////////////////////////////////////////////////////
UINT uCheckSendEvent( LPVOID pParam )
{
  CCOMPort       *pxComPort;
  pxComPort = (CCOMPort *)pParam;

  while(1)
  {
    if(WaitForSingleObject(pxComPort->m_xOverCommWrite.hEvent,INFINITE) == WAIT_OBJECT_0)
	{
      if(pxComPort->m_yExitFromThread)
	  {  
		// exit from thread
		TRACE("Send THREAD function ended.\n");
		pxComPort->hWriteThread=NULL;
        return (0);
      }
	  ResetEvent(pxComPort->m_xOverCommWrite.hEvent);
  	  PostMessage(pxComPort->m_hSrcWnd,ID_IO_SND_EVENT,0,0);
    }    // end WaitForSingleObject
  }    // end while
}    // end thread

/////////////////////////////////////////////////////////////////////////////
//	Receive EVENT														   //
/////////////////////////////////////////////////////////////////////////////
UINT uCheckRecEvent( LPVOID pParam )
{

  CCOMPort       *pxComPort;
  BOOL           yRes;
  pxComPort = (CCOMPort *)pParam;

  while(1)
  {
    pxComPort->Read(pxComPort->m_bReadBuffer,1);
    if(WaitForSingleObject(pxComPort->m_xOverCommRead.hEvent,INFINITE) == WAIT_OBJECT_0)
	{
      if(pxComPort->m_yExitFromThread)
	  {  // exit from thread
		TRACE("Receive THREAD function ended.\n");
		pxComPort->hReadThread=NULL;
		return (0);
      }
      yRes = GetOverlappedResult(pxComPort->m_hPort,&pxComPort->m_xOverCommRead,&pxComPort->m_dwReaded,FALSE);
	  
      if(!yRes)
	  {
        pxComPort->SetErrorText(yRes);
      }

      if(pxComPort->m_dwReaded == 1)
	  {
        PostMessage(pxComPort->m_hSrcWnd,ID_IO_REC_EVENT,pxComPort->m_bReadBuffer[0],0);
      }
    }    // end WaitForSingleObject
  }    // end while
}    // end thread
