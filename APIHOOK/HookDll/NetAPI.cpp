#include "stdafx.h"
#include "NetAPI.h"


SOCKET WINAPI Myaccept(
	_In_    SOCKET          s,
	_Out_   struct sockaddr *addr,
	_Inout_ int             *addrlen
)
{

	return (realaccept)(s, addr, addrlen);
}

int WINAPI Mysend(
	_In_       SOCKET s,
	_In_ const char   *buf,
	_In_       int    len,
	_In_       int    flags
)
{

	return (realsend)(s, buf, len, flags);
}

int WINAPI Mybind(
	_In_ SOCKET                s,
	_In_ const struct sockaddr *name,
	_In_ int                   namelen
)
{

	return (realbind)(s, name, namelen);
}

int WINAPI Myconnect(
	_In_ SOCKET                s,
	_In_ const struct sockaddr *name,
	_In_ int                   namelen
)
{

	return (realconnect)(s, name, namelen);
}

BOOL WINAPI MyConnectNamedPipe(
	_In_        HANDLE       hNamedPipe,
	_Inout_opt_ LPOVERLAPPED lpOverlapped
)
{

	return (realConnectNamedPipe)(hNamedPipe, lpOverlapped);
}

int WINAPI Mygethostname(
	_Out_ char *name,
	_In_  int  namelen
)
{

	return (realgethostname)(name, namelen);
}

unsigned long WINAPI Myinet_addr(
	_In_ const char *cp
)
{

	return (realinet_addr)(cp);
}

BOOL WINAPI MyInternetReadFile(
	_In_  HINTERNET hFile,
	_Out_ LPVOID    lpBuffer,
	_In_  DWORD     dwNumberOfBytesToRead,
	_Out_ LPDWORD   lpdwNumberOfBytesRead
)
{

	return (realInternetReadFile)(hFile, lpBuffer, dwNumberOfBytesToRead, lpdwNumberOfBytesRead);
}

BOOL WINAPI MyInternetWriteFile(
	_In_  HINTERNET hFile,
	_In_  LPCVOID   lpBuffer,
	_In_  DWORD     dwNumberOfBytesToWrite,
	_Out_ LPDWORD   lpdwNumberOfBytesWritten
)
{

	return (realInternetWriteFile)(hFile, lpBuffer, dwNumberOfBytesToWrite, lpdwNumberOfBytesWritten);
}

NET_API_STATUS WINAPI MyNetShareEnum(
	_In_    LPWSTR  servername,
	_In_    DWORD   level,
	_Out_   LPBYTE  *bufptr,
	_In_    DWORD   prefmaxlen,
	_Out_   LPDWORD entriesread,
	_Out_   LPDWORD totalentries,
	_Inout_ LPDWORD resume_handle
)
{

	return (realNetShareEnum)(servername, level, bufptr, prefmaxlen, entriesread, totalentries, resume_handle);
}

int WINAPI Myrecv(
	SOCKET s,
	char FAR* buf,
	int len,
	int flags
)
{

	return (realrecv)(s, buf, len, flags);
}

int WINAPI MyWSAStartup(
	_In_  WORD      wVersionRequested,
	_Out_ LPWSADATA lpWSAData
)
{
	int res = 0;
	res = (realWSAStartup)(wVersionRequested, lpWSAData);

	return res;
}

HINTERNET WINAPI MyInternetOpenW(
	_In_ LPCWSTR lpszAgent,
	_In_ DWORD   dwAccessType,
	_In_ LPCWSTR lpszProxy,
	_In_ LPCWSTR lpszProxyBypass,
	_In_ DWORD   dwFlags
)
{

	return (realInternetOpenW)(lpszAgent, dwAccessType, lpszProxy, lpszProxyBypass, dwFlags);
}

HINTERNET WINAPI MyInternetOpenUrlW(
	_In_ HINTERNET hInternet,
	_In_ LPCWSTR   lpszUrl,
	_In_ LPCWSTR   lpszHeaders,
	_In_ DWORD     dwHeadersLength,
	_In_ DWORD     dwFlags,
	_In_ DWORD_PTR dwContext
)
{

	return (realInternetOpenUrlW)(hInternet, lpszUrl, lpszHeaders, dwHeadersLength, dwFlags, dwContext);
}

HRESULT WINAPI MyURLDownloadToFileW(
	LPUNKNOWN            pCaller,
	LPCWSTR              szURL,
	LPCWSTR              szFileName,
	_Reserved_ DWORD                dwReserved,
	LPBINDSTATUSCALLBACK lpfnCB
)
{

	return (realURLDownloadToFileW)(pCaller, szURL, szFileName, dwReserved, lpfnCB);
}

BOOL WINAPI MyFtpPutFileW(
	_In_ HINTERNET hConnect,
	_In_ LPCWSTR   lpszLocalFile,
	_In_ LPCWSTR   lpszNewRemoteFile,
	_In_ DWORD     dwFlags,
	_In_ DWORD_PTR dwContext
)
{

	return (realFtpPutFileW)(hConnect, lpszLocalFile, lpszNewRemoteFile, dwFlags, dwContext);
}

BOOL WINAPI MyHttpSendRequestW(
	_In_ HINTERNET hRequest,
	_In_ LPCWSTR   lpszHeaders,
	_In_ DWORD     dwHeadersLength,
	_In_ LPVOID    lpOptional,
	_In_ DWORD     dwOptionalLength
)
{

	return (realHttpSendRequestW)(hRequest, lpszHeaders, dwHeadersLength, lpOptional, dwOptionalLength);
}

BOOL WINAPI MyHttpSendRequestExW(
	_In_  HINTERNET          hRequest,
	_In_  LPINTERNET_BUFFERS lpBuffersIn,
	_Out_ LPINTERNET_BUFFERS lpBuffersOut,
	_In_  DWORD              dwFlags,
	_In_  DWORD_PTR          dwContext
)
{

	return (realHttpSendRequestExW)(hRequest, lpBuffersIn, lpBuffersOut, dwFlags, dwContext);
}

HINTERNET WINAPI MyHttpOpenRequestW(
	_In_ HINTERNET hConnect,
	_In_ LPCWSTR   lpszVerb,
	_In_ LPCWSTR   lpszObjectName,
	_In_ LPCWSTR   lpszVersion,
	_In_ LPCWSTR   lpszReferer,
	_In_ LPCWSTR   *lplpszAcceptTypes,
	_In_ DWORD     dwFlags,
	_In_ DWORD_PTR dwContext
)
{

	return (realHttpOpenRequestW)(hConnect, lpszVerb, lpszObjectName, lpszVersion, lpszReferer, lplpszAcceptTypes, dwFlags, dwContext);
}

HINTERNET WINAPI MyInternetConnectW(
	_In_ HINTERNET     hInternet,
	_In_ LPCWSTR       lpszServerName,
	_In_ INTERNET_PORT nServerPort,
	_In_ LPCWSTR       lpszUsername,
	_In_ LPCWSTR       lpszPassword,
	_In_ DWORD         dwService,
	_In_ DWORD         dwFlags,
	_In_ DWORD_PTR     dwContext
)
{

	return (realInternetConnectW)(hInternet, lpszServerName, nServerPort, lpszUsername, lpszPassword, dwService, dwFlags, dwContext);
}

int WINAPI Mylisten(
	_In_ SOCKET s,
	_In_ int    backlog
)
{

	return (reallisten)(s, backlog);
}

HINTERNET WINAPI MyInternetOpenUrlA(
	_In_ HINTERNET hInternet, 
	_In_ LPCSTR lpszUrl, 
	_In_reads_opt_(dwHeadersLength) LPCSTR lpszHeaders, 
	_In_ DWORD dwHeadersLength, 
	_In_ DWORD dwFlags, 
	_In_opt_ DWORD_PTR dwContext
) 
{

	return (realInternetOpenUrlA)(hInternet, lpszUrl, lpszHeaders, dwHeadersLength, dwFlags, dwContext);
}

HINTERNET WINAPI MyHttpOpenRequestA(
	_In_ HINTERNET hConnect, 
	_In_opt_ LPCSTR lpszVerb, 
	_In_opt_ LPCSTR lpszObjectName,
	_In_opt_ LPCSTR lpszVersion, 
	_In_opt_ LPCSTR lpszReferrer,
	_In_opt_z_ LPCSTR FAR * lplpszAcceptTypes, 
	_In_ DWORD dwFlags, 
	_In_opt_ DWORD_PTR dwContext
) 
{

	return (realHttpOpenRequestA)(hConnect, lpszVerb, lpszObjectName, lpszVersion, lpszReferrer, lplpszAcceptTypes, dwFlags, dwContext);
}