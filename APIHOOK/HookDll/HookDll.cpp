// HookDll.cpp: 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "HookDll.h"

//FileAPI INIT
TRACED_HOOK_HANDLE      hHookZwSetInformationFile = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookCreateFileW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookCreateFileA = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookReadFile = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE		hHookMoveFileW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE		hHookCopyFileW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE		hHookDeleteFileW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE		hHookFindFirstFileW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE		hHookFindNextFileW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE		hHookSetFileAttributesW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE		hHookCreateHardLinkW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE		hHookSetEndOfFile = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE		hHookSetFileValidData = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE		hHookSetFileTime = new HOOK_TRACE_INFO();

ULONG                   HookZwSetInformationFile_ACLEntries[1] = { 0 };
ULONG                   HookCreateFileW_ACLEntries[1] = { 0 };
ULONG                   HookCreateFileA_ACLEntries[1] = { 0 };
ULONG                   HookReadFile_ACLEntries[1] = { 0 };
ULONG                   HookMoveFileW_ACLEntries[1] = { 0 };
ULONG                   HookCopyFileW_ACLEntries[1] = { 0 };
ULONG                   HookDeleteFileW_ACLEntries[1] = { 0 };
ULONG                   HookFindFirstFileW_ACLEntries[1] = { 0 };
ULONG                   HookFindNextFileW_ACLEntries[1] = { 0 };
ULONG                   HookSetFileAttributesW_ACLEntries[1] = { 0 };
ULONG                   HookCreateHardLinkW_ACLEntries[1] = { 0 };
ULONG                   HookSetEndOfFile_ACLEntries[1] = { 0 };
ULONG                   HookSetFileValidData_ACLEntries[1] = { 0 };
ULONG                   HookSetFileTime_ACLEntries[1] = { 0 };

ptrZwSetInformationFile realZwSetInformationFile = NULL;
ptrCreateFileW realCreateFileW = NULL;
ptrCreateFileA realCreateFileA = NULL;
ptrReadFile realReadFile = NULL;
ptrMoveFileW realMoveFileW = NULL;
ptrCopyFileW realCopyFileW = NULL;
ptrDeleteFileW realDeleteFileW = NULL;
ptrFindFirstFileW realFindFirstFileW = NULL;
ptrFindNextFileW realFindNextFileW = NULL;
ptrSetFileAttributesW realSetFileAttributesW = NULL;
ptrCreateHardLinkW realCreateHardLinkW = NULL;
ptrSetEndOfFile realSetEndOfFile = NULL;
ptrSetFileValidData realSetFileValidData = NULL;
ptrSetFileTime realSetFileTime = NULL;
//FileAPI INITfinished


//ProcessAPI INIT
//ProcessAPI INIT finished


//NetworkAPI INIT
//NetworkAPI INIT finished


//RegAPI INIT 
//RegAPI INIT finished


//OtherAPI INIT
//OtherAPI INIT finished

void Prepare()
{
	hWriteMailslot = CreateFile(TEXT("\\\\*\\mailslot\\APIHOOK\\Monitor\\Log"),
		GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (INVALID_HANDLE_VALUE == hWriteMailslot)
	{
		OutputDebugString(TEXT("Create Mailslot ERROR\n"));
		return;
	}

	//FileAPI Prepare
	realZwSetInformationFile = (ptrZwSetInformationFile)GetRealApiEntry(L"ntdll.dll", "ZwSetInformationFile");
	realSetFileTime = (ptrSetFileTime)GetRealApiEntry(L"Gdi32", "SetFileTime");
	realSetFileValidData = (ptrSetFileValidData)GetRealApiEntry(L"Kernel32", "SetFileValidData");
	realSetEndOfFile = (ptrSetEndOfFile)GetRealApiEntry(L"Kernel32", "SetEndOfFile");
	realCreateHardLinkW = (ptrCreateHardLinkW)GetRealApiEntry(L"Kernel32", "CreateHardLinkW");
	realSetFileAttributesW = (ptrSetFileAttributesW)GetRealApiEntry(L"Kernel32", "SetFileAttributesW");
	realFindNextFileW = (ptrFindNextFileW)GetRealApiEntry(L"Kernel32", "FindNextFileW");
	realFindFirstFileW = (ptrFindFirstFileW)GetRealApiEntry(L"Kernel32", "FindFirstFileW");
	realDeleteFileW = (ptrDeleteFileW)GetRealApiEntry(L"Kernel32", "DeleteFileW");
	realCopyFileW = (ptrCopyFileW)GetRealApiEntry(L"Kernel32", "CopyFileW");
	realMoveFileW = (ptrMoveFileW)GetRealApiEntry(L"Kernel32", "MoveFileW");
	realCreateFileW = (ptrCreateFileW)GetRealApiEntry(L"Kernel32", "CreateFileW");
	realCreateFileA = (ptrCreateFileA)GetRealApiEntry(L"Kernel32", "CreateFileA");
	realReadFile = (ptrReadFile)GetRealApiEntry(L"Kernel32", "ReadFile");
	//FileAPI Prepare finished


	//ProcessAPI Prepare
	//ProcessAPI Prepare finished


	//NetworkAPI Prepare
	//NetworkAPI Prepare finished


	//RegAPI Prepare
	//RegAPI Prepare finished


	//OtherAPI Prepare
	//OtherAPI Prepare finished
}


void DoHook()
{
	NTSTATUS status = 0;
	//FileAPI DoHook
	/*
	status = LhInstallHook(
		realZwSetInformationFile,
		MyZwSetInformationFile,
		NULL,
		hHookZwSetInformationFile);
	if (!SUCCEEDED(status))
	{
		OutputDebugString(L"LhInstallHook ERROR\n");
	}
	status = LhSetExclusiveACL(
		HookZwSetInformationFile_ACLEntries,
		1,
		hHookZwSetInformationFile);
	if (!SUCCEEDED(status))
	{
		OutputDebugString(L"LhSetExclusiveACL ERROR\n");
	}
	*/
	LhInstallHook(realSetFileTime, MySetFileTime, NULL, hHookSetFileTime);
	LhSetExclusiveACL(HookSetFileTime_ACLEntries, 1, hHookSetFileTime);
	
	LhInstallHook(realSetFileValidData, MySetFileValidData, NULL, hHookSetFileValidData);
	LhSetExclusiveACL(HookSetFileValidData_ACLEntries, 1, hHookSetFileValidData);

	LhInstallHook(realCreateFileA, MyCreateFileA, NULL, hHookCreateFileA);
	LhSetExclusiveACL(HookCreateFileA_ACLEntries, 1, hHookCreateFileA);

	LhInstallHook(realReadFile, MyReadFile, NULL, hHookReadFile);
	LhSetExclusiveACL(HookReadFile_ACLEntries, 1, hHookReadFile);
	
	LhInstallHook(realCreateFileW, MyCreateFileW, NULL, hHookCreateFileW);
	LhSetExclusiveACL(HookCreateFileW_ACLEntries, 1, hHookCreateFileW);
	
	LhInstallHook(realMoveFileW, MyMoveFileW, NULL, hHookMoveFileW);
	LhSetExclusiveACL(HookMoveFileW_ACLEntries, 1, hHookMoveFileW);
	
	LhInstallHook(realCopyFileW, MyCopyFileW, NULL, hHookCopyFileW);
	LhSetExclusiveACL(HookCopyFileW_ACLEntries, 1, hHookCopyFileW);
	
	LhInstallHook(realDeleteFileW, MyDeleteFileW, NULL, hHookDeleteFileW);
	LhSetExclusiveACL(HookDeleteFileW_ACLEntries, 1, hHookDeleteFileW);
	
	LhInstallHook(realFindFirstFileW, MyFindFirstFileW, NULL, hHookFindFirstFileW);
	LhSetExclusiveACL(HookFindFirstFileW_ACLEntries, 1, hHookFindFirstFileW);
	
	LhInstallHook(realFindNextFileW, MyFindNextFileW, NULL, hHookFindNextFileW);
	LhSetExclusiveACL(HookFindNextFileW_ACLEntries, 1, hHookFindNextFileW);
	
	LhInstallHook(realSetFileAttributesW, MySetFileAttributesW, NULL, hHookSetFileAttributesW);
	LhSetExclusiveACL(HookSetFileAttributesW_ACLEntries, 1, hHookSetFileAttributesW);
	
	LhInstallHook(realCreateHardLinkW, MyCreateHardLinkW, NULL, hHookCreateHardLinkW);
	LhSetExclusiveACL(HookCreateHardLinkW_ACLEntries, 1, hHookCreateHardLinkW);
	
	LhInstallHook(realSetEndOfFile, MySetEndOfFile, NULL, hHookSetEndOfFile);
	LhSetExclusiveACL(HookSetEndOfFile_ACLEntries, 1, hHookSetEndOfFile);
	//FileAPI DoHook finished

	//ProcessAPI DoHook
	//ProcessAPI DoHook finished

	//NetworkAPI DoHook
	//NetworkAPI DoHook finished

	//RegAPI DoHook
	//RegAPI DoHook finished

	//OtherAPI DoHook
	//OtherAPI DoHook finished
}


void DoUnHook()
{
	NTSTATUS status = 0;
	LhUninstallAllHooks();
	OutputDebugString(L"LhUninstallAllHooks\n");

	/*
	status = LhUninstallHook(hHookZwSetInformationFile);
	if (!SUCCEEDED(status))
	{
		OutputDebugString(L"LhUninstallHook ERROR\n");
	}
	*/
	
	//FileAPI DoUnHook finished
	delete hHookZwSetInformationFile;
	delete hHookCreateFileW;
	delete hHookCreateFileA;
	delete hHookReadFile;
	delete hHookMoveFileW;
	delete hHookCopyFileW;
	delete hHookDeleteFileW;
	delete hHookFindFirstFileW;
	delete hHookFindNextFileW;
	delete hHookSetFileAttributesW;
	delete hHookCreateHardLinkW;
	delete hHookSetEndOfFile;
	delete hHookSetFileValidData;
	delete hHookSetFileTime;

	hHookZwSetInformationFile = NULL;
	hHookCreateFileW = NULL;
	hHookCreateFileA = NULL;
	hHookReadFile = NULL;
	hHookMoveFileW = NULL;
	hHookCopyFileW = NULL;
	hHookDeleteFileW = NULL;
	hHookFindFirstFileW = NULL;
	hHookFindNextFileW = NULL;
	hHookSetFileAttributesW = NULL;
	hHookCreateHardLinkW = NULL;
	hHookSetEndOfFile = NULL;
	hHookSetFileValidData = NULL;
	hHookSetFileTime = NULL;
	//FileAPI DoUnHook finished

	//ProcessAPI DoUnHook
	//ProcessAPI DoUnHook finished

	//NetworkAPI DoUnHook
	//NetworkAPI DoUnHook finished

	//RegAPI DoUnHook
	//RegAPI DoUnHook finished

	//OtherAPI DoUnHook
	//OtherAPI DoUnHook finished

	status = LhWaitForPendingRemovals();
	if (!SUCCEEDED(status))
	{
		OutputDebugString(L"LhWaitForPendingRemovals ERROR\n");
	}
}


void Finish()
{
	CloseHandle(hWriteMailslot);
	hWriteMailslot = NULL;

}


FARPROC GetRealApiEntry(LPCWSTR lpModuleName, LPCSTR lpProcName)
{
	HMODULE hModule = NULL;
	FARPROC realProc = NULL;

	hModule = GetModuleHandleW(lpModuleName);
	if (NULL == hModule)
	{
		OutputDebugStringW(lpModuleName);
		OutputDebugString(L": GetModuleHandleW ERROR\n");
	}
	realProc = GetProcAddress(hModule, lpProcName);
	if (NULL == realProc)
	{
		OutputDebugStringA(lpProcName);
		OutputDebugString(L": GetProcAddress ERROR\n");
	}
	return realProc;
	//CloseHandle(hModule);
}
