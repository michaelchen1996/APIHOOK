#pragma once

#include "SendLog.h"

#ifndef __NET_API__
#define __NET_API__


SOCKET WINAPI Myaccept(
	_In_    SOCKET          s,
	_Out_   struct sockaddr *addr,
	_Inout_ int             *addrlen
);
typedef SOCKET(WINAPI *ptraccept)(
	_In_    SOCKET          s,
	_Out_   struct sockaddr *addr,
	_Inout_ int             *addrlen
	);

int WINAPI Mysend(
	_In_       SOCKET s,
	_In_ const char   *buf,
	_In_       int    len,
	_In_       int    flags
);
typedef int (WINAPI *ptrsend)(
	_In_       SOCKET s,
	_In_ const char   *buf,
	_In_       int    len,
	_In_       int    flags
	);

int WINAPI Mybind(
	_In_ SOCKET                s,
	_In_ const struct sockaddr *name,
	_In_ int                   namelen
);
typedef int (WINAPI *ptrbind)(
	_In_ SOCKET                s,
	_In_ const struct sockaddr *name,
	_In_ int                   namelen
	);

int WINAPI Myconnect(
	_In_ SOCKET                s,
	_In_ const struct sockaddr *name,
	_In_ int                   namelen
);
typedef int (WINAPI *ptrconnect)(
	_In_ SOCKET                s,
	_In_ const struct sockaddr *name,
	_In_ int                   namelen
	);

BOOL WINAPI MyConnectNamedPipe(
	_In_        HANDLE       hNamedPipe,
	_Inout_opt_ LPOVERLAPPED lpOverlapped
);
typedef BOOL(WINAPI *ptrConnectNamedPipe)(
	_In_        HANDLE       hNamedPipe,
	_Inout_opt_ LPOVERLAPPED lpOverlapped
	);

int WINAPI Mygethostname(
	_Out_ char *name,
	_In_  int  namelen
);
typedef int (WINAPI *ptrgethostname)(
	_Out_ char *name,
	_In_  int  namelen
	);

unsigned long WINAPI Myinet_addr(
	_In_ const char *cp
);
typedef unsigned long (WINAPI *ptrinet_addr)(
	_In_ const char *cp
	);

BOOL WINAPI MyInternetReadFile(
	_In_  HINTERNET hFile,
	_Out_ LPVOID    lpBuffer,
	_In_  DWORD     dwNumberOfBytesToRead,
	_Out_ LPDWORD   lpdwNumberOfBytesRead
);
typedef BOOL(WINAPI *ptrInternetReadFile)(
	_In_  HINTERNET hFile,
	_Out_ LPVOID    lpBuffer,
	_In_  DWORD     dwNumberOfBytesToRead,
	_Out_ LPDWORD   lpdwNumberOfBytesRead
	);

BOOL WINAPI MyInternetWriteFile(
	_In_  HINTERNET hFile,
	_In_  LPCVOID   lpBuffer,
	_In_  DWORD     dwNumberOfBytesToWrite,
	_Out_ LPDWORD   lpdwNumberOfBytesWritten
);
typedef BOOL(WINAPI *ptrInternetWriteFile)(
	_In_  HINTERNET hFile,
	_In_  LPCVOID   lpBuffer,
	_In_  DWORD     dwNumberOfBytesToWrite,
	_Out_ LPDWORD   lpdwNumberOfBytesWritten
	);

NET_API_STATUS WINAPI MyNetShareEnum(
	_In_    LPWSTR  servername,
	_In_    DWORD   level,
	_Out_   LPBYTE  *bufptr,
	_In_    DWORD   prefmaxlen,
	_Out_   LPDWORD entriesread,
	_Out_   LPDWORD totalentries,
	_Inout_ LPDWORD resume_handle
);
typedef NET_API_STATUS(WINAPI *ptrNetShareEnum)(
	_In_    LPWSTR  servername,
	_In_    DWORD   level,
	_Out_   LPBYTE  *bufptr,
	_In_    DWORD   prefmaxlen,
	_Out_   LPDWORD entriesread,
	_Out_   LPDWORD totalentries,
	_Inout_ LPDWORD resume_handle
	);

int WINAPI Myrecv(
	SOCKET s,
	char FAR* buf,
	int len,
	int flags
);
typedef int (WINAPI *ptrrecv)(
	SOCKET s,
	char FAR* buf,
	int len,
	int flags
	);

int WINAPI MyWSAStartup(
	_In_  WORD      wVersionRequested,
	_Out_ LPWSADATA lpWSAData
);
typedef int (WINAPI *ptrWSAStartup)(
	_In_  WORD      wVersionRequested,
	_Out_ LPWSADATA lpWSAData
	);

HINTERNET WINAPI MyInternetOpenW(
	_In_ LPCWSTR lpszAgent,
	_In_ DWORD   dwAccessType,
	_In_ LPCWSTR lpszProxy,
	_In_ LPCWSTR lpszProxyBypass,
	_In_ DWORD   dwFlags
);
typedef HINTERNET(WINAPI *ptrInternetOpenW)(
	_In_ LPCWSTR lpszAgent,
	_In_ DWORD   dwAccessType,
	_In_ LPCWSTR lpszProxy,
	_In_ LPCWSTR lpszProxyBypass,
	_In_ DWORD   dwFlags
	);

HINTERNET WINAPI MyInternetOpenUrlW(
	_In_ HINTERNET hInternet,
	_In_ LPCWSTR   lpszUrl,
	_In_ LPCWSTR   lpszHeaders,
	_In_ DWORD     dwHeadersLength,
	_In_ DWORD     dwFlags,
	_In_ DWORD_PTR dwContext
);
typedef HINTERNET(WINAPI *ptrInternetOpenUrlW)(
	_In_ HINTERNET hInternet,
	_In_ LPCWSTR   lpszUrl,
	_In_ LPCWSTR   lpszHeaders,
	_In_ DWORD     dwHeadersLength,
	_In_ DWORD     dwFlags,
	_In_ DWORD_PTR dwContext
	);

HRESULT WINAPI MyURLDownloadToFileW(
	LPUNKNOWN            pCaller,
	LPCWSTR              szURL,
	LPCWSTR              szFileName,
	_Reserved_ DWORD                dwReserved,
	LPBINDSTATUSCALLBACK lpfnCB
);
typedef HRESULT(WINAPI *ptrURLDownloadToFileW)(
	LPUNKNOWN            pCaller,
	LPCWSTR              szURL,
	LPCWSTR              szFileName,
	_Reserved_ DWORD                dwReserved,
	LPBINDSTATUSCALLBACK lpfnCB
	);

BOOL WINAPI MyFtpPutFileW(
	_In_ HINTERNET hConnect,
	_In_ LPCWSTR   lpszLocalFile,
	_In_ LPCWSTR   lpszNewRemoteFile,
	_In_ DWORD     dwFlags,
	_In_ DWORD_PTR dwContext
);
typedef BOOL(WINAPI *ptrFtpPutFileW)(
	_In_ HINTERNET hConnect,
	_In_ LPCWSTR   lpszLocalFile,
	_In_ LPCWSTR   lpszNewRemoteFile,
	_In_ DWORD     dwFlags,
	_In_ DWORD_PTR dwContext
	);

BOOL WINAPI MyHttpSendRequestW(
	_In_ HINTERNET hRequest,
	_In_ LPCWSTR   lpszHeaders,
	_In_ DWORD     dwHeadersLength,
	_In_ LPVOID    lpOptional,
	_In_ DWORD     dwOptionalLength
);
typedef BOOL(WINAPI *ptrHttpSendRequestW)(
	_In_ HINTERNET hRequest,
	_In_ LPCWSTR   lpszHeaders,
	_In_ DWORD     dwHeadersLength,
	_In_ LPVOID    lpOptional,
	_In_ DWORD     dwOptionalLength
	);

BOOL WINAPI MyHttpSendRequestExW(
	_In_  HINTERNET          hRequest,
	_In_  LPINTERNET_BUFFERS lpBuffersIn,
	_Out_ LPINTERNET_BUFFERS lpBuffersOut,
	_In_  DWORD              dwFlags,
	_In_  DWORD_PTR          dwContext
);
typedef BOOL(WINAPI *ptrHttpSendRequestExW)(
	_In_  HINTERNET          hRequest,
	_In_  LPINTERNET_BUFFERS lpBuffersIn,
	_Out_ LPINTERNET_BUFFERS lpBuffersOut,
	_In_  DWORD              dwFlags,
	_In_  DWORD_PTR          dwContext
	);


HINTERNET WINAPI MyHttpOpenRequestW(
	_In_ HINTERNET hConnect,
	_In_ LPCWSTR   lpszVerb,
	_In_ LPCWSTR   lpszObjectName,
	_In_ LPCWSTR   lpszVersion,
	_In_ LPCWSTR   lpszReferer,
	_In_ LPCWSTR   *lplpszAcceptTypes,
	_In_ DWORD     dwFlags,
	_In_ DWORD_PTR dwContext
);
typedef HINTERNET(WINAPI *ptrHttpOpenRequestW)(
	_In_ HINTERNET hConnect,
	_In_ LPCWSTR   lpszVerb,
	_In_ LPCWSTR   lpszObjectName,
	_In_ LPCWSTR   lpszVersion,
	_In_ LPCWSTR   lpszReferer,
	_In_ LPCWSTR   *lplpszAcceptTypes,
	_In_ DWORD     dwFlags,
	_In_ DWORD_PTR dwContext
	);

HINTERNET WINAPI MyInternetConnectW(
	_In_ HINTERNET     hInternet,
	_In_ LPCWSTR       lpszServerName,
	_In_ INTERNET_PORT nServerPort,
	_In_ LPCWSTR       lpszUsername,
	_In_ LPCWSTR       lpszPassword,
	_In_ DWORD         dwService,
	_In_ DWORD         dwFlags,
	_In_ DWORD_PTR     dwContext
);
typedef HINTERNET(WINAPI *ptrInternetConnectW)(
	_In_ HINTERNET     hInternet,
	_In_ LPCWSTR       lpszServerName,
	_In_ INTERNET_PORT nServerPort,
	_In_ LPCWSTR       lpszUsername,
	_In_ LPCWSTR       lpszPassword,
	_In_ DWORD         dwService,
	_In_ DWORD         dwFlags,
	_In_ DWORD_PTR     dwContext
	);


int WINAPI Mylisten(
	_In_ SOCKET s,
	_In_ int    backlog
);
typedef int (WINAPI *ptrlisten)(
	_In_ SOCKET s,
	_In_ int    backlog
	);

HINTERNET WINAPI MyInternetOpenUrlA(
	_In_ HINTERNET hInternet, 
	_In_ LPCSTR lpszUrl, 
	_In_reads_opt_(dwHeadersLength) LPCSTR lpszHeaders, 
	_In_ DWORD dwHeadersLength, _In_ DWORD dwFlags, 
	_In_opt_ DWORD_PTR dwContext
);
typedef HINTERNET(WINAPI *ptrInternetOpenUrlA)(
	_In_ HINTERNET hInternet, 
	_In_ LPCSTR lpszUrl, 
	_In_reads_opt_(dwHeadersLength) LPCSTR lpszHeaders, 
	_In_ DWORD dwHeadersLength, 
	_In_ DWORD dwFlags, 
	_In_opt_ DWORD_PTR dwContext
	);

HINTERNET WINAPI MyHttpOpenRequestA(
	_In_ HINTERNET hConnect, 
	_In_opt_ LPCSTR lpszVerb, 
	_In_opt_ LPCSTR lpszObjectName, 
	_In_opt_ LPCSTR lpszVersion, 
	_In_opt_ LPCSTR lpszReferrer, 
	_In_opt_z_ LPCSTR FAR * lplpszAcceptTypes, 
	_In_ DWORD dwFlags, 
	_In_opt_ DWORD_PTR dwContext);
typedef HINTERNET(WINAPI *ptrHttpOpenRequestA)(
	_In_ HINTERNET hConnect,
	_In_opt_ LPCSTR lpszVerb, 
	_In_opt_ LPCSTR lpszObjectName,
	_In_opt_ LPCSTR lpszVersion, 
	_In_opt_ LPCSTR lpszReferrer,
	_In_opt_z_ LPCSTR FAR * lplpszAcceptTypes,
	_In_ DWORD dwFlags,
	_In_opt_ DWORD_PTR dwContext
	);

extern	  ptraccept realaccept;
extern	  ptrsend realsend;
extern	  ptrbind realbind;
extern	  ptrconnect realconnect;
extern	  ptrConnectNamedPipe realConnectNamedPipe;
extern	  ptrgethostname realgethostname;
extern	  ptrinet_addr realinet_addr;
extern	  ptrInternetReadFile realInternetReadFile;
extern	  ptrInternetWriteFile realInternetWriteFile;
extern	  ptrNetShareEnum realNetShareEnum;
extern	  ptrrecv realrecv;
extern	  ptrWSAStartup realWSAStartup;
extern	  ptrInternetOpenW realInternetOpenW;
extern	  ptrInternetOpenUrlW realInternetOpenUrlW;
extern	  ptrURLDownloadToFileW realURLDownloadToFileW;
extern	  ptrFtpPutFileW realFtpPutFileW;
extern	  ptrHttpSendRequestW realHttpSendRequestW;
extern	  ptrHttpSendRequestExW realHttpSendRequestExW;
extern	  ptrHttpOpenRequestW realHttpOpenRequestW;
extern	  ptrInternetConnectW realInternetConnectW;
extern	  ptrlisten reallisten;
extern    ptrInternetOpenUrlA realInternetOpenUrlA;
extern    ptrHttpOpenRequestA realHttpOpenRequestA;


#endif // !__NET_API__