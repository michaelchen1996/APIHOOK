#pragma once

#include "SendLog.h"

#ifndef __REG_API__
#define __REG_API__


LONG WINAPI MyRegOpenKeyExW(
	_In_     HKEY    hKey,
	_In_opt_ LPCWSTR lpSubKey,
	_In_     DWORD   ulOptions,
	_In_     REGSAM  samDesired,
	_Out_    PHKEY   phkResult
);
typedef LONG(WINAPI *ptrRegOpenKeyExW)(
	_In_     HKEY    hKey,
	_In_opt_ LPCWSTR lpSubKey,
	_In_     DWORD   ulOptions,
	_In_     REGSAM  samDesired,
	_Out_    PHKEY   phkResult
	);

LONG WINAPI MyRegOpenKeyW(
	_In_     HKEY    hKey,
	_In_opt_ LPCWSTR lpSubKey,
	_Out_    PHKEY   phkResult
);
typedef LONG(WINAPI *ptrRegOpenKeyW)(
	_In_     HKEY    hKey,
	_In_opt_ LPCWSTR lpSubKey,
	_Out_    PHKEY   phkResult
	);

LONG WINAPI MyRegCreateKeyExW(
	_In_       HKEY                  hKey,
	_In_       LPCWSTR               lpSubKey,
	_Reserved_ DWORD                 Reserved,
	_In_opt_   LPTSTR                lpClass,
	_In_       DWORD                 dwOptions,
	_In_       REGSAM                samDesired,
	_In_opt_   LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	_Out_      PHKEY                 phkResult,
	_Out_opt_  LPDWORD               lpdwDisposition
);
typedef LONG(WINAPI *ptrRegCreateKeyExW)(
	_In_       HKEY                  hKey,
	_In_       LPCWSTR               lpSubKey,
	_Reserved_ DWORD                 Reserved,
	_In_opt_   LPTSTR                lpClass,
	_In_       DWORD                 dwOptions,
	_In_       REGSAM                samDesired,
	_In_opt_   LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	_Out_      PHKEY                 phkResult,
	_Out_opt_  LPDWORD               lpdwDisposition
	);

LONG WINAPI MyRegCreateKeyW(
	_In_     HKEY    hKey,
	_In_opt_ LPCWSTR lpSubKey,
	_Out_    PHKEY   phkResult
);
typedef LONG(WINAPI *ptrRegCreateKeyW)(
	_In_     HKEY    hKey,
	_In_opt_ LPCWSTR lpSubKey,
	_Out_    PHKEY   phkResult
	);

LONG WINAPI MyRegQueryValueExW(
	_In_        HKEY    hKey,
	_In_opt_    LPCWSTR lpValueName,
	_Reserved_  LPDWORD lpReserved,
	_Out_opt_   LPDWORD lpType,
	_Out_opt_   LPBYTE  lpData,
	_Inout_opt_ LPDWORD lpcbData
);
typedef LONG(WINAPI *ptrRegQueryValueExW)(
	_In_        HKEY    hKey,
	_In_opt_    LPCWSTR lpValueName,
	_Reserved_  LPDWORD lpReserved,
	_Out_opt_   LPDWORD lpType,
	_Out_opt_   LPBYTE  lpData,
	_Inout_opt_ LPDWORD lpcbData
	);

LONG WINAPI MyRegQueryValueW(
	_In_        HKEY    hKey,
	_In_opt_    LPCWSTR lpSubKey,
	_Out_opt_   LPTSTR  lpValue,
	_Inout_opt_ PLONG   lpcbValue
);
typedef LONG(WINAPI *ptrRegQueryValueW)(
	_In_        HKEY    hKey,
	_In_opt_    LPCWSTR lpSubKey,
	_Out_opt_   LPTSTR  lpValue,
	_Inout_opt_ PLONG   lpcbValue
	);

LONG WINAPI MyRegSetValueExW(
	_In_             HKEY    hKey,
	_In_opt_         LPCWSTR lpValueName,
	_Reserved_       DWORD   Reserved,
	_In_             DWORD   dwType,
	_In_       const BYTE    *lpData,
	_In_             DWORD   cbData
);
typedef LONG(WINAPI *ptrRegSetValueExW)(
	_In_             HKEY    hKey,
	_In_opt_         LPCWSTR lpValueName,
	_Reserved_       DWORD   Reserved,
	_In_             DWORD   dwType,
	_In_       const BYTE    *lpData,
	_In_             DWORD   cbData
	);

LONG WINAPI MyRegSetValueW(
	_In_     HKEY    hKey,
	_In_opt_ LPCWSTR lpSubKey,
	_In_     DWORD   dwType,
	_In_     LPCWSTR lpData,
	_In_     DWORD   cbData
);
typedef LONG(WINAPI *ptrRegSetValueW)(
	_In_     HKEY    hKey,
	_In_opt_ LPCWSTR lpSubKey,
	_In_     DWORD   dwType,
	_In_     LPCWSTR lpData,
	_In_     DWORD   cbData
	);

LONG WINAPI MyRegDeleteKeyExW(
	_In_       HKEY    hKey,
	_In_       LPCWSTR lpSubKey,
	_In_       REGSAM  samDesired,
	_Reserved_ DWORD   Reserved
);
typedef LONG(WINAPI *ptrRegDeleteKeyExW)(
	_In_       HKEY    hKey,
	_In_       LPCWSTR lpSubKey,
	_In_       REGSAM  samDesired,
	_Reserved_ DWORD   Reserved
	);

LONG WINAPI MyRegDeleteKeyW(
	_In_ HKEY    hKey,
	_In_ LPCWSTR lpSubKey
);
typedef LONG(WINAPI *ptrRegDeleteKeyW)(
	_In_ HKEY    hKey,
	_In_ LPCWSTR lpSubKey
	);

LONG WINAPI MyRegSetKeySecurity(
	_In_ HKEY                 hKey,
	_In_ SECURITY_INFORMATION SecurityInformation,
	_In_ PSECURITY_DESCRIPTOR pSecurityDescriptor
);
typedef LONG(WINAPI *ptrRegSetKeySecurity)(
	_In_ HKEY                 hKey,
	_In_ SECURITY_INFORMATION SecurityInformation,
	_In_ PSECURITY_DESCRIPTOR pSecurityDescriptor
	);

LONG WINAPI MyRegRestoreKeyW(
	_In_ HKEY    hKey,
	_In_ LPCWSTR lpFile,
	_In_ DWORD   dwFlags
);
typedef LONG(WINAPI *ptrRegRestoreKeyW)(
	_In_ HKEY    hKey,
	_In_ LPCWSTR lpFile,
	_In_ DWORD   dwFlags
	);

LONG WINAPI MyRegReplaceKeyW(
	_In_     HKEY    hKey,
	_In_opt_ LPCWSTR lpSubKey,
	_In_     LPCWSTR lpNewFile,
	_In_     LPCWSTR lpOldFile
);
typedef LONG(WINAPI *ptrRegReplaceKeyW)(
	_In_     HKEY    hKey,
	_In_opt_ LPCWSTR lpSubKey,
	_In_     LPCWSTR lpNewFile,
	_In_     LPCWSTR lpOldFile
	);

LONG WINAPI MyRegLoadKeyW(
	_In_     HKEY    hKey,
	_In_opt_ LPCWSTR lpSubKey,
	_In_     LPCWSTR lpFile
);
typedef LONG(WINAPI *ptrRegLoadKeyW)(
	_In_     HKEY    hKey,
	_In_opt_ LPCWSTR lpSubKey,
	_In_     LPCWSTR lpFile
	);

LONG WINAPI MyRegUnLoadKey(
	_In_     HKEY    hKey,
	_In_opt_ LPCWSTR lpSubKey
);
typedef LONG(WINAPI *ptrRegUnLoadKey)(
	_In_     HKEY    hKey,
	_In_opt_ LPCWSTR lpSubKey
	);


extern	  ptrRegOpenKeyExW realRegOpenKeyExW;
extern	  ptrRegOpenKeyW realRegOpenKeyW;
extern	  ptrRegCreateKeyExW realRegCreateKeyExW;
extern	  ptrRegCreateKeyW realRegCreateKeyW;
extern	  ptrRegQueryValueExW realRegQueryValueExW;
extern	  ptrRegQueryValueW realRegQueryValueW;
extern	  ptrRegSetValueExW realRegSetValueExW;
extern	  ptrRegSetValueW realRegSetValueW;
extern	  ptrRegDeleteKeyExW realRegDeleteKeyExW;
extern	  ptrRegDeleteKeyW realRegDeleteKeyW;
extern	  ptrRegSetKeySecurity realRegSetKeySecurity;
extern	  ptrRegRestoreKeyW realRegRestoreKeyW;
extern	  ptrRegReplaceKeyW realRegReplaceKeyW;
extern	  ptrRegLoadKeyW realRegLoadKeyW;
extern	  ptrRegUnLoadKey realRegUnLoadKey;


#endif // !__FILE_API__