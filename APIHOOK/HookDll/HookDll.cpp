// HookDll.cpp: 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "HookDll.h"


TRACED_HOOK_HANDLE      hHookZwSetInformationFile = new HOOK_TRACE_INFO();
ULONG                   HookZwSetInformationFile_ACLEntries[1] = { 0 };
ptrZwSetInformationFile realZwSetInformationFile = NULL;


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

	realZwSetInformationFile = (ptrZwSetInformationFile)GetRealApiEntry(L"ntdll.dll", "ZwSetInformationFile");
}


void DoHook()
{
	NTSTATUS status = 0;
	//hook MyZwSetInformationFile
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
}


void DoUnHook()
{
	//LhUninstallAllHooks();
	//OutputDebugString(L"LhUninstallAllHooks\n");

	NTSTATUS status = 0;
	status = LhUninstallHook(hHookZwSetInformationFile);
	if (!SUCCEEDED(status))
	{
		OutputDebugString(L"LhUninstallHook ERROR\n");
	}
	delete hHookZwSetInformationFile;
	hHookZwSetInformationFile = NULL;
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
	OutputDebugString(L"PrepareRealApiEntry()\n");

	hModule = GetModuleHandleW(lpModuleName);
	if (NULL == hModule)
	{
		OutputDebugString(L"GetModuleHandleW ERROR\n");
	}
	realProc = GetProcAddress(hModule, lpProcName);
	if (NULL == realProc)
	{
		OutputDebugString(L"GetProcAddress ERROR\n");
	}
	return realProc;
	//CloseHandle(hModule);
}
