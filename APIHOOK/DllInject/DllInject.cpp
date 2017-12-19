// DllInject.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "DllInject.h"

#define MAX_TARGET_NUM 10


int main()
{
	WCHAR szCurrentDirectory[MAX_PATH];
	HANDLE hProcess = NULL;
	DWORD dwPIdList[MAX_TARGET_NUM];
	DWORD dwNumTarget = 0;
	WCHAR szDllDirectory[MAX_PATH];


	//GetModuleFileName
	GetModuleDirectory(szCurrentDirectory);

	//SetPrivilege
	if (!SetPrivilege(SE_DEBUG_NAME, TRUE))
	{
		OutputDebugString(L"SetPrivilege ERROR\n");
		return 0;
	}

	//ReadTargetList
	dwNumTarget = ReadTargetList(szCurrentDirectory, dwPIdList);

	//DoInject into all the process
	for (DWORD i = 0; i < dwNumTarget; i++)
	{
		//Get handle of process by PID
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPIdList[i]);
		if (!hProcess)
		{
			OutputDebugString(L"OpenProcess ERROR\n");
			return 0;
		}
		//Inject EasyHook64.dll into process
		StringCbCopy(szDllDirectory, MAX_PATH, szCurrentDirectory);
		StringCbCat(szDllDirectory, MAX_PATH, L"EasyHook64.dll");
		OutputDebugString(szDllDirectory);
		OutputDebugString(L" Inject\n");
		DoInject(hProcess, szDllDirectory);
		//Inject HookDll.dll into process
		StringCbCopy(szDllDirectory, MAX_PATH, szCurrentDirectory);
		StringCbCat(szDllDirectory, MAX_PATH, L"HookDll.dll");
		OutputDebugString(szDllDirectory);
		OutputDebugString(L" Inject\n");
		DoInject(hProcess, szDllDirectory);

		CloseHandle(hProcess);
	}

	return 0;
}

VOID GetModuleDirectory(PWCHAR szCurrentDirectory)
{
	DWORD dwCurDirPathLen;
	dwCurDirPathLen = GetModuleFileName(NULL, szCurrentDirectory, MAX_PATH);
	if (!dwCurDirPathLen)
	{
		printf("GetModuleFileName ERROR\n");
		return;
	}
	SIZE_T i = 0;
	StringCbLengthW(szCurrentDirectory, MAX_PATH, &i);
	if (0 == i)
	{
		return;
	}
	for (; i > 0 && L'\\' != szCurrentDirectory[i - 1]; i--) {}
	szCurrentDirectory[i] = L'\0';
	OutputDebugString(szCurrentDirectory);
	OutputDebugString(L"\n");

}

DWORD ReadTargetList(LPCWCHAR szCurrentDirectory, LPDWORD dwPIdList) {
	DWORD dwTargetNum = 0;
	WCHAR szListDirectory[MAX_PATH];
	WCHAR szProcName[MAX_PATH];
	WCHAR szBuf[2];
	DWORD dwNumRead;
	HANDLE hFile = NULL;

	StringCbCopy(szListDirectory, MAX_PATH, szCurrentDirectory);
	StringCbCat(szListDirectory, MAX_PATH, L"TargetList.txt");
	OutputDebugString(szListDirectory);
	OutputDebugString(L"\n");
	hFile = CreateFile(szListDirectory, GENERIC_READ, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		printf_s("error: %d\n", GetLastError()); system("PAUSE");
		OutputDebugString(L"TargetList.txt NOT FOUND\n");
		return 0;
	}
	StringCbCopy(szProcName, MAX_PATH, L"");
	while (TRUE)
	{
		ReadFile(hFile, szBuf, 2, &dwNumRead, NULL);
		szBuf[1] = L'\0';
		if (0 == dwNumRead)
		{
			CloseHandle(hFile);
			break;
		}
		if (L'\r' == *szBuf)
		{
			OutputDebugString(szProcName);
			OutputDebugString(L" in TargetList\n");
			dwPIdList[dwTargetNum] = GetProcessID(szProcName);
			if (0 != dwPIdList[dwTargetNum])
			{
				dwTargetNum++;
			}
			StringCbCopy(szProcName, MAX_PATH, L"");
			continue;

		}
		if (L'\n' == *szBuf)
		{
			continue;
		}
		StringCbCat(szProcName, MAX_PATH, szBuf);
	}

	return dwTargetNum;
}

VOID DoInject(HANDLE hProcess, WCHAR *dllName)
{
	SIZE_T stBufSize = wcslen(dllName) * sizeof(wchar_t) + 2;
	SIZE_T stWriteSize = 0;
	LPVOID pRemoteBuf = NULL;
	HMODULE hKernel32 = NULL;
	PTHREAD_START_ROUTINE pThreadProc = NULL;
	HANDLE hThread = NULL;

	pRemoteBuf = VirtualAllocEx(hProcess, NULL, stBufSize, MEM_COMMIT, PAGE_READWRITE);
	if (!pRemoteBuf)
	{
		OutputDebugString(L"VirtualAllocEx ERROR\n");
		return;
	}
	WriteProcessMemory(hProcess, pRemoteBuf, (LPVOID)dllName, stBufSize, &stWriteSize);
	if (stBufSize != stWriteSize)
	{
		OutputDebugString(L"WriteProcessMemory ERROR\n");

	}
	hKernel32 = GetModuleHandleW(L"kernel32.dll");
	pThreadProc = (PTHREAD_START_ROUTINE)GetProcAddress(hKernel32, "LoadLibraryW");
	hThread = CreateRemoteThread(hProcess,
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)pThreadProc,
		pRemoteBuf,
		0,
		NULL);
	if (hThread)
	{
		WaitForSingleObject(hThread, INFINITE);
		CloseHandle(hThread);
	}
	else
	{
		OutputDebugString(L"CreateRemoteThread ERROR\n");
	}
	VirtualFreeEx(hProcess, pRemoteBuf, stBufSize, MEM_RELEASE);
	
}


DWORD GetProcessID(WCHAR *pName)
{
	DWORD dwPId = 0;
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;

	// Take a snapshot of all processes in the system.
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		OutputDebugString(L"CreateToolhelp32Snapshot (of processes)");
		return 0;
	}

	// Set the size of the structure before using it.
	pe32.dwSize = sizeof(PROCESSENTRY32);

	// Retrieve information about the first process,
	// and exit if unsuccessful
	if (!Process32First(hProcessSnap, &pe32))
	{
		OutputDebugString(L"Process32First");
		CloseHandle(hProcessSnap);
		return 0;
	}
	do
	{
		if (lstrcmp(pe32.szExeFile, pName) == 0)
		{
			dwPId = pe32.th32ProcessID;
		}
	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
	return dwPId;
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
		OutputDebugString(L"OpenProcessToken ERROR\n");
		return FALSE;
	}

	if (!LookupPrivilegeValue(NULL,             // lookup privilege on local system  
		lpszPrivilege,    // privilege to lookup   
		&luid))          // receives LUID of privilege  
	{
		OutputDebugString(L"LookupPrivilegeValue ERROR\n");
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
		OutputDebugString(L"AdjustTokenPrivileges ERROR\n");
		return FALSE;
	}

	if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
	{
		OutputDebugString(L"GetLastError ERROR\n");
		return FALSE;
	}

	return TRUE;
}