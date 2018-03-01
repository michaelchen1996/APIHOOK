#pragma once

#include "SendLog.h"

#ifndef __PROCESS_API__
#define __PROCESS_API__


BOOL WINAPI MyBitBlt(
	_In_ HDC hdc, 
	_In_ int x, 
	_In_ int y, 
	_In_ int cx, 
	_In_ int cy, 
	_In_opt_ HDC hdcSrc, 
	_In_ int x1,
	_In_ int y1, 
	_In_ DWORD rop
);
typedef BOOL(WINAPI *ptrBitBlt)(
	_In_ HDC hdc, 
	_In_ int x, 
	_In_ int y, 
	_In_ int cx, 
	_In_ int cy, 
	_In_opt_ HDC hdcSrc,
	_In_ int x1, 
	_In_ int y1, 
	_In_ DWORD rop
	);
extern ptrBitBlt realBitBlt;

HANDLE WINAPI MyCreateFileMappingW(
	HANDLE hFile,
	LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
	DWORD flProtect,
	DWORD dwMaximumSizeHigh,
	DWORD dwMaximumSizeLow,
	LPCWSTR lpName
);
typedef HANDLE(WINAPI *ptrCreateFileMappingW) (
	HANDLE hFile,
	LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
	DWORD flProtect,
	DWORD dwMaximumSizeHigh,
	DWORD dwMaximumSizeLow,
	LPCWSTR lpName
	);
extern ptrCreateFileMappingW realCreateFileMappingW;

HANDLE WINAPI MyOpenFileMappingW(
	_In_ DWORD dwDesiredAccess, 
	_In_ BOOL bInheritHandle, 
	_In_ LPCWSTR lpName
);
typedef HANDLE(WINAPI *ptrOpenFileMappingW)(
	_In_ DWORD dwDesiredAccess, 
	_In_ BOOL bInheritHandle, 
	_In_ LPCWSTR lpName
	);
extern ptrOpenFileMappingW realOpenFileMappingW;

BOOL WINAPI MyDeviceIoControl(
	_In_        HANDLE       hDevice,
	_In_        DWORD        dwIoControlCode,
	_In_opt_    LPVOID       lpInBuffer,
	_In_        DWORD        nInBufferSize,
	_Out_opt_   LPVOID       lpOutBuffer,
	_In_        DWORD        nOutBufferSize,
	_Out_opt_   LPDWORD      lpBytesReturned,
	_Inout_opt_ LPOVERLAPPED lpOverlapped
);
typedef BOOL(WINAPI *ptrDeviceIoControl) (
	_In_        HANDLE       hDevice,
	_In_        DWORD        dwIoControlCode,
	_In_opt_    LPVOID       lpInBuffer,
	_In_        DWORD        nInBufferSize,
	_Out_opt_   LPVOID       lpOutBuffer,
	_In_        DWORD        nOutBufferSize,
	_Out_opt_   LPDWORD      lpBytesReturned,
	_Inout_opt_ LPOVERLAPPED lpOverlapped
	);
extern ptrDeviceIoControl realDeviceIoControl;

HWND WINAPI MyFindWindowExW(
	_In_opt_ HWND    hwndParent,
	_In_opt_ HWND    hwndChildAfter,
	_In_opt_ LPCWSTR lpszClass,
	_In_opt_ LPCWSTR lpszWindow
);
typedef HWND(WINAPI *ptrFindWindowExW)(
	_In_opt_ HWND    hwndParent,
	_In_opt_ HWND    hwndChildAfter,
	_In_opt_ LPCWSTR lpszClass,
	_In_opt_ LPCWSTR lpszWindow
	);
extern ptrFindWindowExW realFindWindowExW;

SHORT WINAPI MyGetAsyncKeyState(
	_In_ int vKey
);
typedef SHORT(WINAPI *ptrGetAsyncKeyState)(
	_In_ int vKey
	);
extern ptrGetAsyncKeyState realGetAsyncKeyState;

HDC WINAPI MyGetDC(
	_In_ HWND hWnd
);
typedef HDC(WINAPI *ptrGetDC) (
	_In_ HWND hWnd
	);
extern ptrGetDC realGetDC;

HWND WINAPI MyGetForegroundWindow();
typedef HWND(WINAPI *ptrGetForegroundWindow)();
extern ptrGetForegroundWindow realGetForegroundWindow;

SHORT WINAPI MyGetKeyState(
	_In_ int nVirtKey
);
typedef SHORT(WINAPI *ptrGetKeyState)(
	_In_ int nVirtKey
	);
extern ptrGetKeyState realGetKeyState;

DWORD WINAPI MyGetTempPath(
	DWORD nBufferLength,
	LPTSTR lpBuffer
);
typedef DWORD(WINAPI *ptrGetTempPath)(
	DWORD nBufferLength,
	LPTSTR lpBuffer
	);
extern ptrGetTempPath realGetTempPath;

LPVOID WINAPI MyMapViewOfFile(
	_In_ HANDLE hFileMappingObject,
	_In_ DWORD  dwDesiredAccess,
	_In_ DWORD  dwFileOffsetHigh,
	_In_ DWORD  dwFileOffsetLow,
	_In_ SIZE_T dwNumberOfBytesToMap
);
typedef LPVOID(WINAPI *ptrMapViewOfFile)(
	_In_ HANDLE hFileMappingObject,
	_In_ DWORD  dwDesiredAccess,
	_In_ DWORD  dwFileOffsetHigh,
	_In_ DWORD  dwFileOffsetLow,
	_In_ SIZE_T dwNumberOfBytesToMap
	);
extern ptrMapViewOfFile realMapViewOfFile;

HFILE WINAPI MyOpenFile(
	_In_  LPCSTR     lpFileName,
	_Out_ LPOFSTRUCT lpReOpenBuff,
	_In_  UINT       uStyle
);
typedef HFILE(WINAPI *ptrOpenFile)(
	_In_  LPCSTR     lpFileName,
	_Out_ LPOFSTRUCT lpReOpenBuff,
	_In_  UINT       uStyle
	);
extern ptrOpenFile realOpenFile;

BOOL WINAPI MyAdjustTokenPrivileges(
	_In_      HANDLE            TokenHandle,
	_In_      BOOL              DisableAllPrivileges,
	_In_opt_  PTOKEN_PRIVILEGES NewState,
	_In_      DWORD             BufferLength,
	_Out_opt_ PTOKEN_PRIVILEGES PreviousState,
	_Out_opt_ PDWORD            ReturnLength
);
typedef BOOL(WINAPI *ptrAdjustTokenPrivileges)(
	_In_      HANDLE            TokenHandle,
	_In_      BOOL              DisableAllPrivileges,
	_In_opt_  PTOKEN_PRIVILEGES NewState,
	_In_      DWORD             BufferLength,
	_Out_opt_ PTOKEN_PRIVILEGES PreviousState,
	_Out_opt_ PDWORD            ReturnLength
	);
extern ptrAdjustTokenPrivileges realAdjustTokenPrivileges;

BOOL WINAPI MyAttachThreadInput(
	_In_ DWORD idAttach,
	_In_ DWORD idAttachTo,
	_In_ BOOL  fAttach
);
typedef BOOL(WINAPI *ptrAttachThreadInput)(
	_In_ DWORD idAttach,
	_In_ DWORD idAttachTo,
	_In_ BOOL  fAttach
	);
extern ptrAttachThreadInput realAttachThreadInput;

LRESULT WINAPI MyCallNextHookEx(
	_In_opt_ HHOOK  hhk,
	_In_     int    nCode,
	_In_     WPARAM wParam,
	_In_     LPARAM lParam
);
typedef LRESULT(WINAPI *ptrCallNextHookEx)(
	_In_opt_ HHOOK  hhk,
	_In_     int    nCode,
	_In_     WPARAM wParam,
	_In_     LPARAM lParam
	);
extern ptrCallNextHookEx realCallNextHookEx;

BOOL WINAPI MyCheckRemoteDebuggerPresent(
	_In_    HANDLE hProcess,
	_Inout_ PBOOL  pbDebuggerPresent
);
typedef BOOL(WINAPI *ptrCheckRemoteDebuggerPresent)(
	_In_    HANDLE hProcess,
	_Inout_ PBOOL  pbDebuggerPresent
	);
extern ptrCheckRemoteDebuggerPresent realCheckRemoteDebuggerPresent;

BOOL WINAPI MyControlService(
	_In_  SC_HANDLE        hService,
	_In_  DWORD            dwControl,
	_Out_ LPSERVICE_STATUS lpServiceStatus
);
typedef BOOL(WINAPI *ptrControlService)(
	_In_  SC_HANDLE        hService,
	_In_  DWORD            dwControl,
	_Out_ LPSERVICE_STATUS lpServiceStatus
	);
extern ptrControlService realControlService;

HANDLE WINAPI MyCreateRemoteThread(
	_In_  HANDLE                 hProcess,
	_In_  LPSECURITY_ATTRIBUTES  lpThreadAttributes,
	_In_  SIZE_T                 dwStackSize,
	_In_  LPTHREAD_START_ROUTINE lpStartAddress,
	_In_  LPVOID                 lpParameter,
	_In_  DWORD                  dwCreationFlags,
	_Out_ LPDWORD                lpThreadId
);
typedef HANDLE(WINAPI *ptrCreateRemoteThread)(
	_In_  HANDLE                 hProcess,
	_In_  LPSECURITY_ATTRIBUTES  lpThreadAttributes,
	_In_  SIZE_T                 dwStackSize,
	_In_  LPTHREAD_START_ROUTINE lpStartAddress,
	_In_  LPVOID                 lpParameter,
	_In_  DWORD                  dwCreationFlags,
	_Out_ LPDWORD                lpThreadId
	);
extern ptrCreateRemoteThread realCreateRemoteThread;

HANDLE WINAPI MyCreateToolhelp32Snapshot(
	_In_ DWORD dwFlags,
	_In_ DWORD th32ProcessID
);
typedef HANDLE(WINAPI *ptrCreateToolhelp32Snapshot)(
	_In_ DWORD dwFlags,
	_In_ DWORD th32ProcessID
	);
extern ptrCreateToolhelp32Snapshot realCreateToolhelp32Snapshot;

BOOL WINAPI MyEnumProcesses(
	_Out_ DWORD *lpidProcess,
	_In_  DWORD cb,
	_Out_ LPDWORD lpcbNeeded
);
typedef BOOL(WINAPI *ptrEnumProcesses)(
	_Out_ DWORD *lpidProcess,
	_In_  DWORD cb,
	_Out_ LPDWORD lpcbNeeded
	);
extern ptrEnumProcesses realEnumProcesses;

BOOL WINAPI MyEnumProcessModules(
	_In_ HANDLE hProcess,
	_Out_  HMODULE *lphModule,
	_In_   DWORD cb,
	_Out_  LPDWORD lpcbNeeded
);
typedef BOOL(WINAPI *ptrEnumProcessModules)(
	_In_ HANDLE hProcess,
	_Out_  HMODULE *lphModule,
	_In_   DWORD cb,
	_Out_  LPDWORD lpcbNeeded
	);
extern ptrEnumProcessModules realEnumProcessModules;

FARPROC WINAPI MyGetProcAddress(
	_In_ HMODULE hModule,
	_In_ LPCSTR  lpProcName
);
typedef FARPROC(WINAPI *ptrGetProcAddress)(
	_In_ HMODULE hModule,
	_In_ LPCSTR  lpProcName
	);
extern ptrGetProcAddress realGetProcAddress;

LANGID WINAPI MyGetSystemDefaultLangID(void);
typedef LANGID(WINAPI *ptrGetSystemDefaultLangID)(void);
extern ptrGetSystemDefaultLangID realGetSystemDefaultLangID;

BOOL WINAPI MyGetThreadContext(
	_In_    HANDLE    hThread,
	_Inout_ LPCONTEXT lpContext
);
typedef BOOL(WINAPI *ptrGetThreadContext)(
	_In_    HANDLE    hThread,
	_Inout_ LPCONTEXT lpContext
	);
extern ptrGetThreadContext realGetThreadContext;

DWORD WINAPI MyGetTickCount(void);
typedef DWORD(WINAPI *ptrGetTickCount)(void);
extern ptrGetTickCount realGetTickCount;

BOOL WINAPI MyIsDebuggerPresent(void);
typedef BOOL(WINAPI *ptrIsDebuggerPresent)(void);
extern ptrIsDebuggerPresent realIsDebuggerPresent;

HMODULE WINAPI MyLoadLibraryExW(
	_In_       LPCWSTR lpLibFileName,
	_Reserved_ HANDLE  hFile,
	_In_       DWORD   dwFlags
);
typedef HMODULE(WINAPI *ptrLoadLibraryExW)(
	_In_       LPCWSTR lpLibFileName,
	_Reserved_ HANDLE  hFile,
	_In_       DWORD   dwFlags
	);
extern ptrLoadLibraryExW realLoadLibraryExW;

HGLOBAL WINAPI MyLoadResource(
	_In_opt_ HMODULE hModule,
	_In_     HRSRC   hResInfo
);
typedef HGLOBAL(WINAPI *ptrLoadResource)(
	_In_opt_ HMODULE hModule,
	_In_     HRSRC   hResInfo
	);
extern ptrLoadResource realLoadResource;

BOOL WINAPI MyModule32FirstW(
	_In_    HANDLE          hSnapshot,
	_Inout_ LPMODULEENTRY32W lpme
);
typedef BOOL(WINAPI *ptrModule32FirstW)(
	_In_    HANDLE          hSnapshot,
	_Inout_ LPMODULEENTRY32W lpme
	);
extern ptrModule32FirstW realModule32FirstW;

BOOL WINAPI MyModule32NextW(
	_In_  HANDLE          hSnapshot,
	_Out_ LPMODULEENTRY32W  lpme
);
typedef BOOL(WINAPI *ptrModule32NextW)(
	_In_  HANDLE          hSnapshot,
	_Out_ LPMODULEENTRY32W  lpme
	);
extern ptrModule32NextW realModule32NextW;

HANDLE WINAPI MyOpenProcess(
	_In_ DWORD dwDesiredAccess,
	_In_ BOOL  bInheritHandle,
	_In_ DWORD dwProcessId
);
typedef HANDLE(WINAPI *ptrOpenProcess)(
	_In_ DWORD dwDesiredAccess,
	_In_ BOOL  bInheritHandle,
	_In_ DWORD dwProcessId
	);
extern ptrOpenProcess realOpenProcess;

BOOL WINAPI MyPeekNamedPipe(
	_In_      HANDLE  hNamedPipe,
	_Out_opt_ LPVOID  lpBuffer,
	_In_      DWORD   nBufferSize,
	_Out_opt_ LPDWORD lpBytesRead,
	_Out_opt_ LPDWORD lpTotalBytesAvail,
	_Out_opt_ LPDWORD lpBytesLeftThisMessage
);
typedef BOOL(WINAPI *ptrPeekNamedPipe)(
	_In_      HANDLE  hNamedPipe,
	_Out_opt_ LPVOID  lpBuffer,
	_In_      DWORD   nBufferSize,
	_Out_opt_ LPDWORD lpBytesRead,
	_Out_opt_ LPDWORD lpTotalBytesAvail,
	_Out_opt_ LPDWORD lpBytesLeftThisMessage
	);
extern ptrPeekNamedPipe realPeekNamedPipe;
 
BOOL WINAPI MyProcess32First(
	_In_    HANDLE           hSnapshot,
	_Inout_ LPPROCESSENTRY32 lppe
);
typedef BOOL(WINAPI *ptrProcess32First)(
	_In_    HANDLE           hSnapshot,
	_Inout_ LPPROCESSENTRY32 lppe
	);
extern ptrProcess32First realProcess32First;

BOOL WINAPI MyProcess32Next(
	_In_  HANDLE           hSnapshot,
	_Out_ LPPROCESSENTRY32 lppe
);
typedef BOOL(WINAPI *ptrProcess32Next)(
	_In_  HANDLE           hSnapshot,
	_Out_ LPPROCESSENTRY32 lppe
	);
extern ptrProcess32Next realProcess32Next;

BOOL WINAPI MyQueryPerformanceCounter(
	_Out_ LARGE_INTEGER *lpPerformanceCount
);
typedef BOOL(WINAPI *ptrQueryPerformanceCounter)(
	_Out_ LARGE_INTEGER *lpPerformanceCount
	);
extern ptrQueryPerformanceCounter realQueryPerformanceCounter;

DWORD WINAPI MyQueueUserAPC(
	_In_ PAPCFUNC  pfnAPC,
	_In_ HANDLE    hThread,
	_In_ ULONG_PTR dwData
);
typedef DWORD(WINAPI *ptrQueueUserAPC)(
	_In_ PAPCFUNC  pfnAPC,
	_In_ HANDLE    hThread,
	_In_ ULONG_PTR dwData
	);
extern ptrQueueUserAPC realQueueUserAPC;

BOOL WINAPI MyReadProcessMemory(
	_In_  HANDLE  hProcess,
	_In_  LPCVOID lpBaseAddress,
	_Out_ LPVOID  lpBuffer,
	_In_  SIZE_T  nSize,
	_Out_ SIZE_T  *lpNumberOfBytesRead
);
typedef BOOL(WINAPI *ptrReadProcessMemory)(
	_In_  HANDLE  hProcess,
	_In_  LPCVOID lpBaseAddress,
	_Out_ LPVOID  lpBuffer,
	_In_  SIZE_T  nSize,
	_Out_ SIZE_T  *lpNumberOfBytesRead
	);
extern ptrReadProcessMemory realReadProcessMemory;

DWORD WINAPI MyResumeThread(
	_In_ HANDLE hThread
);
typedef DWORD(WINAPI *ptrResumeThread)(
	_In_ HANDLE hThread
	);
extern ptrResumeThread realResumeThread;

BOOL WINAPI MySetThreadContext(
	_In_       HANDLE  hThread,
	_In_ const CONTEXT *lpContext
);
typedef BOOL(WINAPI *ptrSetThreadContext)(
	_In_       HANDLE  hThread,
	_In_ const CONTEXT *lpContext
	);
extern ptrSetThreadContext realSetThreadContext;

DWORD WINAPI MySuspendThread(
	_In_ HANDLE hThread
);
typedef DWORD(WINAPI *ptrSuspendThread)(
	_In_ HANDLE hThread
	); 
extern ptrSuspendThread realSuspendThread;

BOOL WINAPI MyThread32First(
	_In_    HANDLE          hSnapshot,
	_Inout_ LPTHREADENTRY32 lpte
);
typedef BOOL(WINAPI *ptrThread32First)(
	_In_    HANDLE          hSnapshot,
	_Inout_ LPTHREADENTRY32 lpte
	);
extern ptrThread32First realThread32First;

BOOL WINAPI MyThread32Next(
	_In_  HANDLE          hSnapshot,
	_Out_ LPTHREADENTRY32 lpte
);
typedef BOOL(WINAPI *ptrThread32Next)
(
	_In_  HANDLE          hSnapshot,
	_Out_ LPTHREADENTRY32 lpte
	);
extern ptrThread32Next realThread32Next;

BOOL WINAPI MyToolhelp32ReadProcessMemory(
	_In_  DWORD   th32ProcessID,
	_In_  LPCVOID lpBaseAddress,
	_Out_ LPVOID  lpBuffer,
	_In_  SIZE_T  cbRead,
	_Out_ SIZE_T  lpNumberOfBytesRead
);
typedef BOOL(WINAPI *ptrToolhelp32ReadProcessMemory)(
	_In_  DWORD   th32ProcessID,
	_In_  LPCVOID lpBaseAddress,
	_Out_ LPVOID  lpBuffer,
	_In_  SIZE_T  cbRead,
	_Out_ SIZE_T  lpNumberOfBytesRead
	);
extern ptrToolhelp32ReadProcessMemory realToolhelp32ReadProcessMemory;

LPVOID WINAPI MyVirtualAllocEx(
	_In_     HANDLE hProcess,
	_In_opt_ LPVOID lpAddress,
	_In_     SIZE_T dwSize,
	_In_     DWORD  flAllocationType,
	_In_     DWORD  flProtect
);
typedef LPVOID(WINAPI *ptrVirtualAllocEx)(
	_In_     HANDLE hProcess,
	_In_opt_ LPVOID lpAddress,
	_In_     SIZE_T dwSize,
	_In_     DWORD  flAllocationType,
	_In_     DWORD  flProtect
	);
extern ptrVirtualAllocEx realVirtualAllocEx;

BOOL WINAPI MyVirtualProtectEx(
	_In_  HANDLE hProcess,
	_In_  LPVOID lpAddress,
	_In_  SIZE_T dwSize,
	_In_  DWORD  flNewProtect,
	_Out_ PDWORD lpflOldProtect
);
typedef BOOL(WINAPI *ptrVirtualProtectEx)(
	_In_  HANDLE hProcess,
	_In_  LPVOID lpAddress,
	_In_  SIZE_T dwSize,
	_In_  DWORD  flNewProtect,
	_Out_ PDWORD lpflOldProtect
	);
extern ptrVirtualProtectEx realVirtualProtectEx;

UINT WINAPI MyWinExec(
	_In_ LPCSTR lpCmdLine,
	_In_ UINT   uCmdShow
);
typedef UINT(WINAPI *ptrWinExec)(
	_In_ LPCSTR lpCmdLine,
	_In_ UINT   uCmdShow
	);
extern ptrWinExec realWinExec;

BOOL WINAPI MyWriteProcessMemory(
	_In_  HANDLE  hProcess,
	_In_  LPVOID  lpBaseAddress,
	_In_  LPCVOID lpBuffer,
	_In_  SIZE_T  nSize,
	_Out_ SIZE_T  *lpNumberOfBytesWritten
);
typedef BOOL(WINAPI *ptrWriteProcessMemory)(
	_In_  HANDLE  hProcess,
	_In_  LPVOID  lpBaseAddress,
	_In_  LPCVOID lpBuffer,
	_In_  SIZE_T  nSize,
	_Out_ SIZE_T  *lpNumberOfBytesWritten
	); 
extern ptrWriteProcessMemory realWriteProcessMemory;

BOOL WINAPI MyRegisterHotKey(
	_In_opt_ HWND hWnd,
	_In_     int  id,
	_In_     UINT fsModifiers,
	_In_     UINT vk
);
typedef BOOL(WINAPI *ptrRegisterHotKey)(
	_In_opt_ HWND hWnd,
	_In_     int  id,
	_In_     UINT fsModifiers,
	_In_     UINT vk
	);
extern ptrRegisterHotKey realRegisterHotKey;

BOOL WINAPI MyCreateProcessA(
	_In_opt_    LPCSTR                lpApplicationName,
	_Inout_opt_ LPSTR                 lpCommandLine,
	_In_opt_    LPSECURITY_ATTRIBUTES lpProcessAttributes,
	_In_opt_    LPSECURITY_ATTRIBUTES lpThreadAttributes,
	_In_        BOOL                  bInheritHandles,
	_In_        DWORD                 dwCreationFlags,
	_In_opt_    LPVOID                lpEnvironment,
	_In_opt_    LPCSTR               lpCurrentDirectory,
	_In_        LPSTARTUPINFOA         lpStartupInfo,
	_Out_       LPPROCESS_INFORMATION lpProcessInformation
);
typedef BOOL(WINAPI *ptrCreateProcessW)(
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
	);
extern  ptrCreateProcessW realCreateProcessW;

HANDLE WINAPI MyCreateMutexW(
	_In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes,
	_In_     BOOL                  bInitialOwner,
	_In_opt_ LPCWSTR               lpName
);
typedef HANDLE(WINAPI *ptrCreateMutexW)(
	_In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes,
	_In_     BOOL                  bInitialOwner,
	_In_opt_ LPCWSTR               lpName
	);
extern ptrCreateMutexW realCreateMutexW;

HRSRC WINAPI MyFindResourceW(
	_In_opt_ HMODULE hModule,
	_In_     LPCWSTR lpName,
	_In_     LPCWSTR lpType
);
typedef HRSRC(WINAPI *ptrFindResourceW)(
	_In_opt_ HMODULE hModule,
	_In_     LPCWSTR lpName,
	_In_     LPCWSTR lpType
	);
extern ptrFindResourceW realFindResourceW;

HWND WINAPI MyFindWindowW(
	_In_opt_ LPCWSTR lpClassName,
	_In_opt_ LPCWSTR lpWindowName
);
typedef HWND(WINAPI *ptrFindWindowW)(
	_In_opt_ LPCWSTR lpClassName,
	_In_opt_ LPCWSTR lpWindowName
	);
extern ptrFindWindowW realFindWindowW;

UINT WINAPI MyGetWindowsDirectoryW(
	_Out_ LPTSTR lpBuffer,
	_In_  UINT   uSize
);
typedef UINT(WINAPI *ptrGetWindowsDirectoryW)(
	_Out_ LPTSTR lpBuffer,
	_In_  UINT   uSize
	);
extern ptrGetWindowsDirectoryW realGetWindowsDirectoryW;

UINT WINAPI MyMapVirtualKeyW(
	_In_ UINT uCode,
	_In_ UINT uMapType
);
typedef UINT(WINAPI *ptrMapVirtualKeyW)(
	_In_ UINT uCode,
	_In_ UINT uMapType
	);
extern ptrMapVirtualKeyW realMapVirtualKeyW;

HANDLE WINAPI MyOpenMutexW(
	_In_ DWORD   dwDesiredAccess,
	_In_ BOOL    bInheritHandle,
	_In_ LPCWSTR lpName
);
typedef HANDLE(WINAPI *ptrOpenMutexW)(
	_In_ DWORD   dwDesiredAccess,
	_In_ BOOL    bInheritHandle,
	_In_ LPCWSTR lpName
	);
extern ptrOpenMutexW realOpenMutexW;

SC_HANDLE WINAPI MyOpenSCManagerW(
	_In_opt_ LPCWSTR lpMachineName,
	_In_opt_ LPCWSTR lpDatabaseName,
	_In_     DWORD   dwDesiredAccess
);
typedef SC_HANDLE(WINAPI *ptrOpenSCManagerW)(
	_In_opt_ LPCWSTR lpMachineName,
	_In_opt_ LPCWSTR lpDatabaseName,
	_In_     DWORD   dwDesiredAccess
	);
extern ptrOpenSCManagerW realOpenSCManagerW;

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
);
typedef BOOL(WINAPI *ptrCreateProcessA)(
	_In_opt_    LPCSTR               lpApplicationName,
	_Inout_opt_ LPSTR                lpCommandLine,
	_In_opt_    LPSECURITY_ATTRIBUTES lpProcessAttributes,
	_In_opt_    LPSECURITY_ATTRIBUTES lpThreadAttributes,
	_In_        BOOL                  bInheritHandles,
	_In_        DWORD                 dwCreationFlags,
	_In_opt_    LPVOID                lpEnvironment,
	_In_opt_    LPCSTR               lpCurrentDirectory,
	_In_        LPSTARTUPINFOA        lpStartupInfo,
	_Out_       LPPROCESS_INFORMATION lpProcessInformation
	);
extern ptrCreateProcessA realCreateProcessA;

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
);
typedef SC_HANDLE(WINAPI *ptrCreateServiceW)(
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
	);
extern ptrCreateServiceW realCreateServiceW;

DWORD WINAPI MyGetModuleFileNameExW(
	_In_     HANDLE  hProcess,
	_In_opt_ HMODULE hModule,
	_Out_    LPTSTR  lpFilename,
	_In_     DWORD   nSize
);
typedef DWORD(WINAPI *ptrGetModuleFileNameExW)(
	_In_     HANDLE  hProcess,
	_In_opt_ HMODULE hModule,
	_Out_    LPTSTR  lpFilename,
	_In_     DWORD   nSize
	);
extern ptrGetModuleFileNameExW realGetModuleFileNameExW;

HMODULE WINAPI MyGetModuleHandleW(
	_In_opt_ LPCWSTR lpModuleName
);
typedef HMODULE(WINAPI *ptrGetModuleHandleW)(
	_In_opt_ LPCWSTR lpModuleName
	);
extern ptrGetModuleHandleW realGetModuleHandleW;

VOID WINAPI MyGetStartupInfoW(
	_Out_ LPSTARTUPINFOW lpStartupInfo
);
typedef VOID(WINAPI *ptrGetStartupInfoW)(
	_Out_ LPSTARTUPINFO lpStartupInfo
	);
extern ptrGetStartupInfoW realGetStartupInfoW;

BOOL WINAPI	MyGetVersionExW(
	_Inout_ LPOSVERSIONINFO lpVersionInfo
);
typedef BOOL(WINAPI *ptrGetVersionExW)(
	_Inout_ LPOSVERSIONINFO lpVersionInfo
	);
extern ptrGetVersionExW realGetVersionExW;

HMODULE WINAPI MyLoadLibraryW(
	_In_ LPCWSTR lpLibFileName
);
typedef HMODULE(WINAPI *ptrLoadLibraryW)(
	_In_ LPCWSTR lpFileName
	);
extern ptrLoadLibraryW realLoadLibraryW;

void WINAPI MyOutputDebugStringW(
	_In_opt_ LPCWSTR lpOutputString
);
typedef VOID(WINAPI *ptrOutputDebugStringW)(
	_In_opt_ LPCWSTR lpOutputString
	);
extern ptrOutputDebugStringW realOutputDebugStringW;

HHOOK WINAPI MySetWindowsHookExW(
	_In_ int       idHook,
	_In_ HOOKPROC  lpfn,
	_In_ HINSTANCE hMod,
	_In_ DWORD     dwThreadId
);
typedef HHOOK(WINAPI *ptrSetWindowsHookExW)(
	_In_ int       idHook,
	_In_ HOOKPROC  lpfn,
	_In_ HINSTANCE hMod,
	_In_ DWORD     dwThreadId
	);
extern ptrSetWindowsHookExW realSetWindowsHookExW;

HINSTANCE WINAPI MyShellExecuteW(
	_In_opt_ HWND    hwnd,
	_In_opt_ LPCWSTR lpOperation,
	_In_     LPCWSTR lpFile,
	_In_opt_ LPCWSTR lpParameters,
	_In_opt_ LPCWSTR lpDirectory,
	_In_     INT     nShowCmd
);
typedef HINSTANCE(WINAPI *ptrShellExecuteW)(
	_In_opt_ HWND    hwnd,
	_In_opt_ LPCWSTR lpOperation,
	_In_     LPCWSTR lpFile,
	_In_opt_ LPCWSTR lpParameters,
	_In_opt_ LPCWSTR lpDirectory,
	_In_     INT     nShowCmd
	);
extern ptrShellExecuteW realShellExecuteW;

BOOL WINAPI MyStartServiceCtrlDispatcherW(
	_In_ const SERVICE_TABLE_ENTRY *lpServiceStartTable
);
typedef BOOL(WINAPI *ptrStartServiceCtrlDispatcherW)(
	_In_ const SERVICE_TABLE_ENTRY *lpServiceTable
	);
extern ptrStartServiceCtrlDispatcherW realStartServiceCtrlDispatcherW;

BOOL WINAPI MySetLocalTime(
	_In_ const SYSTEMTIME *lpSystemTime
);
typedef BOOL(WINAPI *ptrSetLocalTime)(
	_In_ const SYSTEMTIME *lpSystemTime
	);
extern ptrSetLocalTime realSetLocalTime;

BOOL WINAPI MyTerminateThread(
	_Inout_ HANDLE hThread,
	_In_    DWORD  dwExitCode
);
typedef BOOL(WINAPI *ptrTerminateThread)(
	_Inout_ HANDLE hThread,
	_In_    DWORD  dwExitCode
	);
extern ptrTerminateThread realTerminateThread;

BOOL WINAPI MyVirtualFree(
	_In_ LPVOID lpAddress,
	_In_ SIZE_T dwSize,
	_In_ DWORD  dwFreeType
);
typedef BOOL(WINAPI *ptrVirtualFree)(
	_In_ LPVOID lpAddress,
	_In_ SIZE_T dwSize,
	_In_ DWORD  dwFreeType
	);
extern ptrVirtualFree realVirtualFree;

BOOL WINAPI MySetProcessWorkingSetSize(
	_In_ HANDLE hProcess,
	_In_ SIZE_T dwMinimumWorkingSetSize,
	_In_ SIZE_T dwMaximumWorkingSetSize
);
typedef BOOL(WINAPI *ptrSetProcessWorkingSetSize)(
	_In_ HANDLE hProcess,
	_In_ SIZE_T dwMinimumWorkingSetSize,
	_In_ SIZE_T dwMaximumWorkingSetSize
	);
extern ptrSetProcessWorkingSetSize realSetProcessWorkingSetSize;

BOOL WINAPI MyTerminateProcess(
	_In_ HANDLE hProcess,
	_In_ UINT   uExitCode
);
typedef BOOL(WINAPI *ptrTerminateProcess)(
	_In_ HANDLE hProcess,
	_In_ UINT   uExitCode
	);
extern ptrTerminateProcess realTerminateProcess;


#endif // !__PROCESS_API__


