// TEST.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"
#include "strsafe.h"
//#include <Psapi.h>
//#include <DbgHelp.h>
#include <Imagehlp.h>

BOOL SetPrivilege(LPCTSTR lpszPrivilege, BOOL bEnablePrivilege);
LPBYTE  GetExeEntryPoint(PCSTR filename);


#pragma pack (push ,1) // 保证下面的结构体采用BYTE对齐（必须）  
typedef struct INJECT_CODE
{
	BYTE      int_PUSHAD;         // pushad        0x60         
	BYTE      int_PUSH;             // push &szDLL     0x68  
	DWORD push_Value;           //            &szDLL = "ApiSpy.dll"的path  
	BYTE      int_MOVEAX;              //  move eax &LoadLibrary  0xB8  
	DWORD eax_Value;             //     &LoadLibrary  
	WORD    call_eax;         //     call eax    0xD0FF(FF D0) (LoadLibrary("ApiSpy.dll");
	BYTE      jmp_MOVEAX;             //     move eax &ReplaceOldCode  0xB8         
	DWORD jmp_Value;             //     JMP的参数  
	WORD    jmp_eax;        //     jmp eax   0xE0FF(FF E0) jmp ReplaceOldCode;  
	char szDLL[MAX_PATH]; //  "ApiSpy.dll"的FullPath  
}INJECT_LOADLIBRARY_CODE, *LPINJECT_CODE;
#pragma pack (pop , 1)  

typedef struct
{
	LPBYTE  lpEntryPoint;   // 目标进程的入口地址  
	BYTE      oldcode[sizeof(INJECT_CODE)];        // 目标进程的代码保存  
}SPY_MEM_SHARE, *LPSPY_MEM_SHARE;


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


	LPBYTE pEntryPoint = GetExeEntryPoint("C:\\Users\\michael\\Documents\\GitHub\\APIHOOK\\APIHOOK\\x64\\Debug\\TESTAPI.exe");
	printf("EP: 0x%x\n", pEntryPoint);

	HANDLE hMap = CreateFileMapping((HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE, 0, sizeof(SPY_MEM_SHARE), TEXT("MyDllMapView"));
	LPSPY_MEM_SHARE lpMap = (LPSPY_MEM_SHARE)MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);

	
	DWORD dwProcessId;
	HANDLE hProcess;
	LPTSTR szTargetPath = TEXT("C:\\Users\\michael\\Documents\\GitHub\\APIHOOK\\APIHOOK\\x64\\Debug\\TESTAPI.exe");
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcess(
		szTargetPath,
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
	dwProcessId = pi.dwProcessId;
	printf("PID:%u\n", dwProcessId);

	char szCurrentDir[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, szCurrentDir);
	SIZE_T stRead;
	ReadProcessMemory(pi.hProcess, pEntryPoint, &lpMap->oldcode, sizeof(INJECT_CODE), &stRead);
	lpMap->lpEntryPoint = pEntryPoint;
	INJECT_CODE     newCode;
	strcpy_s(newCode.szDLL, szCurrentDir);
	strcat_s(newCode.szDLL, "\\dll.dll");
	// 准备硬代码（汇编代码）  
	newCode.int_PUSHAD = 0x60;
	newCode.int_PUSH = 0x68;
	newCode.int_MOVEAX = 0xB8;
	newCode.call_eax = 0xD0FF;
	newCode.jmp_MOVEAX = 0xB8;
	newCode.jmp_eax = 0xE0FF;
	newCode.eax_Value = (DWORD)&LoadLibraryA;
	newCode.push_Value = (DWORD)(pEntryPoint + offsetof(INJECT_CODE, szDLL));
	DWORD dwNewFlg, dwOldFlg;
	dwNewFlg = PAGE_READWRITE;
	VirtualProtectEx(pi.hProcess, (LPVOID)pEntryPoint, sizeof(DWORD), dwNewFlg, &dwOldFlg);
	WriteProcessMemory(pi.hProcess, pEntryPoint, &newCode, sizeof(newCode), NULL);//&dwWrited);  
	VirtualProtectEx(pi.hProcess, (LPVOID)pEntryPoint, sizeof(DWORD), dwOldFlg, &dwNewFlg);
	UnmapViewOfFile(lpMap);

	system("PAUSE");
    return 0;
}


LPBYTE  GetExeEntryPoint(PCSTR filename)
{
	PIMAGE_NT_HEADERS pNTHeader;
	DWORD pEntryPoint;
	PLOADED_IMAGE pImage;
	pImage = ImageLoad(filename, NULL);
	if (pImage == NULL)
		return NULL;
	pNTHeader = pImage->FileHeader;
	pEntryPoint = pNTHeader->OptionalHeader.AddressOfEntryPoint + pNTHeader->OptionalHeader.ImageBase;
	ImageUnload(pImage);
	return (LPBYTE)pEntryPoint;
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