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
TRACED_HOOK_HANDLE      hHookBitBlt = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookCreateFileMappingW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookOpenFileMappingW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookDeviceIoControl = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookFindWindowExW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookGetAsyncKeyState = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookGetDC = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookGetForegroundWindow = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookGetKeyState = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookGetTempPath = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookMapViewOfFile = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookOpenFile = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookAdjustTokenPrivileges = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookAttachThreadInput = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookCallNextHookEx = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookCheckRemoteDebuggerPresent = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookControlService = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookCreateRemoteThread = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookCreateToolhelp32Snapshot = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookEnumProcesses = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookEnumProcessModules = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookGetProcAddress = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookGetSystemDefaultLangID = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookGetThreadContext = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookGetTickCount = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookIsDebuggerPresent = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookLoadLibraryExW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookLoadResource = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookModule32FirstW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookModule32NextW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookOpenProcess = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookPeekNamedPipe = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookProcess32First = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookProcess32Next = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookQueryPerformanceCounter = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookQueueUserAPC = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookReadProcessMemory = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookResumeThread = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookSetThreadContext = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookSuspendThread = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookThread32First = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookThread32Next = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookToolhelp32ReadProcessMemory = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookVirtualAllocEx = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookVirtualProtectEx = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookWinExec = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookWriteProcessMemory = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookRegisterHotKey = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookCreateProcessA = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookCreateMutexW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookFindResourceW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookFindWindowW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookGetWindowsDirectoryW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookMapVirtualKeyW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookOpenMutexW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookOpenSCManagerW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookCreateProcessW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookCreateServiceW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookGetModuleFileNameExW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookGetModuleHandleW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookGetStartupInfoW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookGetVersionExW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookLoadLibraryW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookOutputDebugStringW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookSetWindowsHookExW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookShellExecuteW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookStartServiceCtrlDispatcherW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookSetLocalTime = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookTerminateThread = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookVirtualFree = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookSetProcessWorkingSetSize = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookTerminateProcess = new HOOK_TRACE_INFO();

ULONG                   HookBitBlt_ACLEntries[1] = { 0 };
ULONG                   HookCreateFileMappingW_ACLEntries[1] = { 0 };
ULONG					HookOpenFileMappingW_ACLEntries[1] = { 0 };
ULONG                   HookDeviceIoControl_ACLEntries[1] = { 0 };
ULONG                   HookFindWindowExW_ACLEntries[1] = { 0 };
ULONG                   HookGetAsyncKeyState_ACLEntries[1] = { 0 };
ULONG                   HookGetDC_ACLEntries[1] = { 0 };
ULONG                   HookGetForegroundWindow_ACLEntries[1] = { 0 };
ULONG                   HookGetKeyState_ACLEntries[1] = { 0 };
ULONG                   HookGetTempPath_ACLEntries[1] = { 0 };
ULONG                   HookMapViewOfFile_ACLEntries[1] = { 0 };
ULONG                   HookOpenFile_ACLEntries[1] = { 0 };
ULONG                   HookAdjustTokenPrivileges_ACLEntries[1] = { 0 };
ULONG                   HookAttachThreadInput_ACLEntries[1] = { 0 };
ULONG                   HookCallNextHookEx_ACLEntries[1] = { 0 };
ULONG                   HookCheckRemoteDebuggerPresent_ACLEntries[1] = { 0 };
ULONG                   HookControlService_ACLEntries[1] = { 0 };
ULONG                   HookCreateRemoteThread_ACLEntries[1] = { 0 };
ULONG                   HookCreateToolhelp32Snapshot_ACLEntries[1] = { 0 };
ULONG                   HookEnumProcesses_ACLEntries[1] = { 0 };
ULONG                   HookEnumProcessModules_ACLEntries[1] = { 0 };
ULONG                   HookGetProcAddress_ACLEntries[1] = { 0 };
ULONG                   HookGetSystemDefaultLangID_ACLEntries[1] = { 0 };
ULONG                   HookGetThreadContext_ACLEntries[1] = { 0 };
ULONG                   HookGetTickCount_ACLEntries[1] = { 0 };
ULONG                   HookIsDebuggerPresent_ACLEntries[1] = { 0 };
ULONG                   HookLoadLibraryExW_ACLEntries[1] = { 0 };
ULONG                   HookLoadResource_ACLEntries[1] = { 0 };
ULONG                   HookModule32FirstW_ACLEntries[1] = { 0 };
ULONG                   HookModule32NextW_ACLEntries[1] = { 0 };
ULONG                   HookOpenProcess_ACLEntries[1] = { 0 };
ULONG                   HookPeekNamedPipe_ACLEntries[1] = { 0 };
ULONG                   HookProcess32First_ACLEntries[1] = { 0 };
ULONG                   HookProcess32Next_ACLEntries[1] = { 0 };
ULONG                   HookQueryPerformanceCounter_ACLEntries[1] = { 0 };
ULONG                   HookQueueUserAPC_ACLEntries[1] = { 0 };
ULONG                   HookReadProcessMemory_ACLEntries[1] = { 0 };
ULONG                   HookResumeThread_ACLEntries[1] = { 0 };
ULONG                   HookSetThreadContext_ACLEntries[1] = { 0 };
ULONG                   HookSuspendThread_ACLEntries[1] = { 0 };
ULONG                   HookThread32First_ACLEntries[1] = { 0 };
ULONG                   HookThread32Next_ACLEntries[1] = { 0 };
ULONG                   HookToolhelp32ReadProcessMemory_ACLEntries[1] = { 0 };
ULONG                   HookVirtualAllocEx_ACLEntries[1] = { 0 };
ULONG                   HookVirtualProtectEx_ACLEntries[1] = { 0 };
ULONG                   HookWinExec_ACLEntries[1] = { 0 };
ULONG                   HookWriteProcessMemory_ACLEntries[1] = { 0 };
ULONG                   HookRegisterHotKey_ACLEntries[1] = { 0 };
ULONG                   HookCreateProcessA_ACLEntries[1] = { 0 };
ULONG                   HookCreateMutexW_ACLEntries[1] = { 0 };
ULONG                   HookFindResourceW_ACLEntries[1] = { 0 };
ULONG                   HookFindWindowW_ACLEntries[1] = { 0 };
ULONG                   HookGetWindowsDirectoryW_ACLEntries[1] = { 0 };
ULONG                   HookMapVirtualKeyW_ACLEntries[1] = { 0 };
ULONG                   HookOpenMutexW_ACLEntries[1] = { 0 };
ULONG                   HookOpenSCManagerW_ACLEntries[1] = { 0 };
ULONG                   HookCreateProcessW_ACLEntries[1] = { 0 };
ULONG                   HookCreateServiceW_ACLEntries[1] = { 0 };
ULONG                   HookGetModuleFileNameExW_ACLEntries[1] = { 0 };
ULONG                   HookGetModuleHandleW_ACLEntries[1] = { 0 };
ULONG                   HookGetStartupInfoW_ACLEntries[1] = { 0 };
ULONG                   HookGetVersionExW_ACLEntries[1] = { 0 };
ULONG                   HookLoadLibraryW_ACLEntries[1] = { 0 };
ULONG                   HookOutputDebugStringW_ACLEntries[1] = { 0 };
ULONG                   HookSetWindowsHookExW_ACLEntries[1] = { 0 };
ULONG                   HookShellExecuteW_ACLEntries[1] = { 0 };
ULONG                   HookStartServiceCtrlDispatcherW_ACLEntries[1] = { 0 };
ULONG                   HookSetLocalTime_ACLEntries[1] = { 0 };
ULONG                   HookTerminateThread_ACLEntries[1] = { 0 };
ULONG                   HookVirtualFree_ACLEntries[1] = { 0 };
ULONG                   HookSetProcessWorkingSetSize_ACLEntries[1] = { 0 };
ULONG                   HookTerminateProcess_ACLEntries[1] = { 0 };

ptrBitBlt realBitBlt = NULL;
ptrCreateFileMappingW realCreateFileMappingW = NULL;
ptrOpenFileMappingW realOpenFileMappingW = NULL;
ptrDeviceIoControl realDeviceIoControl = NULL;
ptrFindWindowExW realFindWindowExW = NULL;
ptrGetAsyncKeyState realGetAsyncKeyState = NULL;
ptrGetDC realGetDC = NULL;
ptrGetKeyState realGetKeyState = NULL;
ptrGetForegroundWindow realGetForegroundWindow = NULL;
ptrGetTempPath realGetTempPath = NULL;
ptrMapViewOfFile realMapViewOfFile = NULL;
ptrOpenFile realOpenFile = NULL;
ptrAdjustTokenPrivileges realAdjustTokenPrivileges = NULL;
ptrAttachThreadInput realAttachThreadInput = NULL;
ptrCallNextHookEx realCallNextHookEx = NULL;
ptrCheckRemoteDebuggerPresent realCheckRemoteDebuggerPresent = NULL;
ptrControlService realControlService = NULL;
ptrCreateRemoteThread realCreateRemoteThread = NULL;
ptrCreateToolhelp32Snapshot realCreateToolhelp32Snapshot = NULL;
ptrEnumProcesses realEnumProcesses = NULL;
ptrEnumProcessModules realEnumProcessModules = NULL;
ptrGetProcAddress realGetProcAddress = NULL;
ptrGetSystemDefaultLangID realGetSystemDefaultLangID = NULL;
ptrGetThreadContext realGetThreadContext = NULL;
ptrGetTickCount realGetTickCount = NULL;
ptrIsDebuggerPresent realIsDebuggerPresent = NULL;
ptrLoadLibraryExW realLoadLibraryExW = NULL;
ptrLoadResource realLoadResource = NULL;
ptrModule32FirstW realModule32FirstW = NULL;
ptrModule32NextW realModule32NextW = NULL;
ptrOpenProcess realOpenProcess = NULL;
ptrPeekNamedPipe realPeekNamedPipe = NULL;
ptrProcess32First realProcess32First = NULL;
ptrProcess32Next realProcess32Next = NULL;
ptrQueryPerformanceCounter realQueryPerformanceCounter = NULL;
ptrQueueUserAPC realQueueUserAPC = NULL;
ptrReadProcessMemory realReadProcessMemory = NULL;
ptrResumeThread realResumeThread = NULL;
ptrSetThreadContext realSetThreadContext = NULL;
ptrSuspendThread realSuspendThread = NULL;
ptrThread32First realThread32First = NULL;
ptrThread32Next realThread32Next = NULL;
ptrToolhelp32ReadProcessMemory realToolhelp32ReadProcessMemory = NULL;
ptrVirtualAllocEx realVirtualAllocEx = NULL;
ptrVirtualProtectEx realVirtualProtectEx = NULL;
ptrWinExec realWinExec = NULL;
ptrWriteProcessMemory realWriteProcessMemory = NULL;
ptrRegisterHotKey realRegisterHotKey = NULL;
ptrCreateProcessA realCreateProcessA = NULL;
ptrCreateMutexW realCreateMutexW = NULL;
ptrFindResourceW realFindResourceW = NULL;
ptrFindWindowW realFindWindowW;
ptrGetWindowsDirectoryW realGetWindowsDirectoryW = NULL;
ptrMapVirtualKeyW realMapVirtualKeyW = NULL;
ptrOpenMutexW realOpenMutexW = NULL;
ptrOpenSCManagerW realOpenSCManagerW = NULL;
ptrCreateProcessW realCreateProcessW = NULL;
ptrCreateServiceW realCreateServiceW = NULL;
ptrGetModuleFileNameExW realGetModuleFileNameExW = NULL;
ptrGetModuleHandleW realGetModuleHandleW = NULL;
ptrGetStartupInfoW realGetStartupInfoW = NULL;
ptrGetVersionExW realGetVersionExW = NULL;
ptrLoadLibraryW realLoadLibraryW = NULL;
ptrOutputDebugStringW realOutputDebugStringW = NULL;
ptrSetWindowsHookExW realSetWindowsHookExW = NULL;
ptrShellExecuteW realShellExecuteW = NULL;
ptrStartServiceCtrlDispatcherW realStartServiceCtrlDispatcherW = NULL;
ptrSetLocalTime realSetLocalTime = NULL;
ptrTerminateThread realTerminateThread = NULL;
ptrVirtualFree realVirtualFree = NULL;
ptrSetProcessWorkingSetSize realSetProcessWorkingSetSize = NULL;
ptrTerminateProcess realTerminateProcess = NULL;
//ProcessAPI INIT finished


//NetworkAPI INIT
//NetworkAPI INIT finished


//RegAPI INIT 
TRACED_HOOK_HANDLE      hHookRegOpenKeyExW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookRegOpenKeyW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookRegCreateKeyExW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookRegCreateKeyW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookRegQueryValueExW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookRegQueryValueW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookRegSetValueExW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookRegSetValueW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookRegDeleteKeyExW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookRegDeleteKeyW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookRegSetKeySecurity = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookRegRestoreKeyW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookRegReplaceKeyW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookRegLoadKeyW = new HOOK_TRACE_INFO();
TRACED_HOOK_HANDLE      hHookRegUnLoadKey = new HOOK_TRACE_INFO();

ULONG                   HookRegOpenKeyExW_ACLEntries[1] = { 0 };
ULONG                   HookRegOpenKeyW_ACLEntries[1] = { 0 };
ULONG                   HookRegCreateKeyExW_ACLEntries[1] = { 0 };
ULONG                   HookRegCreateKeyW_ACLEntries[1] = { 0 };
ULONG                   HookRegQueryValueExW_ACLEntries[1] = { 0 };
ULONG                   HookRegQueryValueW_ACLEntries[1] = { 0 };
ULONG                   HookRegSetValueExW_ACLEntries[1] = { 0 };
ULONG                   HookRegSetValueW_ACLEntries[1] = { 0 };
ULONG                   HookRegDeleteKeyExW_ACLEntries[1] = { 0 };
ULONG                   HookRegDeleteKeyW_ACLEntries[1] = { 0 };
ULONG                   HookRegSetKeySecurity_ACLEntries[1] = { 0 };
ULONG                   HookRegRestoreKeyW_ACLEntries[1] = { 0 };
ULONG                   HookRegReplaceKeyW_ACLEntries[1] = { 0 };
ULONG                   HookRegLoadKeyW_ACLEntries[1] = { 0 };
ULONG                   HookRegUnLoadKey_ACLEntries[1] = { 0 };

ptrRegOpenKeyExW realRegOpenKeyExW = NULL;
ptrRegOpenKeyW realRegOpenKeyW = NULL;
ptrRegCreateKeyExW realRegCreateKeyExW = NULL;
ptrRegCreateKeyW realRegCreateKeyW = NULL;
ptrRegQueryValueExW realRegQueryValueExW = NULL;
ptrRegQueryValueW realRegQueryValueW = NULL;
ptrRegSetValueExW realRegSetValueExW = NULL;
ptrRegSetValueW realRegSetValueW = NULL;
ptrRegDeleteKeyExW realRegDeleteKeyExW = NULL;
ptrRegDeleteKeyW realRegDeleteKeyW = NULL;
ptrRegSetKeySecurity realRegSetKeySecurity = NULL;
ptrRegRestoreKeyW realRegRestoreKeyW = NULL;
ptrRegReplaceKeyW realRegReplaceKeyW = NULL;
ptrRegLoadKeyW realRegLoadKeyW = NULL;
ptrRegUnLoadKey realRegUnLoadKey = NULL;
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
	realBitBlt = (ptrBitBlt)GetRealApiEntry(L"Gdi32", "BitBlt");
	realCreateFileMappingW = (ptrCreateFileMappingW)GetRealApiEntry(L"Kernel32", "CreateFileMappingW");
	realOpenFileMappingW = (ptrOpenFileMappingW)GetRealApiEntry(L"Kernel32", "OpenFileMappingW");
	realDeviceIoControl = (ptrDeviceIoControl)GetRealApiEntry(L"Kernel32", "DeviceIoControl");
	realFindWindowExW = (ptrFindWindowExW)GetRealApiEntry(L"User32", "FindWindowExW");
	realGetAsyncKeyState = (ptrGetAsyncKeyState)GetRealApiEntry(L"User32", "GetAsyncKeyState");
	realGetDC = (ptrGetDC)GetRealApiEntry(L"User32", "GetDC");
	realGetForegroundWindow = (ptrGetForegroundWindow)GetRealApiEntry(L"User32", "GetForegroundWindow");
	realGetKeyState = (ptrGetKeyState)GetRealApiEntry(L"User32", "GetKeyState");
	realGetTempPath = (ptrGetTempPath)GetRealApiEntry(L"Kernel32", "GetTempPath");
	realMapViewOfFile = (ptrMapViewOfFile)GetRealApiEntry(L"Kernel32", "MapViewOfFile");
	realOpenFile = (ptrOpenFile)GetRealApiEntry(L"Kernel32", "OpenFile");
	realAdjustTokenPrivileges = (ptrAdjustTokenPrivileges)GetRealApiEntry(L"Advapi32", "AdjustTokenPrivileges");
	realAttachThreadInput = (ptrAttachThreadInput)GetRealApiEntry(L"User32", "AttachThreadInput");
	realCallNextHookEx = (ptrCallNextHookEx)GetRealApiEntry(L"User32", "CallNextHookEx");
	realCheckRemoteDebuggerPresent = (ptrCheckRemoteDebuggerPresent)GetRealApiEntry(L"Kernel32", "CheckRemoteDebuggerPresent");
	realControlService = (ptrControlService)GetRealApiEntry(L"Advapi32", "ControlService");
	realCreateRemoteThread = (ptrCreateRemoteThread)GetRealApiEntry(L"Kernel32", "CreateRemoteThread");
	realCreateToolhelp32Snapshot = (ptrCreateToolhelp32Snapshot)GetRealApiEntry(L"Kernel32", "CreateToolhelp32Snapshot");
	realEnumProcesses = (ptrEnumProcesses)GetRealApiEntry(L"Kernel32", "EnumProcesses");
	realEnumProcessModules = (ptrEnumProcessModules)GetRealApiEntry(L"Kernel32", "EnumProcessModules");
	realGetProcAddress = (ptrGetProcAddress)GetRealApiEntry(L"Kernel32", "GetProcAddress");
	realGetSystemDefaultLangID = (ptrGetSystemDefaultLangID)GetRealApiEntry(L"Kernel32", "GetSystemDefaultLangID");
	realGetThreadContext = (ptrGetThreadContext)GetRealApiEntry(L"Kernel32", "GetThreadContext");
	realGetTickCount = (ptrGetTickCount)GetRealApiEntry(L"Kernel32", "GetTickCount");
	realIsDebuggerPresent = (ptrIsDebuggerPresent)GetRealApiEntry(L"Kernel32", "IsDebuggerPresent");
	realLoadLibraryExW = (ptrLoadLibraryExW)GetRealApiEntry(L"Kernel32", "LoadLibraryExW");
	realLoadResource = (ptrLoadResource)GetRealApiEntry(L"Kernel32", "LoadResource");
	realModule32FirstW = (ptrModule32FirstW)GetRealApiEntry(L"Kernel32", "Module32FirstW");
	realModule32NextW = (ptrModule32NextW)GetRealApiEntry(L"Kernel32", "Module32NextW");
	realOpenProcess = (ptrOpenProcess)GetRealApiEntry(L"Kernel32", "OpenProcess");
	realPeekNamedPipe = (ptrPeekNamedPipe)GetRealApiEntry(L"Kernel32", "PeekNamedPipe");
	realProcess32First = (ptrProcess32First)GetRealApiEntry(L"Kernel32", "Process32FirstW");
	realProcess32Next = (ptrProcess32Next)GetRealApiEntry(L"Kernel32", "Process32NextW");
	realQueryPerformanceCounter = (ptrQueryPerformanceCounter)GetRealApiEntry(L"Kernel32", "QueryPerformanceCounter");
	realQueueUserAPC = (ptrQueueUserAPC)GetRealApiEntry(L"Kernel32", "QueueUserAPC");
	realReadProcessMemory = (ptrReadProcessMemory)GetRealApiEntry(L"Kernel32", "ReadProcessMemory");
	realResumeThread = (ptrResumeThread)GetRealApiEntry(L"Kernel32", "ResumeThread");
	realSetThreadContext = (ptrSetThreadContext)GetRealApiEntry(L"Kernel32", "SetThreadContext");
	realSuspendThread = (ptrSuspendThread)GetRealApiEntry(L"Kernel32", "SuspendThread");
	realThread32First = (ptrThread32First)GetRealApiEntry(L"Kernel32", "Thread32First");
	realThread32Next = (ptrThread32Next)GetRealApiEntry(L"Kernel32", "Thread32Next");
	realToolhelp32ReadProcessMemory = (ptrToolhelp32ReadProcessMemory)GetRealApiEntry(L"Kernel32", "Toolhelp32ReadProcessMemory");
	realVirtualAllocEx = (ptrVirtualAllocEx)GetRealApiEntry(L"Kernel32", "VirtualAllocEx");
	realVirtualProtectEx = (ptrVirtualProtectEx)GetRealApiEntry(L"Kernel32", "VirtualProtectEx");
	realWinExec = (ptrWinExec)GetRealApiEntry(L"Kernel32", "WinExec");
	realWriteProcessMemory = (ptrWriteProcessMemory)GetRealApiEntry(L"Kernel32", "WriteProcessMemory");
	realRegisterHotKey = (ptrRegisterHotKey)GetRealApiEntry(L"User32", "RegisterHotKey");
	realCreateProcessA = (ptrCreateProcessA)GetRealApiEntry(L"Kernel32", "CreateProcessA");
	realCreateMutexW = (ptrCreateMutexW)GetRealApiEntry(L"Kernel32", "CreateMutexW");
	realFindResourceW = (ptrFindResourceW)GetRealApiEntry(L"Kernel32", "FindResourceW");
	realFindWindowW = (ptrFindWindowW)GetRealApiEntry(L"User32", "FindWindowW");
	realGetWindowsDirectoryW = (ptrGetWindowsDirectoryW)GetRealApiEntry(L"Kernel32", "GetWindowsDirectoryW");
	realMapVirtualKeyW = (ptrMapVirtualKeyW)GetRealApiEntry(L"User32", "MapVirtualKeyW");
	realOpenMutexW = (ptrOpenMutexW)GetRealApiEntry(L"Kernel32", "OpenMutexW");
	realOpenSCManagerW = (ptrOpenSCManagerW)GetRealApiEntry(L"Advapi32", "OpenSCManagerW");
	realCreateProcessW = (ptrCreateProcessW)GetRealApiEntry(L"Kernel32", "CreateProcessW");
	realCreateServiceW = (ptrCreateServiceW)GetRealApiEntry(L"Advapi32", "CreateServiceW");
	realGetModuleFileNameExW = (ptrGetModuleFileNameExW)GetRealApiEntry(L"Kernel32", "GetModuleFileNameExW");
	realGetModuleHandleW = (ptrGetModuleHandleW)GetRealApiEntry(L"Kernel32", "GetModuleHandleW");
	realGetStartupInfoW = (ptrGetStartupInfoW)GetRealApiEntry(L"Kernel32", "GetStartupInfoW");
	realGetVersionExW = (ptrGetVersionExW)GetRealApiEntry(L"Kernel32", "GetVersionExW");
	realLoadLibraryW = (ptrLoadLibraryW)GetRealApiEntry(L"Kernel32", "LoadLibraryW");
	realOutputDebugStringW = (ptrOutputDebugStringW)GetRealApiEntry(L"Kernel32", "OutputDebugStringW");
	realSetWindowsHookExW = (ptrSetWindowsHookExW)GetRealApiEntry(L"User32", "SetWindowsHookExW");
	realShellExecuteW = (ptrShellExecuteW)GetRealApiEntry(L"Shell32", "ShellExecuteW");
	realStartServiceCtrlDispatcherW = (ptrStartServiceCtrlDispatcherW)GetRealApiEntry(L"Advapi32", "StartServiceCtrlDispatcherW");
	realSetLocalTime = (ptrSetLocalTime)GetRealApiEntry(L"Kernel32", "SetLocalTime");
	realTerminateThread = (ptrTerminateThread)GetRealApiEntry(L"Kernel32", "TerminateThread");
	realVirtualFree = (ptrVirtualFree)GetRealApiEntry(L"Kernel32", "VirtualFree");
	realSetProcessWorkingSetSize = (ptrSetProcessWorkingSetSize)GetRealApiEntry(L"Kernel32", "SetProcessWorkingSetSize");
	realTerminateProcess = (ptrTerminateProcess)GetRealApiEntry(L"Kernel32", "TerminateProcess");
	//ProcessAPI Prepare finished

	//NetworkAPI Prepare
	//NetworkAPI Prepare finished

	//RegAPI Prepare
	realRegOpenKeyExW = (ptrRegOpenKeyExW)GetRealApiEntry(L"Advapi32", "RegOpenKeyExW");
	realRegOpenKeyW = (ptrRegOpenKeyW)GetRealApiEntry(L"Advapi32", "RegOpenKeyW");
	realRegCreateKeyExW = (ptrRegCreateKeyExW)GetRealApiEntry(L"Advapi32", "RegCreateKeyExW");
	realRegCreateKeyW = (ptrRegCreateKeyW)GetRealApiEntry(L"Advapi32", "RegCreateKeyW");
	realRegQueryValueExW = (ptrRegQueryValueExW)GetRealApiEntry(L"Advapi32", "RegQueryValueExW");
	realRegQueryValueW = (ptrRegQueryValueW)GetRealApiEntry(L"Advapi32", "RegQueryValueW");
	realRegSetValueExW = (ptrRegSetValueExW)GetRealApiEntry(L"Advapi32", "RegSetValueExW");
	realRegSetValueW = (ptrRegSetValueW)GetRealApiEntry(L"Advapi32", "RegSetValueW");
	realRegDeleteKeyExW = (ptrRegDeleteKeyExW)GetRealApiEntry(L"Advapi32", "RegDeleteKeyExW");
	realRegDeleteKeyW = (ptrRegDeleteKeyW)GetRealApiEntry(L"Advapi32", "RegDeleteKeyW");
	realRegSetKeySecurity = (ptrRegSetKeySecurity)GetRealApiEntry(L"Advapi32", "RegSetKeySecurity");
	realRegRestoreKeyW = (ptrRegRestoreKeyW)GetRealApiEntry(L"Advapi32", "RegRestoreKeyW");
	realRegReplaceKeyW = (ptrRegReplaceKeyW)GetRealApiEntry(L"Advapi32", "RegReplaceKeyW");
	realRegLoadKeyW = (ptrRegLoadKeyW)GetRealApiEntry(L"Advapi32", "RegLoadKeyW");
	realRegUnLoadKey = (ptrRegUnLoadKey)GetRealApiEntry(L"Advapi32", "RegUnLoadKeyW");
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
	if (realBitBlt != NULL)
	{
		//LhInstallHook(realBitBlt,MyBitBlt,NULL,hHookBitBlt);
		//LhSetExclusiveACL(HookBitBlt_ACLEntries, 1, hHookBitBlt);
	}
	if (realCreateFileMappingW != NULL)
	{
		LhInstallHook(realCreateFileMappingW, MyCreateFileMappingW, NULL, hHookCreateFileMappingW);
		LhSetExclusiveACL(HookCreateFileMappingW_ACLEntries, 1, hHookCreateFileMappingW);
	}
	if (realOpenFileMappingW != NULL)
	{
		LhInstallHook(realOpenFileMappingW, MyOpenFileMappingW, NULL, hHookOpenFileMappingW);
		LhSetExclusiveACL(HookOpenFileMappingW_ACLEntries, 1, hHookOpenFileMappingW);
	}
	if (realDeviceIoControl != NULL)
	{
		LhInstallHook(realDeviceIoControl, MyDeviceIoControl, NULL, hHookDeviceIoControl);
		LhSetExclusiveACL(HookDeviceIoControl_ACLEntries, 1, hHookDeviceIoControl);
	}
	if (realFindWindowExW != NULL)
	{
		LhInstallHook(realFindWindowExW, MyFindWindowExW, NULL, hHookFindWindowExW);
		LhSetExclusiveACL(HookFindWindowExW_ACLEntries, 1, hHookFindWindowExW);
	}
	if (realGetAsyncKeyState != NULL)
	{
		LhInstallHook(realGetAsyncKeyState, MyGetAsyncKeyState, NULL, hHookGetAsyncKeyState);
		LhSetExclusiveACL(HookGetAsyncKeyState_ACLEntries, 1, hHookGetAsyncKeyState);
	}
	if (realGetDC != NULL)
	{
		//LhInstallHook(realGetDC,MyGetDC,NULL,hHookGetDC);
		//LhSetExclusiveACL(HookGetDC_ACLEntries, 1, hHookGetDC);
	}
	if (realGetForegroundWindow != NULL){
		//LhInstallHook(realGetForegroundWindow,MyGetForegroundWindow,NULL,hHookGetForegroundWindow);
		//LhSetExclusiveACL(HookGetForegroundWindow_ACLEntries, 1, hHookGetForegroundWindow);
	}
	if (realGetKeyState != NULL)
	{
		//LhInstallHook(realGetKeyState,MyGetKeyState,NULL,hHookGetKeyState);
		//LhSetExclusiveACL(HookGetKeyState_ACLEntries, 1, hHookGetKeyState);
	}
	if (realGetTempPath != NULL)
	{
		LhInstallHook(realGetTempPath, MyGetTempPath, NULL, hHookGetTempPath);
		LhSetExclusiveACL(HookGetTempPath_ACLEntries, 1, hHookGetTempPath);
	}
	if (realMapViewOfFile != NULL)
	{
		//LhInstallHook(realMapViewOfFile,MyMapViewOfFile,NULL,hHookMapViewOfFile);
		//LhSetExclusiveACL(HookMapViewOfFile_ACLEntries, 1, hHookMapViewOfFile);
	}
	if (realOpenFile != NULL)
	{
		LhInstallHook(realOpenFile, MyOpenFile, NULL, hHookOpenFile);
		LhSetExclusiveACL(HookOpenFile_ACLEntries, 1, hHookOpenFile);
	}
	if (realAdjustTokenPrivileges != NULL)
	{
		LhInstallHook(realAdjustTokenPrivileges, MyAdjustTokenPrivileges, NULL, hHookAdjustTokenPrivileges);
		LhSetExclusiveACL(HookAdjustTokenPrivileges_ACLEntries, 1, hHookAdjustTokenPrivileges);
	}
	if (realAttachThreadInput != NULL)
	{
		LhInstallHook(realAttachThreadInput, MyAttachThreadInput, NULL, hHookAttachThreadInput);
		LhSetExclusiveACL(HookAttachThreadInput_ACLEntries, 1, hHookAttachThreadInput);
	}
	if (realCallNextHookEx != NULL)
	{
		LhInstallHook(realCallNextHookEx, MyCallNextHookEx, NULL, hHookCallNextHookEx);
		LhSetExclusiveACL(HookCallNextHookEx_ACLEntries, 1, hHookCallNextHookEx);
	}
	if (realCheckRemoteDebuggerPresent != NULL)
	{
		LhInstallHook(realCheckRemoteDebuggerPresent, MyCheckRemoteDebuggerPresent, NULL, hHookCheckRemoteDebuggerPresent);
		LhSetExclusiveACL(HookCheckRemoteDebuggerPresent_ACLEntries, 1, hHookCheckRemoteDebuggerPresent);
	}
	if (realControlService != NULL)
	{
		LhInstallHook(realControlService, MyControlService, NULL, hHookControlService);
		LhSetExclusiveACL(HookControlService_ACLEntries, 1, hHookControlService);
	}
	if (realCreateRemoteThread != NULL)
	{
		LhInstallHook(realCreateRemoteThread, MyCreateRemoteThread, NULL, hHookCreateRemoteThread);
		LhSetExclusiveACL(HookCreateRemoteThread_ACLEntries, 1, hHookCreateRemoteThread);
	}
	if (realCreateToolhelp32Snapshot != NULL)
	{
		LhInstallHook(realCreateToolhelp32Snapshot, MyCreateToolhelp32Snapshot, NULL, hHookCreateToolhelp32Snapshot);
		LhSetExclusiveACL(HookCreateToolhelp32Snapshot_ACLEntries, 1, hHookCreateToolhelp32Snapshot);
	}
	if (realEnumProcesses != NULL)
	{
		LhInstallHook(realEnumProcesses, MyEnumProcesses, NULL, hHookEnumProcesses);
		LhSetExclusiveACL(HookEnumProcesses_ACLEntries, 1, hHookEnumProcesses);
	}
	if (realEnumProcessModules != NULL)
	{
		LhInstallHook(realEnumProcessModules, MyEnumProcessModules, NULL, hHookEnumProcessModules);
		LhSetExclusiveACL(HookEnumProcessModules_ACLEntries, 1, hHookEnumProcessModules);
	}
	if (realGetProcAddress != NULL)
	{
		//LhInstallHook(realGetProcAddress,MyGetProcAddress,NULL,hHookGetProcAddress);
		//LhSetExclusiveACL(HookGetProcAddress_ACLEntries, 1, hHookGetProcAddress);
	}
	if (realGetSystemDefaultLangID != NULL)
	{
		LhInstallHook(realGetSystemDefaultLangID, MyGetSystemDefaultLangID, NULL, hHookGetSystemDefaultLangID);
		LhSetExclusiveACL(HookGetSystemDefaultLangID_ACLEntries, 1, hHookGetSystemDefaultLangID);
	}
	if (realGetThreadContext != NULL)
	{
		//LhInstallHook(realGetThreadContext,MyGetThreadContext,NULL,hHookGetThreadContext);
		//LhSetExclusiveACL(HookGetThreadContext_ACLEntries, 1, hHookGetThreadContext);
	}
	if (realGetTickCount != NULL)
	{
		LhInstallHook(realGetTickCount, MyGetTickCount, NULL, hHookGetTickCount);
		LhSetExclusiveACL(HookGetTickCount_ACLEntries, 1, hHookGetTickCount);
	}
	if (realIsDebuggerPresent != NULL)
	{
		LhInstallHook(realIsDebuggerPresent, MyIsDebuggerPresent, NULL, hHookIsDebuggerPresent);
		LhSetExclusiveACL(HookIsDebuggerPresent_ACLEntries, 1, hHookIsDebuggerPresent);
	}
	if (realLoadLibraryExW != NULL)
	{
		LhInstallHook(realLoadLibraryExW, MyLoadLibraryExW, NULL, hHookLoadLibraryExW);
		LhSetExclusiveACL(HookLoadLibraryExW_ACLEntries, 1, hHookLoadLibraryExW);
	}
	if (realLoadResource != NULL)
	{
		LhInstallHook(realLoadResource, MyLoadResource, NULL, hHookLoadResource);
		LhSetExclusiveACL(HookLoadResource_ACLEntries, 1, hHookLoadResource);
	}
	if (realModule32FirstW != NULL)
	{
		LhInstallHook(realModule32FirstW, MyModule32FirstW, NULL, hHookModule32FirstW);
		LhSetExclusiveACL(HookModule32FirstW_ACLEntries, 1, hHookModule32FirstW);
	}
	if (realModule32NextW != NULL)
	{
		LhInstallHook(realModule32NextW, MyModule32NextW, NULL, hHookModule32NextW);
		LhSetExclusiveACL(HookModule32NextW_ACLEntries, 1, hHookModule32NextW);
	}
	if (realOpenProcess != NULL)
	{
		LhInstallHook(realOpenProcess, MyOpenProcess, NULL, hHookOpenProcess);
		LhSetExclusiveACL(HookOpenProcess_ACLEntries, 1, hHookOpenProcess);
	}
	if (realPeekNamedPipe != NULL)
	{
		LhInstallHook(realPeekNamedPipe, MyPeekNamedPipe, NULL, hHookPeekNamedPipe);
		LhSetExclusiveACL(HookPeekNamedPipe_ACLEntries, 1, hHookPeekNamedPipe);
	}
	if (realProcess32First != NULL)
	{
		LhInstallHook(realProcess32First, MyProcess32First, NULL, hHookProcess32First);
		LhSetExclusiveACL(HookProcess32First_ACLEntries, 1, hHookProcess32First);
	}
	if (realProcess32Next != NULL)
	{
		LhInstallHook(realProcess32Next, MyProcess32Next, NULL, hHookProcess32Next);
		LhSetExclusiveACL(HookProcess32Next_ACLEntries, 1, hHookProcess32Next);
	}
	if (realQueryPerformanceCounter != NULL)
	{
		LhInstallHook(realQueryPerformanceCounter, MyQueryPerformanceCounter, NULL, hHookQueryPerformanceCounter);
		LhSetExclusiveACL(HookQueryPerformanceCounter_ACLEntries, 1, hHookQueryPerformanceCounter);
	}
	if (realQueueUserAPC != NULL)
	{
		LhInstallHook(realQueueUserAPC, MyQueueUserAPC, NULL, hHookQueueUserAPC);
		LhSetExclusiveACL(HookQueueUserAPC_ACLEntries, 1, hHookQueueUserAPC);
	}
	if (realReadProcessMemory != NULL)
	{
		LhInstallHook(realReadProcessMemory, MyReadProcessMemory, NULL, hHookReadProcessMemory);
		LhSetExclusiveACL(HookReadProcessMemory_ACLEntries, 1, hHookReadProcessMemory);
	}
	if (realResumeThread != NULL)
	{
		LhInstallHook(realResumeThread, MyResumeThread, NULL, hHookResumeThread);
		LhSetExclusiveACL(HookResumeThread_ACLEntries, 1, hHookResumeThread);
	}
	if (realSetThreadContext != NULL)
	{
		LhInstallHook(realSetThreadContext, MySetThreadContext, NULL, hHookSetThreadContext);
		LhSetExclusiveACL(HookSetThreadContext_ACLEntries, 1, hHookSetThreadContext);
	}
	if (realSuspendThread != NULL)
	{
		LhInstallHook(realSuspendThread, MySuspendThread, NULL, hHookSuspendThread);
		LhSetExclusiveACL(HookSuspendThread_ACLEntries, 1, hHookSuspendThread);
	}
	if (realThread32First != NULL)
	{
		LhInstallHook(realThread32First, MyThread32First, NULL, hHookThread32First);
		LhSetExclusiveACL(HookThread32First_ACLEntries, 1, hHookThread32First);
	}
	if (realThread32Next != NULL)
	{
		LhInstallHook(realThread32Next, MyThread32Next, NULL, hHookThread32Next);
		LhSetExclusiveACL(HookThread32Next_ACLEntries, 1, hHookThread32Next);
	}
	if (realToolhelp32ReadProcessMemory != NULL)
	{
		LhInstallHook(realToolhelp32ReadProcessMemory, MyToolhelp32ReadProcessMemory, NULL, hHookToolhelp32ReadProcessMemory);
		LhSetExclusiveACL(HookToolhelp32ReadProcessMemory_ACLEntries, 1, hHookToolhelp32ReadProcessMemory);
	}
	if (realVirtualAllocEx != NULL)
	{
		LhInstallHook(realVirtualAllocEx, MyVirtualAllocEx, NULL, hHookVirtualAllocEx);
		LhSetExclusiveACL(HookVirtualAllocEx_ACLEntries, 1, hHookVirtualAllocEx);
	}
	if (realVirtualProtectEx != NULL)
	{
		LhInstallHook(realVirtualProtectEx, MyVirtualProtectEx, NULL, hHookVirtualProtectEx);
		LhSetExclusiveACL(HookVirtualProtectEx_ACLEntries, 1, hHookVirtualProtectEx);
	}
	if (realWinExec != NULL)
	{
		LhInstallHook(realWinExec, MyWinExec, NULL, hHookWinExec);
		LhSetExclusiveACL(HookWinExec_ACLEntries, 1, hHookWinExec);
	}
	if (realWriteProcessMemory != NULL)
	{
		LhInstallHook(realWriteProcessMemory, MyWriteProcessMemory, NULL, hHookWriteProcessMemory);
		LhSetExclusiveACL(HookWriteProcessMemory_ACLEntries, 1, hHookWriteProcessMemory);
	}
	if (realRegisterHotKey != NULL)
	{
		//LhInstallHook(realRegisterHotKey,MyRegisterHotKey,NULL,hHookRegisterHotKey);
		//LhSetExclusiveACL(HookRegisterHotKey_ACLEntries, 1, hHookRegisterHotKey);
	}
	if (realCreateProcessA != NULL)
	{
		LhInstallHook(realCreateProcessA, MyCreateProcessA, NULL, hHookCreateProcessA);
		LhSetExclusiveACL(HookCreateProcessA_ACLEntries, 1, hHookCreateProcessA);
	}
	if (realCreateMutexW != NULL)
	{
		LhInstallHook(realCreateMutexW, MyCreateMutexW, NULL, hHookCreateMutexW);
		LhSetExclusiveACL(HookCreateMutexW_ACLEntries, 1, hHookCreateMutexW);
	}
	if (realFindResourceW != NULL)
	{
		//LhInstallHook(realFindResourceW,MyFindResourceW,NULL,hHookFindResourceW);
		//LhSetExclusiveACL(HookFindResourceW_ACLEntries, 1, hHookFindResourceW);
	}
	if (realFindWindowW != NULL)
	{
		LhInstallHook(realFindWindowW, MyFindWindowW, NULL, hHookFindWindowW);
		LhSetExclusiveACL(HookFindWindowW_ACLEntries, 1, hHookFindWindowW);
	}

	if (realGetWindowsDirectoryW != NULL)
	{
		LhInstallHook(realGetWindowsDirectoryW, MyGetWindowsDirectoryW, NULL, hHookGetWindowsDirectoryW);
		LhSetExclusiveACL(HookGetWindowsDirectoryW_ACLEntries, 1, hHookGetWindowsDirectoryW);
	}
	if (realMapVirtualKeyW != NULL)
	{
		LhInstallHook(realMapVirtualKeyW, MyMapVirtualKeyW, NULL, hHookMapVirtualKeyW);
		LhSetExclusiveACL(HookMapVirtualKeyW_ACLEntries, 1, hHookMapVirtualKeyW);
	}
	if (realOpenMutexW != NULL)
	{
		LhInstallHook(realOpenMutexW, MyOpenMutexW, NULL, hHookOpenMutexW);
		LhSetExclusiveACL(HookOpenMutexW_ACLEntries, 1, hHookOpenMutexW);
	}
	if (realOpenSCManagerW != NULL)
	{
		LhInstallHook(realOpenSCManagerW, MyOpenSCManagerW, NULL, hHookOpenSCManagerW);
		LhSetExclusiveACL(HookOpenSCManagerW_ACLEntries, 1, hHookOpenSCManagerW);
	}
	if (realCreateProcessW != NULL)
	{
		LhInstallHook(realCreateProcessW, MyCreateProcessW, NULL, hHookCreateProcessW);
		LhSetExclusiveACL(HookCreateProcessW_ACLEntries, 1, hHookCreateProcessW);
	}
	if (realCreateServiceW != NULL)
	{
		LhInstallHook(realCreateServiceW, MyCreateServiceW, NULL, hHookCreateServiceW);
		LhSetExclusiveACL(HookCreateServiceW_ACLEntries, 1, hHookCreateServiceW);
	}
	if (realGetModuleFileNameExW != NULL)
	{
		LhInstallHook(realGetModuleFileNameExW, MyGetModuleFileNameExW, NULL, hHookGetModuleFileNameExW);
		LhSetExclusiveACL(HookGetModuleFileNameExW_ACLEntries, 1, hHookGetModuleFileNameExW);
	}
	if (realGetModuleHandleW != NULL)
	{
		LhInstallHook(realGetModuleHandleW, MyGetModuleHandleW, NULL, hHookGetModuleHandleW);
		LhSetExclusiveACL(HookGetModuleHandleW_ACLEntries, 1, hHookGetModuleHandleW);
	}
	if (realGetStartupInfoW != NULL)
	{
		LhInstallHook(realGetStartupInfoW, MyGetStartupInfoW, NULL, hHookGetStartupInfoW);
		LhSetExclusiveACL(HookGetStartupInfoW_ACLEntries, 1, hHookGetStartupInfoW);
	}
	if (realGetVersionExW != NULL)
	{
		LhInstallHook(realGetVersionExW, MyGetVersionExW, NULL, hHookGetVersionExW);
		LhSetExclusiveACL(HookGetVersionExW_ACLEntries, 1, hHookGetVersionExW);
	}
	if (realLoadLibraryW != NULL)
	{
		LhInstallHook(realLoadLibraryW, MyLoadLibraryW, NULL, hHookLoadLibraryW);
		LhSetExclusiveACL(HookLoadLibraryW_ACLEntries, 1, hHookLoadLibraryW);
	}
	if (realOutputDebugStringW != NULL)
	{
		LhInstallHook(realOutputDebugStringW, MyOutputDebugStringW, NULL, hHookOutputDebugStringW);
		LhSetExclusiveACL(HookOutputDebugStringW_ACLEntries, 1, hHookOutputDebugStringW);
	}
	if (realSetWindowsHookExW != NULL)
	{
		LhInstallHook(realSetWindowsHookExW, MySetWindowsHookExW, NULL, hHookSetWindowsHookExW);
		LhSetExclusiveACL(HookSetWindowsHookExW_ACLEntries, 1, hHookSetWindowsHookExW);
	}
	if (realShellExecuteW != NULL)
	{
		LhInstallHook(realShellExecuteW, MyShellExecuteW, NULL, hHookShellExecuteW);
		LhSetExclusiveACL(HookShellExecuteW_ACLEntries, 1, hHookShellExecuteW);
	}
	if (realStartServiceCtrlDispatcherW != NULL)
	{
		LhInstallHook(realStartServiceCtrlDispatcherW, MyStartServiceCtrlDispatcherW, NULL, hHookStartServiceCtrlDispatcherW);
		LhSetExclusiveACL(HookStartServiceCtrlDispatcherW_ACLEntries, 1, hHookStartServiceCtrlDispatcherW);
	}
	if (realSetLocalTime != NULL)
	{
		LhInstallHook(realSetLocalTime, MySetLocalTime, NULL, hHookSetLocalTime);
		LhSetExclusiveACL(HookSetLocalTime_ACLEntries, 1, hHookSetLocalTime);
	}
	if (realTerminateThread != NULL)
	{
		LhInstallHook(realTerminateThread, MyTerminateThread, NULL, hHookTerminateThread);
		LhSetExclusiveACL(HookTerminateThread_ACLEntries, 1, hHookTerminateThread);
	}
	if (realVirtualFree != NULL)
	{
		LhInstallHook(realVirtualFree, MyVirtualFree, NULL, hHookVirtualFree);
		LhSetExclusiveACL(HookVirtualFree_ACLEntries, 1, hHookVirtualFree);
	}
	if (realSetProcessWorkingSetSize != NULL)
	{
		LhInstallHook(realSetProcessWorkingSetSize, MySetProcessWorkingSetSize, NULL, hHookSetProcessWorkingSetSize);
		LhSetExclusiveACL(HookSetProcessWorkingSetSize_ACLEntries, 1, hHookSetProcessWorkingSetSize);
	}
	if (realTerminateProcess != NULL)
	{
		LhInstallHook(realTerminateProcess, MyTerminateProcess, NULL, hHookTerminateProcess);
		LhSetExclusiveACL(HookTerminateProcess_ACLEntries, 1, hHookTerminateProcess);
	}
	//ProcessAPI DoHook finished

	//NetworkAPI DoHook
	//NetworkAPI DoHook finished

	//RegAPI DoHook
	if (realRegOpenKeyExW != NULL)
	{
		LhInstallHook(realRegOpenKeyExW, MyRegOpenKeyExW, NULL, hHookRegOpenKeyExW);
		LhSetExclusiveACL(HookRegOpenKeyExW_ACLEntries, 1, hHookRegOpenKeyExW);
	}
	if (realRegOpenKeyW != NULL)
	{
		LhInstallHook(realRegOpenKeyW, MyRegOpenKeyW, NULL, hHookRegOpenKeyW);
		LhSetExclusiveACL(HookRegOpenKeyW_ACLEntries, 1, hHookRegOpenKeyW);
	}
	if (realRegCreateKeyExW != NULL)
	{
		LhInstallHook(realRegCreateKeyExW, MyRegCreateKeyExW, NULL, hHookRegCreateKeyExW);
		LhSetExclusiveACL(HookRegCreateKeyExW_ACLEntries, 1, hHookRegCreateKeyExW);
	}
	if (realRegCreateKeyW != NULL)
	{
		LhInstallHook(realRegCreateKeyW, MyRegCreateKeyW, NULL, hHookRegCreateKeyW);
		LhSetExclusiveACL(HookRegCreateKeyW_ACLEntries, 1, hHookRegCreateKeyW);
	}
	if (realRegQueryValueExW != NULL)
	{
		LhInstallHook(realRegQueryValueExW, MyRegQueryValueExW, NULL, hHookRegQueryValueExW);
		LhSetExclusiveACL(HookRegQueryValueExW_ACLEntries, 1, hHookRegQueryValueExW);
	}
	if (realRegQueryValueW != NULL)
	{
		LhInstallHook(realRegQueryValueW, MyRegQueryValueW, NULL, hHookRegQueryValueW);
		LhSetExclusiveACL(HookRegQueryValueW_ACLEntries, 1, hHookRegQueryValueW);
	}
	if (realRegSetValueExW != NULL)
	{
		LhInstallHook(realRegSetValueExW, MyRegSetValueExW, NULL, hHookRegSetValueExW);
		LhSetExclusiveACL(HookRegSetValueExW_ACLEntries, 1, hHookRegSetValueExW);
	}
	if (realRegSetValueW != NULL)
	{
		LhInstallHook(realRegSetValueW, MyRegSetValueW, NULL, hHookRegSetValueW);
		LhSetExclusiveACL(HookRegSetValueW_ACLEntries, 1, hHookRegSetValueW);
	}
	if (realRegDeleteKeyExW != NULL)
	{
		LhInstallHook(realRegDeleteKeyExW, MyRegDeleteKeyExW, NULL, hHookRegDeleteKeyExW);
		LhSetExclusiveACL(HookRegDeleteKeyExW_ACLEntries, 1, hHookRegDeleteKeyExW);
	}
	if (realRegDeleteKeyW != NULL)
	{
		LhInstallHook(realRegDeleteKeyW, MyRegDeleteKeyW, NULL, hHookRegDeleteKeyW);
		LhSetExclusiveACL(HookRegDeleteKeyW_ACLEntries, 1, hHookRegDeleteKeyW);
	}
	if (realRegSetKeySecurity != NULL)
	{
		LhInstallHook(realRegSetKeySecurity, MyRegSetKeySecurity, NULL, hHookRegSetKeySecurity);
		LhSetExclusiveACL(HookRegSetKeySecurity_ACLEntries, 1, hHookRegSetKeySecurity);
	}
	if (realRegRestoreKeyW != NULL)
	{
		LhInstallHook(realRegRestoreKeyW, MyRegRestoreKeyW, NULL, hHookRegRestoreKeyW);
		LhSetExclusiveACL(HookRegRestoreKeyW_ACLEntries, 1, hHookRegRestoreKeyW);
	}
	if (realRegReplaceKeyW != NULL)
	{
		LhInstallHook(realRegReplaceKeyW, MyRegReplaceKeyW, NULL, hHookRegReplaceKeyW);
		LhSetExclusiveACL(HookRegReplaceKeyW_ACLEntries, 1, hHookRegReplaceKeyW);
	}
	if (realRegLoadKeyW != NULL)
	{
		LhInstallHook(realRegLoadKeyW, MyRegLoadKeyW, NULL, hHookRegLoadKeyW);
		LhSetExclusiveACL(HookRegLoadKeyW_ACLEntries, 1, hHookRegLoadKeyW);
	}
	if (realRegUnLoadKey != NULL)
	{
		LhInstallHook(realRegUnLoadKey, MyRegUnLoadKey, NULL, hHookRegUnLoadKey);
		LhSetExclusiveACL(HookRegUnLoadKey_ACLEntries, 1, hHookRegUnLoadKey);
	}
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
	delete      hHookBitBlt;
	delete      hHookCreateFileMappingW;
	delete      hHookOpenFileMappingW;
	delete      hHookDeviceIoControl;
	delete      hHookFindWindowExW;
	delete      hHookGetAsyncKeyState;
	delete      hHookGetDC;
	delete      hHookGetForegroundWindow;
	delete      hHookGetKeyState;
	delete      hHookGetTempPath;
	delete      hHookMapViewOfFile;
	delete      hHookOpenFile;
	delete      hHookAdjustTokenPrivileges;
	delete      hHookAttachThreadInput;
	delete      hHookCallNextHookEx;
	delete      hHookCheckRemoteDebuggerPresent;
	delete      hHookControlService;
	delete      hHookCreateRemoteThread;
	delete      hHookCreateToolhelp32Snapshot;
	delete      hHookEnumProcesses;
	delete      hHookEnumProcessModules;
	delete      hHookGetProcAddress;
	delete      hHookGetSystemDefaultLangID;
	delete      hHookGetThreadContext;
	delete      hHookGetTickCount;
	delete      hHookIsDebuggerPresent;
	delete      hHookLoadLibraryExW;
	delete      hHookLoadResource;
	delete      hHookModule32FirstW;
	delete      hHookModule32NextW;
	delete      hHookOpenProcess;
	delete      hHookPeekNamedPipe;
	delete      hHookProcess32First;
	delete      hHookProcess32Next;
	delete      hHookQueryPerformanceCounter;
	delete      hHookQueueUserAPC;
	delete      hHookReadProcessMemory;
	delete      hHookResumeThread;
	delete      hHookSetThreadContext;
	delete      hHookSuspendThread;
	delete      hHookThread32First;
	delete      hHookThread32Next;
	delete      hHookToolhelp32ReadProcessMemory;
	delete      hHookVirtualAllocEx;
	delete      hHookVirtualProtectEx;
	delete      hHookWinExec;
	delete      hHookWriteProcessMemory;
	delete      hHookRegisterHotKey;
	delete      hHookCreateProcessA;
	delete      hHookCreateMutexW;
	delete      hHookFindResourceW;
	delete      hHookFindWindowW;
	delete      hHookGetWindowsDirectoryW;
	delete      hHookMapVirtualKeyW;
	delete      hHookOpenMutexW;
	delete      hHookOpenSCManagerW;
	delete      hHookCreateProcessW;
	delete      hHookCreateServiceW;
	delete      hHookGetModuleFileNameExW;
	delete      hHookGetModuleHandleW;
	delete      hHookGetStartupInfoW;
	delete      hHookGetVersionExW;
	delete      hHookLoadLibraryW;
	delete      hHookOutputDebugStringW;
	delete      hHookSetWindowsHookExW;
	delete      hHookShellExecuteW;
	delete      hHookStartServiceCtrlDispatcherW;
	delete      hHookSetLocalTime;
	delete      hHookTerminateThread;
	delete      hHookVirtualFree;
	delete      hHookSetProcessWorkingSetSize;
	delete      hHookTerminateProcess;

	hHookBitBlt = NULL;
	hHookCreateFileMappingW = NULL;
	hHookOpenFileMappingW = NULL;
	hHookDeviceIoControl = NULL;
	hHookFindWindowExW = NULL;
	hHookGetAsyncKeyState = NULL;
	hHookGetDC = NULL;
	hHookGetForegroundWindow = NULL;
	hHookGetKeyState = NULL;
	hHookGetTempPath = NULL;
	hHookMapViewOfFile = NULL;
	hHookOpenFile = NULL;
	hHookAdjustTokenPrivileges = NULL;
	hHookAttachThreadInput = NULL;
	hHookCallNextHookEx = NULL;
	hHookCheckRemoteDebuggerPresent = NULL;
	hHookControlService = NULL;
	hHookCreateRemoteThread = NULL;
	hHookCreateToolhelp32Snapshot = NULL;
	hHookEnumProcesses = NULL;
	hHookEnumProcessModules = NULL;
	hHookGetProcAddress = NULL;
	hHookGetSystemDefaultLangID = NULL;
	hHookGetThreadContext = NULL;
	hHookGetTickCount = NULL;
	hHookIsDebuggerPresent = NULL;
	hHookLoadLibraryExW = NULL;
	hHookLoadResource = NULL;
	hHookModule32FirstW = NULL;
	hHookModule32NextW = NULL;
	hHookOpenProcess = NULL;
	hHookPeekNamedPipe = NULL;
	hHookProcess32First = NULL;
	hHookProcess32Next = NULL;
	hHookQueryPerformanceCounter = NULL;
	hHookQueueUserAPC = NULL;
	hHookReadProcessMemory = NULL;
	hHookResumeThread = NULL;
	hHookSetThreadContext = NULL;
	hHookSuspendThread = NULL;
	hHookThread32First = NULL;
	hHookThread32Next = NULL;
	hHookToolhelp32ReadProcessMemory = NULL;
	hHookVirtualAllocEx = NULL;
	hHookVirtualProtectEx = NULL;
	hHookWinExec = NULL;
	hHookWriteProcessMemory = NULL;
	hHookRegisterHotKey = NULL;
	hHookCreateProcessA = NULL;
	hHookCreateMutexW = NULL;
	hHookFindResourceW = NULL;
	hHookFindWindowW = NULL;
	hHookGetWindowsDirectoryW = NULL;
	hHookMapVirtualKeyW = NULL;
	hHookOpenMutexW = NULL;
	hHookOpenSCManagerW = NULL;
	hHookCreateProcessW = NULL;
	hHookCreateServiceW = NULL;
	hHookGetModuleFileNameExW = NULL;
	hHookGetModuleHandleW = NULL;
	hHookGetStartupInfoW = NULL;
	hHookGetVersionExW = NULL;
	hHookLoadLibraryW = NULL;
	hHookOutputDebugStringW = NULL;
	hHookSetWindowsHookExW = NULL;
	hHookShellExecuteW = NULL;
	hHookStartServiceCtrlDispatcherW = NULL;
	hHookSetLocalTime = NULL;
	hHookTerminateThread = NULL;
	hHookVirtualFree = NULL;
	hHookSetProcessWorkingSetSize = NULL;
	hHookTerminateProcess = NULL;
	//ProcessAPI DoUnHook finished

	//NetworkAPI DoUnHook
	//NetworkAPI DoUnHook finished

	//RegAPI DoUnHook
	delete      hHookRegOpenKeyExW;
	delete      hHookRegOpenKeyW;
	delete      hHookRegCreateKeyExW;
	delete      hHookRegCreateKeyW;
	delete      hHookRegQueryValueExW;
	delete      hHookRegQueryValueW;
	delete      hHookRegSetValueExW;
	delete      hHookRegSetValueW;
	delete      hHookRegDeleteKeyExW;
	delete      hHookRegDeleteKeyW;
	delete      hHookRegSetKeySecurity;
	delete      hHookRegRestoreKeyW;
	delete      hHookRegReplaceKeyW;
	delete      hHookRegLoadKeyW;
	delete      hHookRegUnLoadKey;

	hHookRegOpenKeyExW = NULL;
	hHookRegOpenKeyW = NULL;
	hHookRegCreateKeyExW = NULL;
	hHookRegCreateKeyW = NULL;
	hHookRegQueryValueExW = NULL;
	hHookRegQueryValueW = NULL;
	hHookRegSetValueExW = NULL;
	hHookRegSetValueW = NULL;
	hHookRegDeleteKeyExW = NULL;
	hHookRegDeleteKeyW = NULL;
	hHookRegSetKeySecurity = NULL;
	hHookRegRestoreKeyW = NULL;
	hHookRegReplaceKeyW = NULL;
	hHookRegLoadKeyW = NULL;
	hHookRegUnLoadKey = NULL;
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
