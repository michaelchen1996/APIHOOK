#pragma once

#include "SendLog.h"

#ifndef __FILE_API__
#define __FILE_API__


NTSTATUS MyZwSetInformationFile(
	_In_  HANDLE                 FileHandle,
	_Out_ PIO_STATUS_BLOCK       IoStatusBlock,
	_In_  PVOID                  FileInformation,
	_In_  ULONG                  Length,
	_In_  FILE_INFORMATION_CLASS FileInformationClass
);
typedef NTSTATUS(*ptrZwSetInformationFile)(
	_In_  HANDLE                 FileHandle,
	_Out_ PIO_STATUS_BLOCK       IoStatusBlock,
	_In_  PVOID                  FileInformation,
	_In_  ULONG                  Length,
	_In_  FILE_INFORMATION_CLASS FileInformationClass
	);
extern ptrZwSetInformationFile realZwSetInformationFile;

BOOL WINAPI MySetFileTime(
	_In_ HANDLE hFile, 
	_In_opt_ CONST FILETIME * lpCreationTime, 
	_In_opt_ CONST FILETIME * lpLastAccessTime, 
	_In_opt_ CONST FILETIME * lpLastWriteTime
);
typedef BOOL(WINAPI *ptrSetFileTime)(
	_In_ HANDLE hFile, 
	_In_opt_ CONST FILETIME * lpCreationTime, 
	_In_opt_ CONST FILETIME * lpLastAccessTime, 
	_In_opt_ CONST FILETIME * lpLastWriteTime
	);
extern ptrSetFileTime realSetFileTime;

BOOL WINAPI MySetFileValidData(
	_In_ HANDLE hFile, 
	_In_ LONGLONG ValidDataLength
);
typedef BOOL(WINAPI *ptrSetFileValidData)(
	_In_ HANDLE hFile, 
	_In_ LONGLONG ValidDataLength
	);
extern ptrSetFileValidData realSetFileValidData;

BOOL WINAPI MySetEndOfFile(
	_In_ HANDLE hFile
);
typedef BOOL(WINAPI *ptrSetEndOfFile)(
	_In_ HANDLE hFile
	);
extern ptrSetEndOfFile realSetEndOfFile;

BOOL WINAPI MyCreateHardLinkW(
	_In_ LPCWSTR lpFileName, 
	_In_ LPCWSTR lpExistingFileName, 
	_Reserved_ LPSECURITY_ATTRIBUTES lpSecurityAttributes
);
typedef BOOL(WINAPI *ptrCreateHardLinkW)(
	_In_ LPCWSTR lpFileName, 
	_In_ LPCWSTR lpExistingFileName, 
	_Reserved_ LPSECURITY_ATTRIBUTES lpSecurityAttributes
	);
extern ptrCreateHardLinkW realCreateHardLinkW;

BOOL WINAPI MySetFileAttributesW(
	_In_ LPCWSTR lpFileName, 
	_In_ DWORD dwFileAttributes
);
typedef BOOL(WINAPI *ptrSetFileAttributesW)(
	_In_ LPCWSTR lpFileName, 
	_In_ DWORD dwFileAttributes
	);
extern ptrSetFileAttributesW realSetFileAttributesW;

BOOL WINAPI MyFindNextFileW(
	_In_ HANDLE hFindFile, 
	_Out_ LPWIN32_FIND_DATAW lpFindFileData
);
typedef BOOL(WINAPI *ptrFindNextFileW)(
	_In_ HANDLE hFindFile, 
	_Out_ LPWIN32_FIND_DATAW lpFindFileData
	);
extern ptrFindNextFileW realFindNextFileW;

HANDLE WINAPI MyFindFirstFileW(
	_In_ LPCWSTR lpFileName, 
	_Out_ LPWIN32_FIND_DATAW lpFindFileData
);
typedef HANDLE(WINAPI *ptrFindFirstFileW)(
	_In_ LPCWSTR lpFileName, 
	_Out_ LPWIN32_FIND_DATAW lpFindFileData
	);
extern ptrFindFirstFileW realFindFirstFileW;

BOOL WINAPI MyDeleteFileW(
	_In_ LPCWSTR lpFileName
);
typedef BOOL(WINAPI *ptrDeleteFileW)(
	_In_ LPCWSTR lpFileName
	);
extern ptrDeleteFileW realDeleteFileW;

BOOL WINAPI MyCopyFileW(
	_In_ LPCWSTR lpExistingFileName, 
	_In_ LPCWSTR lpNewFileName, 
	_In_ BOOL bFailIfExists
);
typedef BOOL(WINAPI *ptrCopyFileW)(
	_In_ LPCWSTR lpExistingFileName, 
	_In_ LPCWSTR lpNewFileName, 
	_In_ BOOL bFailIfExists
	);
extern ptrCopyFileW realCopyFileW;

BOOL WINAPI MyMoveFileW(
	_In_ LPCWSTR lpExistingFileName,
	_In_ LPCWSTR lpNewFileName
);

typedef BOOL(WINAPI *ptrMoveFileW)(
	_In_ LPCWSTR lpExistingFileName,
	_In_ LPCWSTR lpNewFileName
	);
extern ptrMoveFileW realMoveFileW;

HANDLE WINAPI MyCreateFileW(
	__in     LPCWSTR lpFileName,
	__in     DWORD dwDesiredAccess,
	__in     DWORD dwShareMode,
	__in_opt LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	__in     DWORD dwCreationDisposition,
	__in     DWORD dwFlagsAndAttributes,
	__in_opt HANDLE hTemplateFile
);
typedef HANDLE(WINAPI *ptrCreateFileW)(
	__in     LPCWSTR lpFileName,
	__in     DWORD dwDesiredAccess,
	__in     DWORD dwShareMode,
	__in_opt LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	__in     DWORD dwCreationDisposition,
	__in     DWORD dwFlagsAndAttributes,
	__in_opt HANDLE hTemplateFile
	);
extern ptrCreateFileW realCreateFileW;

HANDLE WINAPI MyCreateFileA(
	__in     LPCSTR lpFileName,
	__in     DWORD dwDesiredAccess,
	__in     DWORD dwShareMode,
	__in_opt LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	__in     DWORD dwCreationDisposition,
	__in     DWORD dwFlagsAndAttributes,
	__in_opt HANDLE hTemplateFile
);
typedef HANDLE(WINAPI *ptrCreateFileA)(
	__in     LPCSTR lpFileName,
	__in     DWORD dwDesiredAccess,
	__in     DWORD dwShareMode,
	__in_opt LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	__in     DWORD dwCreationDisposition,
	__in     DWORD dwFlagsAndAttributes,
	__in_opt HANDLE hTemplateFile
	);
extern ptrCreateFileA realCreateFileA;

BOOL WINAPI MyReadFile(
	_In_        HANDLE       hFile,
	_Out_       LPVOID       lpBuffer,
	_In_        DWORD        nNumberOfBytesToRead,
	_Out_opt_   LPDWORD      lpNumberOfBytesRead,
	_Inout_opt_ LPOVERLAPPED lpOverlapped
);

typedef BOOL(WINAPI *ptrReadFile)(
	_In_        HANDLE       hFile,
	_Out_       LPVOID       lpBuffer,
	_In_        DWORD        nNumberOfBytesToRead,
	_Out_opt_   LPDWORD      lpNumberOfBytesRead,
	_Inout_opt_ LPOVERLAPPED lpOverlapped
	);
extern ptrReadFile realReadFile;


#endif // !__FILE_API__


