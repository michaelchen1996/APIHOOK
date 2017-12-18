// DllUnInject.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "DllUnInject.h"


int main()
{
	
	//SetPrivilege
	if (!SetPrivilege(SE_DEBUG_NAME, TRUE))
	{
		OutputDebugString(L"SetPrivilege ERROR\n");
		return 0;
	}

	DoSearchProcess(NULL);
	//DoReleaseSemaphoreStatus();

    return 0;
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
		OutputDebugString(L"CreateToolhelp32Snapshot ERROR");
		return;
	}

	//get pe32
	pe32.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hProcessSnap, &pe32))
	{
		OutputDebugString(L"Process32First ERROR");
		CloseHandle(hProcessSnap);
		return;
	}
	//search for all the process
	do
	{
		if (!szProcessName || CSTR_EQUAL == CompareString(GetSystemDefaultLCID(), 0, szProcessName, -1, pe32.szExeFile, -1))
		{
			OutputDebugString(pe32.szExeFile);
			OutputDebugString(L": looking for module\n");
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
		OutputDebugString(L"CreateToolhelp32Snapshot for MODULE ERROR\n");
		return;
	}

	// get me32
	me32.dwSize = sizeof(MODULEENTRY32);
	if (!Module32First(hModuleSnap, &me32))
	{
		OutputDebugString(L"Module32First ERROR\n");
		CloseHandle(hModuleSnap);
		return;
	}
	//search for all the module
	do
	{
		if (CSTR_EQUAL == CompareString(GetSystemDefaultLCID(), 0, me32.szModule, -1, L"EasyHook64.dll", -1))
		{
			hEasyHook64 = me32.hModule;
		}
		else if (CSTR_EQUAL == CompareString(GetSystemDefaultLCID(), 0, me32.szModule, -1, L"HookDll.dll", -1))
		{
			hHookDll = me32.hModule;
		}
	} while (Module32Next(hModuleSnap, &me32));
	CloseHandle(hModuleSnap);

	//do DllUnInject
	if (hHookDll)
	{
		OutputDebugString(L"HookDll.dll UnInject START\n");
		DoDllUnInject(dwProcessId, hHookDll);
	}
	if (hEasyHook64)
	{
		OutputDebugString(L"EasyHook64.dll UnInject START\n");
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
	hKernel32 = GetModuleHandle(L"kernel32.dll");
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
			OutputDebugString(L"CreateRemoteThread ERROR\n");
		}
	}
}

void DoReleaseSemaphoreStatus()
{
	HANDLE hSemaphoreStatus;

	hSemaphoreStatus = CreateSemaphore(NULL, 0, 1, L"APIHOOK_Monitor_Semaphore_Status");
	if (!hSemaphoreStatus)
	{
		printf("CreateSemaphore ERROR\n");
		return;
	}
	ReleaseSemaphore(hSemaphoreStatus, 1, NULL);
	CloseHandle(hSemaphoreStatus);
	hSemaphoreStatus = NULL;
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