#include "stdafx.h"
#include "ProcessAPI.h"

BOOL WINAPI MyBitBlt(_In_ HDC hdc, _In_ int x, _In_ int y, _In_ int cx, _In_ int cy, _In_opt_ HDC hdcSrc, _In_ int x1, _In_ int y1, _In_ DWORD rop)
{

	return (realBitBlt)(hdc, x, y, cx, cy, hdcSrc, x1, y1, rop);
}

HANDLE WINAPI MyCreateFileMappingW(
	HANDLE hFile,
	LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
	DWORD flProtect,
	DWORD dwMaximumSizeHigh,
	DWORD dwMaximumSizeLow,
	LPCWSTR lpName
)
{
	char hFilepath[512] = "NULL";
	if (hFile != NULL)
	{
		GetFinalPathNameByHandleA(hFile, hFilepath, MAX_PATH, VOLUME_NAME_DOS);
	}

	return (realCreateFileMappingW)(hFile, lpFileMappingAttributes, flProtect, dwMaximumSizeHigh, dwMaximumSizeLow, lpName);
}

HANDLE WINAPI MyOpenFileMappingW(_In_ DWORD dwDesiredAccess, _In_ BOOL bInheritHandle, _In_ LPCWSTR lpName) {

	return (realOpenFileMappingW)(dwDesiredAccess, bInheritHandle, lpName);
}


BOOL WINAPI MyDeviceIoControl(
	_In_        HANDLE       hDevice,
	_In_        DWORD        dwIoControlCode,
	_In_opt_    LPVOID       lpInBuffer,
	_In_        DWORD        nInBufferSize,
	_Out_opt_   LPVOID       lpOutBuffer,
	_In_        DWORD        nOutBufferSize,
	_Out_opt_   LPDWORD      lpBytesReturned,
	_Inout_opt_ LPOVERLAPPED lpOverlapped
)
{

	return (realDeviceIoControl)(hDevice, dwIoControlCode, lpInBuffer, nInBufferSize, lpOutBuffer, nOutBufferSize, lpBytesReturned, lpOverlapped);
}

HWND WINAPI MyFindWindowExW(
	_In_opt_ HWND    hwndParent,
	_In_opt_ HWND    hwndChildAfter,
	_In_opt_ LPCWSTR lpszClass,
	_In_opt_ LPCWSTR lpszWindow
)
{

	return (realFindWindowExW)(hwndParent, hwndChildAfter, lpszClass, lpszWindow);
}

SHORT WINAPI MyGetAsyncKeyState(
	_In_ int vKey
)
{

	return (realGetAsyncKeyState)(vKey);
}

HDC WINAPI MyGetDC(
	_In_ HWND hWnd
)
{


	return (realGetDC)(hWnd);
}

HWND WINAPI MyGetForegroundWindow(void)
{
	HWND h;
	h = (realGetForegroundWindow)();
	int len = 0;
	len = GetWindowTextLengthA(h);
	char win[MAX_PATH] = "NULL";

	return h;
}

SHORT WINAPI MyGetKeyState(
	_In_ int nVirtKey
)
{

	return (realGetKeyState)(nVirtKey);
}

DWORD WINAPI MyGetTempPath(
	DWORD nBufferLength,
	LPTSTR lpBuffer
)
{


	return (realGetTempPath)(nBufferLength, lpBuffer);
}

LPVOID WINAPI MyMapViewOfFile(
	_In_ HANDLE hFileMappingObject,
	_In_ DWORD  dwDesiredAccess,
	_In_ DWORD  dwFileOffsetHigh,
	_In_ DWORD  dwFileOffsetLow,
	_In_ SIZE_T dwNumberOfBytesToMap
)
{

	return (realMapViewOfFile)(hFileMappingObject, dwDesiredAccess, dwFileOffsetHigh, dwFileOffsetLow, dwNumberOfBytesToMap);
}

HFILE WINAPI MyOpenFile(
	_In_  LPCSTR     lpFileName,
	_Out_ LPOFSTRUCT lpReOpenBuff,
	_In_  UINT       uStyle
)
{

	return (realOpenFile)(lpFileName, lpReOpenBuff, uStyle);
}

BOOL WINAPI MyAdjustTokenPrivileges(
	_In_      HANDLE            TokenHandle,
	_In_      BOOL              DisableAllPrivileges,
	_In_opt_  PTOKEN_PRIVILEGES NewState,
	_In_      DWORD             BufferLength,
	_Out_opt_ PTOKEN_PRIVILEGES PreviousState,
	_Out_opt_ PDWORD            ReturnLength
)
{

	return (realAdjustTokenPrivileges)(TokenHandle, DisableAllPrivileges, NewState, BufferLength, PreviousState, ReturnLength);
}

BOOL WINAPI MyAttachThreadInput(
	_In_ DWORD idAttach,
	_In_ DWORD idAttachTo,
	_In_ BOOL  fAttach
)
{

	return (realAttachThreadInput)(idAttach, idAttachTo, fAttach);
}

LRESULT WINAPI MyCallNextHookEx(
	_In_opt_ HHOOK  hhk,
	_In_     int    nCode,
	_In_     WPARAM wParam,
	_In_     LPARAM lParam
)
{

	return (realCallNextHookEx)(hhk, nCode, wParam, lParam);
}

BOOL WINAPI MyCheckRemoteDebuggerPresent(
	_In_    HANDLE hProcess,
	_Inout_ PBOOL  pbDebuggerPresent
)
{
	char buf[MAX_PATH] = "NULL";
	GetModuleFileNameExA(hProcess, 0, buf, MAX_PATH);

	return (realCheckRemoteDebuggerPresent)(hProcess, pbDebuggerPresent);
}

BOOL WINAPI MyControlService(
	_In_  SC_HANDLE        hService,
	_In_  DWORD            dwControl,
	_Out_ LPSERVICE_STATUS lpServiceStatus
)
{

	return (realControlService)(hService, dwControl, lpServiceStatus);
}

HANDLE WINAPI MyCreateRemoteThread(
	_In_  HANDLE                 hProcess,
	_In_  LPSECURITY_ATTRIBUTES  lpThreadAttributes,
	_In_  SIZE_T                 dwStackSize,
	_In_  LPTHREAD_START_ROUTINE lpStartAddress,
	_In_  LPVOID                 lpParameter,
	_In_  DWORD                  dwCreationFlags,
	_Out_ LPDWORD                lpThreadId
)
{

	return (realCreateRemoteThread)(hProcess, lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
}

HANDLE WINAPI MyCreateToolhelp32Snapshot(
	_In_ DWORD dwFlags,
	_In_ DWORD th32ProcessID
)
{

	return (realCreateToolhelp32Snapshot)(dwFlags, th32ProcessID);
}

BOOL WINAPI MyEnumProcesses(
	_Out_ DWORD *lpidProcess,
	_In_  DWORD cb,
	_Out_ LPDWORD lpcbNeeded
)
{

	return (realEnumProcesses)(lpidProcess, cb, lpcbNeeded);
}

BOOL WINAPI MyEnumProcessModules(
	_In_ HANDLE hProcess,
	_Out_  HMODULE *lphModule,
	_In_   DWORD cb,
	_Out_  LPDWORD lpcbNeeded
)
{
	char buf[MAX_PATH] = "NULL";
	GetModuleFileNameExA(hProcess, 0, buf, MAX_PATH);

	return (realEnumProcessModules)(hProcess, lphModule, cb, lpcbNeeded);
}

FARPROC WINAPI MyGetProcAddress(
	_In_ HMODULE hModule,
	_In_ LPCSTR  lpProcName
)
{

	return (realGetProcAddress)(hModule, lpProcName);
}

LANGID WINAPI MyGetSystemDefaultLangID(void)
{

	return (realGetSystemDefaultLangID)();
}

BOOL WINAPI MyGetThreadContext(
	_In_    HANDLE    hThread,
	_Inout_ LPCONTEXT lpContext
)
{

	return (realGetThreadContext)(hThread, lpContext);
}

DWORD WINAPI MyGetTickCount(void)
{

	return (realGetTickCount)();
}

BOOL WINAPI MyIsDebuggerPresent(void)
{

	return (realIsDebuggerPresent)();
}

HMODULE WINAPI MyLoadLibraryExW(
	_In_       LPCWSTR lpLibFileName,
	_Reserved_ HANDLE  hFile,
	_In_       DWORD   dwFlags
)
{

	return (realLoadLibraryExW)(lpLibFileName, hFile, dwFlags);
}

HGLOBAL WINAPI MyLoadResource(
	_In_opt_ HMODULE hModule,
	_In_     HRSRC   hResInfo
)
{
	char modulestr[MAX_PATH] = "NULL";
	GetModuleFileNameA(hModule, modulestr, MAX_PATH);

	return (realLoadResource)(hModule, hResInfo);
}


BOOL WINAPI MyModule32FirstW(
	_In_    HANDLE          hSnapshot,
	_Inout_ LPMODULEENTRY32W lpme
)
{

	return (realModule32FirstW)(hSnapshot, lpme);
}

BOOL WINAPI MyModule32NextW(
	_In_  HANDLE          hSnapshot,
	_Out_ LPMODULEENTRY32W lpme
)
{

	return (realModule32NextW)(hSnapshot, lpme);
}

HANDLE WINAPI MyOpenProcess(
	_In_ DWORD dwDesiredAccess,
	_In_ BOOL  bInheritHandle,
	_In_ DWORD dwProcessId
)
{

	return (realOpenProcess)(dwDesiredAccess, bInheritHandle, dwProcessId);
}
BOOL WINAPI MyPeekNamedPipe(
	_In_      HANDLE  hNamedPipe,
	_Out_opt_ LPVOID  lpBuffer,
	_In_      DWORD   nBufferSize,
	_Out_opt_ LPDWORD lpBytesRead,
	_Out_opt_ LPDWORD lpTotalBytesAvail,
	_Out_opt_ LPDWORD lpBytesLeftThisMessage
)
{

	return (realPeekNamedPipe)(hNamedPipe, lpBuffer, nBufferSize, lpBytesRead, lpTotalBytesAvail, lpBytesLeftThisMessage);
}

BOOL WINAPI MyProcess32First(
	_In_    HANDLE           hSnapshot,
	_Inout_ LPPROCESSENTRY32 lppe
)
{

	return (realProcess32First)(hSnapshot, lppe);
}

BOOL WINAPI MyProcess32Next(
	_In_  HANDLE           hSnapshot,
	_Out_ LPPROCESSENTRY32 lppe
)
{

	return (realProcess32Next)(hSnapshot, lppe);
}

BOOL WINAPI MyQueryPerformanceCounter(
	_Out_ LARGE_INTEGER *lpPerformanceCount
)
{

	return (realQueryPerformanceCounter)(lpPerformanceCount);
}

DWORD WINAPI MyQueueUserAPC(
	_In_ PAPCFUNC  pfnAPC,
	_In_ HANDLE    hThread,
	_In_ ULONG_PTR dwData
)
{

	return (realQueueUserAPC)(pfnAPC, hThread, dwData);
}

BOOL WINAPI MyReadProcessMemory(
	_In_  HANDLE  hProcess,
	_In_  LPCVOID lpBaseAddress,
	_Out_ LPVOID  lpBuffer,
	_In_  SIZE_T  nSize,
	_Out_ SIZE_T  *lpNumberOfBytesRead
)
{

	return (realReadProcessMemory)(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesRead);
}

DWORD WINAPI MyResumeThread(
	_In_ HANDLE hThread
)
{

	return (realResumeThread)(hThread);
}

BOOL WINAPI MySetThreadContext(
	_In_       HANDLE  hThread,
	_In_ const CONTEXT *lpContext
)
{


	return (realSetThreadContext)(hThread, lpContext);
}

DWORD WINAPI MySuspendThread(
	_In_ HANDLE hThread
)
{

	return (realSuspendThread)(hThread);
}

BOOL WINAPI MyThread32First(
	_In_    HANDLE          hSnapshot,
	_Inout_ LPTHREADENTRY32 lpte
)
{

	return (realThread32First)(hSnapshot, lpte);
}

BOOL WINAPI MyThread32Next(
	_In_  HANDLE          hSnapshot,
	_Out_ LPTHREADENTRY32 lpte
)
{

	return (realThread32Next)(hSnapshot, lpte);
}

BOOL WINAPI MyToolhelp32ReadProcessMemory(
	_In_  DWORD   th32ProcessID,
	_In_  LPCVOID lpBaseAddress,
	_Out_ LPVOID  lpBuffer,
	_In_  SIZE_T  cbRead,
	_Out_ SIZE_T  lpNumberOfBytesRead
)
{

	return (realToolhelp32ReadProcessMemory)(th32ProcessID, lpBaseAddress, lpBuffer, cbRead, lpNumberOfBytesRead);
}

LPVOID WINAPI MyVirtualAllocEx(
	_In_     HANDLE hProcess,
	_In_opt_ LPVOID lpAddress,
	_In_     SIZE_T dwSize,
	_In_     DWORD  flAllocationType,
	_In_     DWORD  flProtect
)
{
	//LPSTR buf="NULL";
	char buf[MAX_PATH] = "NULL";
	GetModuleFileNameExA(hProcess, 0, buf, MAX_PATH);

	return (realVirtualAllocEx)(hProcess, lpAddress, dwSize, flAllocationType, flProtect);
}

BOOL WINAPI MyVirtualProtectEx(
	_In_  HANDLE hProcess,
	_In_  LPVOID lpAddress,
	_In_  SIZE_T dwSize,
	_In_  DWORD  flNewProtect,
	_Out_ PDWORD lpflOldProtect
)
{
	char buf[MAX_PATH] = "NULL";
	GetModuleFileNameExA(hProcess, 0, buf, MAX_PATH);

	return (realVirtualProtectEx)(hProcess, lpAddress, dwSize, flNewProtect, lpflOldProtect);
}

UINT WINAPI MyWinExec(
	_In_ LPCSTR lpCmdLine,
	_In_ UINT   uCmdShow
)
{

	return (realWinExec)(lpCmdLine, uCmdShow);
}

BOOL WINAPI MyWriteProcessMemory(
	_In_  HANDLE  hProcess,
	_In_  LPVOID  lpBaseAddress,
	_In_  LPCVOID lpBuffer,
	_In_  SIZE_T  nSize,
	_Out_ SIZE_T  *lpNumberOfBytesWritten
)
{

	return (realWriteProcessMemory)(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesWritten);
}

BOOL WINAPI MyRegisterHotKey(
	_In_opt_ HWND hWnd,
	_In_     int  id,
	_In_     UINT fsModifiers,
	_In_     UINT vk
)
{
	char win[MAX_PATH] = "NULL";
	int len = 0;
	if (hWnd != NULL)
	{
		len = GetWindowTextLengthA(hWnd);
		GetWindowTextA(hWnd, win, len);
	}

	return (realRegisterHotKey)(hWnd, id, fsModifiers, vk);
}

BOOL WINAPI MyCreateProcessA(
	_In_opt_    LPCSTR               lpApplicationName,
	_Inout_opt_ LPSTR                lpCommandLine,
	_In_opt_    LPSECURITY_ATTRIBUTES lpProcessAttributes,
	_In_opt_    LPSECURITY_ATTRIBUTES lpThreadAttributes,
	_In_        BOOL                  bInheritHandles,
	_In_        DWORD                 dwCreationFlags,
	_In_opt_    LPVOID                lpEnvironment,
	_In_opt_    LPCSTR               lpCurrentDirectory,
	_In_        LPSTARTUPINFOA         lpStartupInfo,
	_Out_       LPPROCESS_INFORMATION lpProcessInformation
)
{
	BOOL res = FALSE;
	res = (realCreateProcessA)(lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation);

	return res;
}

BOOL WINAPI	MyCreateProcessW(
	_In_opt_    LPCWSTR               lpApplicationName,
	_Inout_opt_ LPTSTR                lpCommandLine,
	_In_opt_    LPSECURITY_ATTRIBUTES lpProcessAttributes,
	_In_opt_    LPSECURITY_ATTRIBUTES lpThreadAttributes,
	_In_        BOOL                  bInheritHandles,
	_In_        DWORD                 dwCreationFlags,
	_In_opt_    LPVOID                lpEnvironment,
	_In_opt_    LPCWSTR               lpCurrentDirectory,
	_In_        LPSTARTUPINFO         lpStartupInfo,
	_Out_       LPPROCESS_INFORMATION lpProcessInformation
)
{
	BOOL res = FALSE;
	res = (realCreateProcessW)(lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation);
	return res;
}

HANDLE WINAPI MyCreateMutexW(
	_In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes,
	_In_     BOOL                  bInitialOwner,
	_In_opt_ LPCWSTR               lpName
)
{

	return (realCreateMutexW)(lpMutexAttributes, bInitialOwner, lpName);
}

HRSRC WINAPI MyFindResourceW(
	_In_opt_ HMODULE hModule,
	_In_     LPCWSTR lpName,
	_In_     LPCWSTR lpType
)
{

	return (realFindResourceW)(hModule, lpName, lpType);
}

HWND WINAPI MyFindWindowW(
	_In_opt_ LPCWSTR lpClassName,
	_In_opt_ LPCWSTR lpWindowName
)
{

	return (realFindWindowW)(lpClassName, lpWindowName);
}

UINT WINAPI MyGetWindowsDirectoryW(
	_Out_ LPTSTR lpBuffer,
	_In_  UINT   uSize
)
{
	UINT res = (realGetWindowsDirectoryW)(lpBuffer, uSize);

	return res;
}

UINT WINAPI MyMapVirtualKeyW(
	_In_ UINT uCode,
	_In_ UINT uMapType
)
{

	return (realMapVirtualKeyW)(uCode, uMapType);
}

HANDLE WINAPI MyOpenMutexW(
	_In_ DWORD   dwDesiredAccess,
	_In_ BOOL    bInheritHandle,
	_In_ LPCWSTR lpName
)
{
	return (realOpenMutexW)(dwDesiredAccess, bInheritHandle, lpName);
}

SC_HANDLE WINAPI MyOpenSCManagerW(
	_In_opt_ LPCWSTR lpMachineName,
	_In_opt_ LPCWSTR lpDatabaseName,
	_In_     DWORD   dwDesiredAccess
)
{

	return (realOpenSCManagerW)(lpMachineName, lpDatabaseName, dwDesiredAccess);
}



SC_HANDLE WINAPI MyCreateServiceW(
	_In_      SC_HANDLE hSCManager,
	_In_      LPCWSTR   lpServiceName,
	_In_opt_  LPCWSTR   lpDisplayName,
	_In_      DWORD     dwDesiredAccess,
	_In_      DWORD     dwServiceType,
	_In_      DWORD     dwStartType,
	_In_      DWORD     dwErrorControl,
	_In_opt_  LPCWSTR   lpBinaryPathName,
	_In_opt_  LPCWSTR   lpLoadOrderGroup,
	_Out_opt_ LPDWORD   lpdwTagId,
	_In_opt_  LPCWSTR   lpDependencies,
	_In_opt_  LPCWSTR   lpServiceStartName,
	_In_opt_  LPCWSTR   lpPassword
)
{


	return (realCreateServiceW)(hSCManager, lpServiceName, lpDisplayName, dwDesiredAccess, dwServiceType, dwStartType, dwErrorControl, lpBinaryPathName, lpLoadOrderGroup, lpdwTagId, lpDependencies, lpServiceStartName, lpPassword);
}

DWORD WINAPI MyGetModuleFileNameExW(
	_In_     HANDLE  hProcess,
	_In_opt_ HMODULE hModule,
	_Out_    LPTSTR  lpFilename,
	_In_     DWORD   nSize
)
{
	char buf[MAX_PATH] = "NULL";
	GetModuleFileNameExA(hProcess, 0, buf, MAX_PATH);
	char modulestr[MAX_PATH] = "NULL";
	if (hModule != NULL)
	{
		GetModuleFileNameA(hModule, modulestr, MAX_PATH);
	}

	return (realGetModuleFileNameExW)(hProcess, hModule, lpFilename, nSize);
}

HMODULE WINAPI MyGetModuleHandleW(
	_In_opt_ LPCWSTR lpModuleName
)
{

	return (realGetModuleHandleW)(lpModuleName);
}

VOID WINAPI MyGetStartupInfoW(
	_Out_ LPSTARTUPINFOW lpStartupInfo
)
{

	return (realGetStartupInfoW)(lpStartupInfo);
}

BOOL WINAPI	MyGetVersionExW(
	_Inout_ LPOSVERSIONINFO lpVersionInfo
)
{

	return (realGetVersionExW)(lpVersionInfo);
}

HMODULE WINAPI MyLoadLibraryW(
	_In_ LPCWSTR lpLibFileName
)
{

	return (realLoadLibraryW)(lpLibFileName);
}

void WINAPI MyOutputDebugStringW(
	_In_opt_ LPCWSTR lpOutputString
)
{

	return (realOutputDebugStringW)(lpOutputString);
}

HHOOK WINAPI MySetWindowsHookExW(
	_In_ int       idHook,
	_In_ HOOKPROC  lpfn,
	_In_ HINSTANCE hMod,
	_In_ DWORD     dwThreadId
)
{

	return (realSetWindowsHookExW)(idHook, lpfn, hMod, dwThreadId);
}

HINSTANCE WINAPI MyShellExecuteW(
	_In_opt_ HWND    hwnd,
	_In_opt_ LPCWSTR lpOperation,
	_In_     LPCWSTR lpFile,
	_In_opt_ LPCWSTR lpParameters,
	_In_opt_ LPCWSTR lpDirectory,
	_In_     INT     nShowCmd
)
{
	int len = 0;
	char win[MAX_PATH] = "NULL";
	if (hwnd != NULL)
	{
		len = GetWindowTextLengthA(hwnd);
		GetWindowTextA(hwnd, win, len);
	}


	return (realShellExecuteW)(hwnd, lpOperation, lpFile, lpParameters, lpDirectory, nShowCmd);
}

BOOL WINAPI MyStartServiceCtrlDispatcherW(
	_In_ const SERVICE_TABLE_ENTRY *lpServiceStartTable
)
{

	return (realStartServiceCtrlDispatcherW)(lpServiceStartTable);
}

BOOL WINAPI MySetLocalTime(
	_In_ const SYSTEMTIME *lpSystemTime
)
{

	return (realSetLocalTime)(lpSystemTime);
}

BOOL WINAPI MyTerminateThread(
	_Inout_ HANDLE hThread,
	_In_    DWORD  dwExitCode
)
{

	return (realTerminateThread)(hThread, dwExitCode);
}

BOOL WINAPI MyVirtualFree(
	_In_ LPVOID lpAddress,
	_In_ SIZE_T dwSize,
	_In_ DWORD  dwFreeType
)
{

	return (realVirtualFree)(lpAddress, dwSize, dwFreeType);
}

BOOL WINAPI MySetProcessWorkingSetSize(
	_In_ HANDLE hProcess,
	_In_ SIZE_T dwMinimumWorkingSetSize,
	_In_ SIZE_T dwMaximumWorkingSetSize
)
{
	char buf[MAX_PATH] = "NULL";
	GetModuleFileNameExA(hProcess, 0, buf, MAX_PATH);

	return (realSetProcessWorkingSetSize)(hProcess, dwMinimumWorkingSetSize, dwMaximumWorkingSetSize);
}

BOOL WINAPI MyTerminateProcess(
	_In_ HANDLE hProcess,
	_In_ UINT   uExitCode
)
{
	char buf[MAX_PATH] = "NULL";
	GetModuleFileNameExA(hProcess, 0, buf, MAX_PATH);

	return (realTerminateProcess)(hProcess, uExitCode);
}