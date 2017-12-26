#include "stdafx.h"
#include "CreateProcessInject.h"

BOOL CreateProcessAndDoInject(LPCWSTR szProcessName)
{
	HANDLE hSemaphoreStatus;
	HANDLE hSemaphoreAck;

	HANDLE hProcess;
	HANDLE hThread;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	CONTEXT ctx;
	LPVOID LpRemoteAddr;
	DWORD64 LoadLibraryEntry;
	BYTE *szDllPath;

	BYTE ShellCode64[SHELLCODE_SIZE] =
	{
		0x48,0x83,0xEC,0x28,  // sub rsp ,28h

		0x48,0x8D,0x0d,       // [+4] lea rcx,
		0xaa,0xbb,0xcc,0xdd,  // [+7] dll path offset =  TargetAddress- Current(0x48)[+4] -7 

		0xff,0x15,            // [+11]
		0xdd,0xcc,0xbb,0xaa,  // [+13] call LoadLibrary offset = TargetAddress - Current(0xe8)[+11] -5

		0x48,0x83,0xc4,0x28,  // [+17] add rsp,28

		0xff,0x25,            // [+21]
		0xaa,0xbb,0xcc,0xdd,  // [+23] jmp rip offset  = TargetAddress - Current(0xff)[+20] - 6

		0xaa,0xbb,0xcc,0xdd,  //+27
		0xaa,0xbb,0xcc,0xdd,

		0xaa,0xbb,0xcc,0xdd,  //+35
		0xaa,0xbb,0xcc,0xdd

		//+43
	};

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

	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	if (!CreateProcess(
		szProcessName,
		NULL,
		NULL,
		NULL,
		FALSE,
		CREATE_SUSPENDED,
		NULL,
		NULL,
		&si,
		&pi
	))
	{
		OutputDebugString(TEXT("CreateProcess ERROR\n"));
		return FALSE;
	}

	hProcess = pi.hProcess;
	hThread = pi.hThread;
	
	if (!GetThreadContext(hThread, &ctx))
	{
		OutputDebugString(TEXT("GetThreadContext Error\n"));
		return FALSE;
	}
	
	LpRemoteAddr = VirtualAllocEx(
		hProcess, 
		NULL, 
		SHELLCODE_SIZE, 
		MEM_COMMIT | MEM_RESERVE, 
		PAGE_EXECUTE_READWRITE
	);
	if (LpRemoteAddr == NULL)
	{
		OutputDebugString(TEXT("VirtualAlloc Error\n"));
		return FALSE;
	}

#ifdef _UNICODE
	LoadLibraryEntry = (DWORD64)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryW");
#else
	LoadLibraryEntry = (DWORD64)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryA");
#endif // _UNICODE

	if (LoadLibraryEntry == NULL)
	{
		OutputDebugString(TEXT("LoadDllAddr error\n"));
		return FALSE;
	}
	
	szDllPath = ShellCode64 + SHELLCODE_DLL_PATH;
	GetCurrentDirectory(MAX_PATH, (LPTSTR)szDllPath);
	StringCbCat((LPTSTR)szDllPath, MAX_PATH, TEXT("\\HookDll.dll"));
	*(DWORD*)(ShellCode64 + SHELLCODE_DLL_PATH_ADDR) = (DWORD)SHELLCODE_DLL_PATH_OFFSET;

	*(DWORD64*)(ShellCode64 + SHELLCODE_LOAD_LIBRARY_ENTRY) = LoadLibraryEntry;
	*(DWORD*)(ShellCode64 + SHELLCODE_DLL_PATH_ADDR) = (DWORD)SHELLCODE_LOAD_LIBRARY_ENTRY_OFFSET;
	
	*(DWORD64*)(ShellCode64 + SHELLCODE_RIP) = ctx.Rip;
	*(DWORD*)(ShellCode64 + SHELLCODE_RIP_ADDR) = (DWORD)SHELLCODE_RIP_OFFSET;
	
	if (!WriteProcessMemory(hProcess, LpRemoteAddr, ShellCode64, SHELLCODE_SIZE, NULL))
	{
		OutputDebugString(TEXT("write Process Error\n"));
		return FALSE;
	}

	ctx.ContextFlags = CONTEXT_ALL;
	ctx.Rip = (DWORD64)LpRemoteAddr;

	if (!SetThreadContext(hThread, &ctx))
	{
		OutputDebugString(TEXT("set thread context error\n"));
		return FALSE;
	}

	ResumeThread(hThread);

	WaitForSingleObject(hSemaphoreStatus, INFINITE);

	TerminateProcess(hProcess, 0);
	
	ReleaseSemaphore(hSemaphoreAck, 1, NULL);

	CloseHandle(hSemaphoreStatus);
	hSemaphoreStatus = NULL;
	CloseHandle(hSemaphoreAck);
	hSemaphoreAck = NULL;

}