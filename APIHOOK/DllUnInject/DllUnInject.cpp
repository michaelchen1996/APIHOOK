// DllUnInject.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "DllUnInject.h"


int main()
{

	//SetPrivilege
	if (!SetPrivilege(SE_DEBUG_NAME, TRUE))
	{
		OutputDebugString(TEXT("SetPrivilege ERROR\n"));
		return 0;
	}

	DoReleaseSemaphoreStatus();

	ReadTargetListAndDo();

    return 0;
}


void ReadTargetListAndDo() {
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
	szProcName[0] = TEXT('\0');
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
			DoSearchProcess(szProcName);
			szProcName[0] = TEXT('\0');
			continue;

		}
		if (TEXT('\n') == *szBuf)
		{
			continue;
		}
		StringCbCat(szProcName, MAX_PATH, szBuf);
	}
}


void DoSearchProcess(LPCWCHAR szProcessName)
{
	DWORD dwPId = 0;
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;

	//take a snapshot
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		OutputDebugString(TEXT("CreateToolhelp32Snapshot ERROR"));
		return;
	}

	//get pe32
	pe32.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hProcessSnap, &pe32))
	{
		OutputDebugString(TEXT("Process32First ERROR"));
		CloseHandle(hProcessSnap);
		return;
	}
	//search for all the process
	do
	{
		if (!szProcessName || CSTR_EQUAL == CompareString(GetSystemDefaultLCID(), 0, szProcessName, -1, pe32.szExeFile, -1))
		{
			OutputDebugString(pe32.szExeFile);
			OutputDebugString(TEXT(": looking for module\n"));
			DoSearchModule(pe32.th32ProcessID);
		}

	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
}


void DoSearchModule(DWORD dwProcessId)
{
	HANDLE hModuleSnap = NULL;
	MODULEENTRY32 me32;
	HMODULE hEasyHook64 = NULL;
	HMODULE hHookDll = NULL;

	//take a snapshot
	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessId);
	if (hModuleSnap == INVALID_HANDLE_VALUE)
	{
		OutputDebugString(TEXT("CreateToolhelp32Snapshot for MODULE ERROR\n"));
		return;
	}

	// get me32
	me32.dwSize = sizeof(MODULEENTRY32);
	if (!Module32First(hModuleSnap, &me32))
	{
		OutputDebugString(TEXT("Module32First ERROR\n"));
		CloseHandle(hModuleSnap);
		return;
	}
	//search for all the module
	do
	{
		if (CSTR_EQUAL == CompareString(
			GetSystemDefaultLCID(), 
			0, 
			me32.szModule, 
			-1, 
			TEXT("EasyHook64.dll"), 
			-1
		))
		{
			hEasyHook64 = me32.hModule;
		}
		else if (CSTR_EQUAL == CompareString(
			GetSystemDefaultLCID(), 
			0, 
			me32.szModule, 
			-1, 
			TEXT("HookDll.dll"), 
			-1
		))
		{
			hHookDll = me32.hModule;
		}
	} while (Module32Next(hModuleSnap, &me32));
	CloseHandle(hModuleSnap);

	//do DllUnInject
	if (hHookDll)
	{
		OutputDebugString(TEXT("HookDll.dll UnInject START\n"));
		DoDllUnInject(dwProcessId, hHookDll);
	}
	if (hEasyHook64)
	{
		OutputDebugString(TEXT("EasyHook64.dll UnInject START\n"));
		DoDllUnInject(dwProcessId, hEasyHook64);
	}
}

void DoDllUnInject(DWORD dwProcessId, HMODULE hModule)
{
	HMODULE hKernel32 = NULL;
	PTHREAD_START_ROUTINE pThreadProc = NULL;
	HANDLE hThread = NULL;
	HANDLE hProcess = NULL;

	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
	hKernel32 = GetModuleHandle(TEXT("kernel32.dll"));
	pThreadProc = (PTHREAD_START_ROUTINE)GetProcAddress(hKernel32, "FreeLibrary");

	//do UnInject
	if (hModule)
	{
		
		hThread = CreateRemoteThread(hProcess,
			NULL,
			0,
			(LPTHREAD_START_ROUTINE)pThreadProc,
			hModule,
			0,
			NULL);
		if (hThread)
		{
			WaitForSingleObject(hThread, INFINITE);
			CloseHandle(hThread);
		}
		else
		{
			OutputDebugString(TEXT("CreateRemoteThread ERROR\n"));
		}
	}
}

void DoReleaseSemaphoreStatus()
{
	HANDLE hSemaphoreStatus;
	HANDLE hSemaphoreAck;

	hSemaphoreStatus = CreateSemaphore(NULL, 0, 2, TEXT("APIHOOK_Monitor_Semaphore_Status"));
	if (!hSemaphoreStatus)
	{
		OutputDebugString(TEXT("CreateSemaphore ERROR\n"));
		return;
	}

	hSemaphoreAck = CreateSemaphore(NULL, 0, 1, TEXT("APIHOOK_Monitor_Semaphore_Ack"));
	if (!hSemaphoreStatus)
	{
		OutputDebugString(TEXT("CreateSemaphore ERROR\n"));
		return;
	}

	ReleaseSemaphore(hSemaphoreStatus, 2, NULL);
	WaitForSingleObject(hSemaphoreAck, INFINITE);

	CloseHandle(hSemaphoreStatus);
	hSemaphoreStatus = NULL;
	CloseHandle(hSemaphoreAck);
	hSemaphoreAck = NULL;
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