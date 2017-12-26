// TEST.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"
#include "strsafe.h"
#include <tlhelp32.h>

BOOL SetPrivilege(LPCTSTR lpszPrivilege, BOOL bEnablePrivilege);


int main()
{
	/*
	WCHAR szCurrentDirectory[MAX_PATH];
	DWORD dwCurDirPathLen;
	dwCurDirPathLen = GetCurrentDirectoryW(MAX_PATH, szCurrentDirectory);
	if (dwCurDirPathLen == 0)
	{
		printf("获取当前目录错误。\n");
		return 0;
	}
	OutputDebugStringW(szCurrentDirectory);
	OutputDebugStringW(L"\n");
	*/

	//APIHOOK_Monitor_Semaphore_Status TEST
	/*
	HANDLE hSemaphoreStatus;
	//hSemaphoreStatus = OpenSemaphore(SYNCHRONIZE, FALSE, L"APIHOOK_Monitor_Semaphore_Status");
	hSemaphoreStatus = CreateSemaphore(NULL, 0, 1, L"APIHOOK_Monitor_Semaphore_Status");
	if (!hSemaphoreStatus)
	{
		printf("fuck\n");
		system("PAUSE");
	}
	ReleaseSemaphore(hSemaphoreStatus, 1, NULL);
	CloseHandle(hSemaphoreStatus);
	hSemaphoreStatus = NULL;
	*/

	//Mailslot TEST
	/*
	HANDLE hWriteMailslot = NULL;
	hWriteMailslot = CreateFile(L"\\\\*\\mailslot\\APIHOOK\\Monitor\\Log", 
		GENERIC_WRITE, 
		FILE_SHARE_READ, 
		NULL, 
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (INVALID_HANDLE_VALUE == hWriteMailslot)
	{
		OutputDebugString(L"FUCK!!!!\n");
		system("PAUSE");
		return 0;
	}
	for (int j=0;j<5;j++)
	{
		SIZE_T a;
		DWORD b,c;
		StringCbLength(L"你好呵呵\r\n", MAX_PATH, &a);
		WriteFile(hWriteMailslot, L"你好呵呵\r\n", a, &b, NULL);
		Sleep(100);
	}
	*/


	if (!SetPrivilege(SE_DEBUG_NAME, TRUE))
	{
		OutputDebugString(TEXT("SetPrivilege ERROR\n"));
		return 0;
	}

	LoadLibraryA("C;\\HookDll.dll");


	HANDLE hProcess;
	HANDLE hThread;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	BYTE ShellCode64[64] =
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

	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcess(
		TEXT("C:\\Users\\michael\\Documents\\GitHub\\APIHOOK\\APIHOOK\\x64\\Debug\\TESTAPI.exe"),
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
	}

	hProcess = pi.hProcess;
	hThread = pi.hThread;

	//////////////////////////////////////////////////////
	CONTEXT ctx;
	if (!GetThreadContext(hThread, &ctx))
	{
		printf("GetThreadContext Error\n");
		return FALSE;
	}
	ctx.ContextFlags = CONTEXT_ALL;
	LPVOID LpAddr = VirtualAllocEx(hProcess, NULL, 64, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (LpAddr == NULL)
	{
		printf("VirtualAlloc Error\n");
		return FALSE;
	}
	DWORD64 LoadDllAAddr = (DWORD64)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryA");
	if (LoadDllAAddr == NULL)
	{
		printf("LoadDllAddr error\n");
		return FALSE;
	}
	//////////////////////////////////////////////////////
	BYTE *DllPath;
	DllPath = ShellCode64 + 43;
	StringCbCopyA((char*)DllPath, MAX_PATH, "C:\\HookDll.dll");
	DWORD DllNameOffset = 32;
	*(DWORD*)(ShellCode64 + 7) = (DWORD)DllNameOffset;
	//DWORD LoadDllAddroffset = (BYTE*)LoadDllAAddr - ((BYTE*)LpAddr + 11) - 5;
	*(DWORD64*)(ShellCode64 + 35) = LoadDllAAddr;
	*(DWORD*)(ShellCode64 + 13) = 18;
	*(DWORD64*)(ShellCode64 + 27) = ctx.Rip;
	*(DWORD*)(ShellCode64 + 23) = (DWORD)0;
	if (!WriteProcessMemory(hProcess, LpAddr, ShellCode64, 64, NULL))
	{
		printf("write Process Error\n");
		return FALSE;
	}
	ctx.Rip = (DWORD64)LpAddr;
	if (!SetThreadContext(hThread, &ctx))
	{
		printf("set thread context error\n");
		return FALSE;
	}
	ResumeThread(hThread);

	system("PAUSE");
    return 0;
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