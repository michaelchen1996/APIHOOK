#include "stdafx.h"
#include "CreateRemoteThreadInject.h"


void DoSingleInject(vector<LPTSTR> *szTargetList)
{
	TCHAR szDllDirectory[MAX_PATH];
	HANDLE hProcess = NULL;

	//DoInject into all the process
	for (DWORD i = 0; i < szTargetList->size(); i++)
	{
		LPTSTR szProcessName = (*szTargetList)[i];
		DWORD dwProcessId = GetProcessID(szProcessName);
		if (!dwProcessId)
		{
			OutputDebugString(szProcessName);
			OutputDebugString(TEXT(" is not running\n"));
			continue;
		}
		if (isInjected(dwProcessId))
		{
			OutputDebugString(szProcessName);
			OutputDebugString(TEXT(" has already been injected\n"));
			continue;
		}

		//Get handle of process by PID
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
		if (!hProcess)
		{
			OutputDebugString(TEXT("OpenProcess ERROR\n"));
			return;
		}
		//Inject EasyHook64.dll into process
		GetCurrentDirectory(MAX_PATH, szDllDirectory);
		StringCbCat(szDllDirectory, MAX_PATH, TEXT("\\EasyHook64.dll"));
		OutputDebugString(szDllDirectory);
		OutputDebugString(L" Inject\n");
		DoInject(hProcess, szDllDirectory);
		//Inject HookDll.dll into process
		GetCurrentDirectory(MAX_PATH, szDllDirectory);
		StringCbCat(szDllDirectory, MAX_PATH, TEXT("\\HookDll.dll"));
		OutputDebugString(szDllDirectory);
		OutputDebugString(TEXT(" Inject\n"));
		DoInject(hProcess, szDllDirectory);

		CloseHandle(hProcess);
	}
}


void DoContinualInject(vector<LPTSTR> *szTargetList)
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

	while (WAIT_OBJECT_0 != WaitForSingleObject(hSemaphoreStatus, 0))
	{
		DoSingleInject(szTargetList);
		Sleep(1000);
	}

	ReleaseSemaphore(hSemaphoreAck, 1, NULL);

	CloseHandle(hSemaphoreStatus);
	hSemaphoreStatus = NULL;
	CloseHandle(hSemaphoreAck);
	hSemaphoreAck = NULL;
}


DWORD GetProcessID(LPTSTR pName)
{
	DWORD dwPId = 0;
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;

	// Take a snapshot of all processes in the system.
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		OutputDebugString(TEXT("CreateToolhelp32Snapshot (of processes)"));
		return 0;
	}

	// Set the size of the structure before using it.
	pe32.dwSize = sizeof(PROCESSENTRY32);

	// Retrieve information about the first process,
	// and exit if unsuccessful
	if (!Process32First(hProcessSnap, &pe32))
	{
		OutputDebugString(TEXT("Process32First"));
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


BOOL isInjected(DWORD dwProcessId)
{
	HANDLE hModuleSnap = NULL;
	MODULEENTRY32 me32;
	HMODULE hHookDll = NULL;

	//take a snapshot
	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessId);
	if (hModuleSnap == INVALID_HANDLE_VALUE)
	{
		OutputDebugString(TEXT("CreateToolhelp32Snapshot for MODULE ERROR\n"));
		return FALSE;
	}

	// get me32
	me32.dwSize = sizeof(MODULEENTRY32);
	if (!Module32First(hModuleSnap, &me32))
	{
		OutputDebugString(TEXT("Module32First ERROR\n"));
		CloseHandle(hModuleSnap);
		return FALSE;
	}
	//search for all the module
	do
	{
		if (CSTR_EQUAL == CompareString(
			GetSystemDefaultLCID(), 
			0, 
			me32.szModule, 
			-1, 
			TEXT("HookDll.dll"), 
			-1
		))
		{
			hHookDll = me32.hModule;
			break;
		}
	} while (Module32Next(hModuleSnap, &me32));
	CloseHandle(hModuleSnap);
	if (hHookDll)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


void DoInject(HANDLE hProcess, TCHAR *dllName)
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
		OutputDebugString(TEXT("VirtualAllocEx ERROR\n"));
		return;
	}
	WriteProcessMemory(hProcess, pRemoteBuf, (LPVOID)dllName, stBufSize, &stWriteSize);
	if (stBufSize != stWriteSize)
	{
		OutputDebugString(TEXT("WriteProcessMemory ERROR\n"));

	}
	hKernel32 = GetModuleHandle(TEXT("kernel32.dll"));

#ifdef _UNICODE
	pThreadProc = (PTHREAD_START_ROUTINE)GetProcAddress(hKernel32, "LoadLibraryW");
#else
	pThreadProc = (PTHREAD_START_ROUTINE)GetProcAddress(hKernel32, "LoadLibraryA");
#endif // _UNICODE

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
		OutputDebugString(TEXT("CreateRemoteThread ERROR\n"));
	}
	VirtualFreeEx(hProcess, pRemoteBuf, stBufSize, MEM_RELEASE);

}