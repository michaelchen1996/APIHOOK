#include "stdafx.h"
#include "RegAPI.h"


LONG WINAPI MyRegOpenKeyExW(
	_In_     HKEY    hKey,
	_In_opt_ LPCWSTR lpSubKey,
	_In_     DWORD   ulOptions,
	_In_     REGSAM  samDesired,
	_Out_    PHKEY   phkResult
)
{

	return (realRegOpenKeyExW)(hKey, lpSubKey, ulOptions, samDesired, phkResult);
}

LONG WINAPI MyRegOpenKeyW(
	_In_     HKEY    hKey,
	_In_opt_ LPCWSTR lpSubKey,
	_Out_    PHKEY   phkResult
)
{

	return (realRegOpenKeyW)(hKey, lpSubKey, phkResult);
}

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
)
{

	return (realRegCreateKeyExW)(hKey, lpSubKey, Reserved, lpClass, dwOptions, samDesired, lpSecurityAttributes, phkResult, lpdwDisposition);
}

LONG WINAPI MyRegCreateKeyW(
	_In_     HKEY    hKey,
	_In_opt_ LPCWSTR lpSubKey,
	_Out_    PHKEY   phkResult
)
{

	return (realRegCreateKeyW)(hKey, lpSubKey, phkResult);
}

LONG WINAPI MyRegQueryValueExW(
	_In_        HKEY    hKey,
	_In_opt_    LPCWSTR lpValueName,
	_Reserved_  LPDWORD lpReserved,
	_Out_opt_   LPDWORD lpType,
	_Out_opt_   LPBYTE  lpData,
	_Inout_opt_ LPDWORD lpcbData
)
{

	return (realRegQueryValueExW)(hKey, lpValueName, lpReserved, lpType, lpData, lpcbData);
}

LONG WINAPI MyRegQueryValueW(
	_In_        HKEY    hKey,
	_In_opt_    LPCWSTR lpSubKey,
	_Out_opt_   LPWSTR  lpValue,
	_Inout_opt_ PLONG   lpcbValue
)
{

	return (realRegQueryValueW)(hKey, lpSubKey, lpValue, lpcbValue);
}

LONG WINAPI MyRegSetValueExW(
	_In_             HKEY    hKey,
	_In_opt_         LPCWSTR lpValueName,
	_Reserved_       DWORD   Reserved,
	_In_             DWORD   dwType,
	_In_       const BYTE    *lpData,
	_In_             DWORD   cbData
)
{

	if (cbData != 0 && lpData != NULL)
	{
		if (dwType == REG_SZ)
		{

		}
		if (dwType == REG_DWORD || dwType == REG_DWORD_LITTLE_ENDIAN)
		{
			UINT a = 0;
			UINT b, c, d, e;
			b = lpData[0];
			c = lpData[1];
			d = lpData[2];
			e = lpData[3];
			a = b & 0xff;
			a |= ((c << 8) & 0xff00);
			a |= ((d << 16) & 0xff0000);
			a |= ((e << 24) & 0xff000000);
			//a=e<<24 + d<<16 + c<<8 + b;
			char p[256];
		}
		if (dwType == REG_DWORD_BIG_ENDIAN)
		{
			UINT a = 0;
			UINT b, c, d, e;
			b = lpData[0];
			c = lpData[1];
			d = lpData[2];
			e = lpData[3];
			a = e & 0xff;
			a |= ((d << 8) & 0xff00);
			a |= ((c << 16) & 0xff0000);
			a |= ((b << 24) & 0xff000000);
			//a=e<<24 + d<<16 + c<<8 + b;
			char p[256];
		}
	}
	return (realRegSetValueExW)(hKey, lpValueName, Reserved, dwType, lpData, cbData);
}

LONG WINAPI MyRegSetValueW(
	_In_     HKEY    hKey,
	_In_opt_ LPCWSTR lpSubKey,
	_In_     DWORD   dwType,
	_In_     LPCWSTR lpData,
	_In_     DWORD   cbData
)
{

	return (realRegSetValueW)(hKey, lpSubKey, dwType, lpData, cbData);
}

LONG WINAPI MyRegDeleteKeyExW(
	_In_       HKEY    hKey,
	_In_       LPCWSTR lpSubKey,
	_In_       REGSAM  samDesired,
	_Reserved_ DWORD   Reserved
)
{

	return (realRegDeleteKeyExW)(hKey, lpSubKey, samDesired, Reserved);
}

LONG WINAPI MyRegDeleteKeyW(
	_In_ HKEY    hKey,
	_In_ LPCWSTR lpSubKey
)
{

	return (realRegDeleteKeyW)(hKey, lpSubKey);
}

LONG WINAPI MyRegSetKeySecurity(
	_In_ HKEY                 hKey,
	_In_ SECURITY_INFORMATION SecurityInformation,
	_In_ PSECURITY_DESCRIPTOR pSecurityDescriptor
)
{

	return (realRegSetKeySecurity)(hKey, SecurityInformation, pSecurityDescriptor);
}

LONG WINAPI MyRegRestoreKeyW(
	_In_ HKEY    hKey,
	_In_ LPCWSTR lpFile,
	_In_ DWORD   dwFlags
)
{

	return (realRegRestoreKeyW)(hKey, lpFile, dwFlags);
}

LONG WINAPI MyRegReplaceKeyW(
	_In_     HKEY    hKey,
	_In_opt_ LPCWSTR lpSubKey,
	_In_     LPCWSTR lpNewFile,
	_In_     LPCWSTR lpOldFile
)
{

	return (realRegReplaceKeyW)(hKey, lpSubKey, lpNewFile, lpOldFile);
}

LONG WINAPI MyRegLoadKeyW(
	_In_     HKEY    hKey,
	_In_opt_ LPCWSTR lpSubKey,
	_In_     LPCWSTR lpFile
)
{

	return (realRegLoadKeyW)(hKey, lpSubKey, lpFile);
}

LONG WINAPI MyRegUnLoadKey(
	_In_     HKEY    hKey,
	_In_opt_ LPCWSTR lpSubKey
)
{

	return (realRegUnLoadKey)(hKey, lpSubKey);
}