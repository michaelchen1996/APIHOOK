// DllInject.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "DllInject.h"


int main()
{
	vector<LPTSTR> szTargetList;

	//SetPrivilege
	if (!SetPrivilege(SE_DEBUG_NAME, TRUE))
	{
		OutputDebugString(TEXT("SetPrivilege ERROR\n"));
		return 0;
	}

	//ReadTargetList
	ReadTargetList(&szTargetList);

	//CreateRemoteThread Inject
	DoSingleInject(&szTargetList);
	//DoContinualInject(&szTargetList);

	//CreateProcess Inject
	//printf("GetExeEntryPoint: %x\n", GetExeEntryPoint("C:\\Users\\michael\\Documents\\GitHub\\APIHOOK\\APIHOOK\\x64\\Debug\\DllInject.exe"));
	//CreateProcessAndDoInject(TEXT("C:\\Users\\michael\\Documents\\GitHub\\APIHOOK\\APIHOOK\\x64\\Debug\\TESTAPI.exe"));
	return 0;
}


void ReadTargetList(vector<LPTSTR> *szTargetList) {
	TCHAR szListDirectory[MAX_PATH];
	TCHAR szProcName[MAX_PATH];
	TCHAR szBuf[2];
	DWORD dwNumRead;
	HANDLE hFile = NULL;

	GetCurrentDirectory(MAX_PATH, szListDirectory);
	StringCbCat(szListDirectory, MAX_PATH, TEXT("\\TargetList.txt"));
	OutputDebugString(szListDirectory);
	OutputDebugString(TEXT("\n"));
	hFile = CreateFile(
		szListDirectory, 
		GENERIC_READ, 
		FILE_SHARE_WRITE, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL
	);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		printf_s("error: %d\n", GetLastError()); system("PAUSE");
		OutputDebugString(TEXT("TargetList.txt NOT FOUND\n"));
		return;
	}
	StringCbCopy(szProcName, MAX_PATH, TEXT(""));
	while (TRUE)
	{
		ReadFile(hFile, szBuf, 2, &dwNumRead, NULL);
		szBuf[1] = TEXT('\0');
		if (0 == dwNumRead)
		{
			CloseHandle(hFile);
			break;
		}
		if (TEXT('\r') == *szBuf)
		{
			OutputDebugString(szProcName);
			OutputDebugString(TEXT(" in TargetList\n"));
			SIZE_T dwProcNameLength = 0;
			StringCbLength(szProcName, MAX_PATH, &dwProcNameLength);
			dwProcNameLength += sizeof(TCHAR);
			LPTSTR szTempProcName = (LPTSTR)HeapAlloc(GetProcessHeap(), 0, dwProcNameLength);
			StringCbCopy(szTempProcName, dwProcNameLength, szProcName);
			szTargetList->push_back(szTempProcName);
			szProcName[0] = TEXT('\0');
			continue;
		}
		if (TEXT('\n') == *szBuf)
		{
			continue;
		}
		StringCbCat(szProcName, MAX_PATH, szBuf);
	}

	return;
}


BOOL SetPrivilege(LPCTSTR lpszPrivilege, BOOL bEnablePrivilege)
{
	TOKEN_PRIVILEGES tp;
	HANDLE hToken;
	LUID luid;

	if (!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
		&hToken))
	{
		OutputDebugString(TEXT("OpenProcessToken ERROR\n"));
		return FALSE;
	}

	if (!LookupPrivilegeValue(NULL,             // lookup privilege on local system  
		lpszPrivilege,    // privilege to lookup   
		&luid))          // receives LUID of privilege  
	{
		OutputDebugString(TEXT("LookupPrivilegeValue ERROR\n"));
		return FALSE;
	}

	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;
	if (bEnablePrivilege)
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	else
		tp.Privileges[0].Attributes = 0;

	// Enable the privilege or disable all privileges.  
	if (!AdjustTokenPrivileges(hToken,
		FALSE,
		&tp,
		sizeof(TOKEN_PRIVILEGES),
		(PTOKEN_PRIVILEGES)NULL,
		(PDWORD)NULL))
	{
		OutputDebugString(TEXT("AdjustTokenPrivileges ERROR\n"));
		return FALSE;
	}

	if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
	{
		OutputDebugString(TEXT("GetLastError ERROR\n"));
		return FALSE;
	}

	return TRUE;
}