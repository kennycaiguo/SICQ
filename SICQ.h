//! \file SICQ.h Header for SICQ.cpp

#pragma once
#include <shlwapi.h>
#pragma comment(lib,"shlwapi.lib")

#include "Utils.h"
#include "Net.h"
#include "ICQPacket.h"
#include "SICQ_define.h"


//! A class for OSCAR protocol (ICQ/AIM)
/*!
An application or DLL is required to perform a successful WSAStartup call before it can use SICQ
\code
WORD wVersionRequested;
WSADATA wsaData;
int err;

wVersionRequested = MAKEWORD(2, 2);

err = WSAStartup(wVersionRequested, &wsaData);
if (err != 0) {                                
	printf("WSAStartup failed with error: %d\n", err);
	return 1;
}
\endcode
When it has completed the use of SICQ, the application or DLL must call WSACleanup to deregister 
itself from a Windows Sockets implementation and allow the implementation to free any resources 
allocated on behalf of the application or DLL.
\code
WSACleanup();
\endcode

\sa _LoadWS, _UnloadWS
*/

class SICQ: private ICQPacket
{
private:
	int nError;
	HWND hEventWnd;
	TCHAR szUIN[20];
	TCHAR szPassword[20];
	TCHAR szServerIP[20];
	int nServerPort;
	SOCKET sock;
	int nSequence;
	int nStatus;

	FOODGROUPS FoodGroups;

	HWND hMainWnd;

	void SequenceIncrement();

	// Start
	bool Start();
	// Stop
	bool Stop();
	// ICQ Login
	bool ICQLoginPlain();
	// ICQ Login MD5
	bool ICQLoginMD5();

	void ICQBOSServerConnect(TCHAR *pszBOSServerIPAndPort,char *pCookies,int nCookiesSize);

	// CALLBACK function
	static LRESULT CALLBACK SocketProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	SICQ(HWND hMainWnd);
	~SICQ(void);

	// Get Last Error
	TCHAR *GetErrorString();
	
	// Login
	bool Login(TCHAR *pszServerIP,int nServerPort,TCHAR *pszUIN,TCHAR *pszPassword);
	
};



