#include "stdafx.h"
#include "FileAPI.h"


NTSTATUS MyZwSetInformationFile(
	_In_  HANDLE                 FileHandle,
	_Out_ PIO_STATUS_BLOCK       IoStatusBlock,
	_In_  PVOID                  FileInformation,
	_In_  ULONG                  Length,
	_In_  FILE_INFORMATION_CLASS FileInformationClass
)
{
	NTSTATUS status = -1;
	TCHAR szLogBuf[MAX_LOG_SIZE];

	if (NULL == realZwSetInformationFile)
	{
		OutputDebugString(TEXT("realZwSetInformationFile NOT FOUND\n"));
		return status;
	}
	else
	{
		StringCbCopy(szLogBuf, MAX_LOG_SIZE, TEXT("\"api\":\"MyZwSetInformationFile\""));
		if (10 == FileInformationClass)
		{
			//StringCbCat(szLogBuf, MAX_LOG_SIZE, TEXT(", FileRenameInformation"));
			//StringCbCat(szLogBuf, MAX_LOG_SIZE, ((PFILE_RENAME_INFORMATION)FileInformation))
		}
		//StringCbCat(szLogBuf, MAX_LOG_SIZE, TEXT("\r\n"));
		SendLog(szLogBuf);
		status = realZwSetInformationFile(
			FileHandle,
			IoStatusBlock,
			FileInformation,
			Length,
			FileInformationClass
		);

	}

	return status;
}


BOOL WINAPI MyReadFile(
	_In_        HANDLE       hFile,
	_Out_       LPVOID       lpBuffer,
	_In_        DWORD        nNumberOfBytesToRead,
	_Out_opt_   LPDWORD      lpNumberOfBytesRead,
	_Inout_opt_ LPOVERLAPPED lpOverlapped
)
{
	TCHAR szLogBuf[MAX_LOG_SIZE];
	TCHAR szFilepath[MAX_PATH];
	if (hFile != NULL)
	{
		GetFinalPathNameByHandle(hFile, szFilepath, MAX_PATH, VOLUME_NAME_DOS);
	}
	else
	{
		StringCbCopy(szFilepath, MAX_PATH, TEXT("NULL"));
	}
	StringCbCopy(szLogBuf, MAX_LOG_SIZE, TEXT("\"api\":\"ReadFile\""));
	StringCbCat(szLogBuf, MAX_LOG_SIZE, TEXT(",\"param\":[\""));
	StringCbCat(szLogBuf, MAX_LOG_SIZE, szFilepath);
	StringCbCat(szLogBuf, MAX_LOG_SIZE, TEXT("\"]"));
	SendLog(szLogBuf);
	return (realReadFile)(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
}


BOOL WINAPI MySetFileTime(
	_In_ HANDLE hFile, 
	_In_opt_ CONST FILETIME * lpCreationTime, 
	_In_opt_ CONST FILETIME * lpLastAccessTime, 
	_In_opt_ CONST FILETIME * lpLastWriteTime
) 
{
	TCHAR szLogBuf[MAX_LOG_SIZE];
	TCHAR szFilepath[MAX_PATH];
	if (hFile != NULL)
	{
		GetFinalPathNameByHandle(hFile, szFilepath, MAX_PATH, VOLUME_NAME_DOS);
	}
	else
	{
		StringCbCopy(szFilepath, MAX_PATH, TEXT("NULL"));
	}
	StringCbCopy(szLogBuf, MAX_LOG_SIZE, TEXT("\"api\":\"SetFileTime\""));
	StringCbCat(szLogBuf, MAX_LOG_SIZE, TEXT(",\"param\":[\""));
	StringCbCat(szLogBuf, MAX_LOG_SIZE, szFilepath);
	StringCbCat(szLogBuf, MAX_LOG_SIZE, TEXT("\"]"));
	SendLog(szLogBuf);
	return (realSetFileTime)(hFile, lpCreationTime, lpLastAccessTime, lpLastWriteTime);
}


BOOL WINAPI MySetFileValidData(
	_In_ HANDLE hFile, 
	_In_ LONGLONG ValidDataLength
) 
{
	TCHAR szLogBuf[MAX_LOG_SIZE];
	TCHAR szFilepath[MAX_PATH];
	if (hFile != NULL)
	{
		GetFinalPathNameByHandle(hFile, szFilepath, MAX_PATH, VOLUME_NAME_DOS);
	}
	else
	{
		StringCbCopy(szFilepath, MAX_PATH, TEXT("NULL"));
	}
	StringCbCopy(szLogBuf, MAX_LOG_SIZE, TEXT("\"api\":\"SetFileValidData\""));
	StringCbCat(szLogBuf, MAX_LOG_SIZE, TEXT(",\"param\":[\""));
	StringCbCat(szLogBuf, MAX_LOG_SIZE, szFilepath);
	StringCbCat(szLogBuf, MAX_LOG_SIZE, TEXT("\"]"));
	SendLog(szLogBuf);
	return (realSetFileValidData)(hFile, ValidDataLength);
}


BOOL WINAPI MySetEndOfFile(
	_In_ HANDLE hFile
) 
{
	TCHAR szLogBuf[MAX_LOG_SIZE];
	TCHAR szFilepath[MAX_PATH];
	if (hFile != NULL)
	{
		GetFinalPathNameByHandle(hFile, szFilepath, MAX_PATH, VOLUME_NAME_DOS);
	}
	else
	{
		StringCbCopy(szFilepath, MAX_PATH, TEXT("NULL"));
	}
	StringCbCopy(szLogBuf, MAX_LOG_SIZE, TEXT("\"api\":\"SetEndOfFile\""));
	StringCbCat(szLogBuf, MAX_LOG_SIZE, TEXT(",\"param\":[\""));
	StringCbCat(szLogBuf, MAX_LOG_SIZE, szFilepath);
	StringCbCat(szLogBuf, MAX_LOG_SIZE, TEXT("\"]"));
	SendLog(szLogBuf);
	return (realSetEndOfFile)(hFile);
}


BOOL WINAPI MyCreateHardLinkW(
	_In_ LPCWSTR lpFileName, 
	_In_ LPCWSTR lpExistingFileName, 
	_Reserved_ LPSECURITY_ATTRIBUTES lpSecurityAttributes
) 
{
	TCHAR szLogBuf[MAX_LOG_SIZE];
	StringCbCopy(szLogBuf, MAX_LOG_SIZE, TEXT("\"api\":\"CreateHardLinkW\""));
	StringCbCat(szLogBuf, MAX_LOG_SIZE, TEXT(",\"param\":[\""));
	StringCbCat(szLogBuf, MAX_LOG_SIZE, lpFileName);
	StringCbCat(szLogBuf, MAX_LOG_SIZE, TEXT("\",\""));
	StringCbCat(szLogBuf, MAX_LOG_SIZE, lpExistingFileName);
	StringCbCat(szLogBuf, MAX_LOG_SIZE, TEXT("\"]"));
	SendLog(szLogBuf);
	return (realCreateHardLinkW)(lpFileName, lpExistingFileName, lpSecurityAttributes);
}


BOOL WINAPI MySetFileAttributesW(
	_In_ LPCWSTR lpFileName, 
	_In_ DWORD dwFileAttributes
) 
{
	TCHAR szLogBuf[MAX_LOG_SIZE];
	StringCbCopy(szLogBuf, MAX_LOG_SIZE, TEXT("\"api\":\"SetFileAttributesW\""));
	StringCbCat(szLogBuf, MAX_LOG_SIZE, TEXT(",\"param\":[\""));
	StringCbCat(szLogBuf, MAX_LOG_SIZE, lpFileName);
	StringCbCat(szLogBuf, MAX_LOG_SIZE, TEXT("\"]"));
	SendLog(szLogBuf);
	return (realSetFileAttributesW)(lpFileName, dwFileAttributes);
}


BOOL WINAPI MyFindNextFileW(
	_In_ HANDLE hFindFile, 
	_Out_ LPWIN32_FIND_DATAW lpFindFileData
) 
{
	TCHAR szLogBuf[MAX_LOG_SIZE];
	TCHAR szFilepath[MAX_PATH];
	if (hFindFile != NULL)
	{
		GetFinalPathNameByHandle(hFindFile, szFilepath, MAX_PATH, VOLUME_NAME_DOS);
	}
	else
	{
		StringCbCopy(szFilepath, MAX_PATH, TEXT("NULL"));
	}
	StringCbCopy(szLogBuf, MAX_LOG_SIZE, TEXT("\"api\":\"FindNextFileW\""));
	StringCbCat(szLogBuf, MAX_LOG_SIZE, TEXT(",\"param\":[\""));
	StringCbCat(szLogBuf, MAX_LOG_SIZE, szFilepath);
	StringCbCat(szLogBuf, MAX_LOG_SIZE, TEXT("\"]"));
	SendLog(szLogBuf);
	return (realFindNextFileW)(hFindFile, lpFindFileData);
}


HANDLE WINAPI MyFindFirstFileW(
	_In_ LPCWSTR lpFileName, 
	_Out_ LPWIN32_FIND_DATAW lpFindFileData
) 
{
	TCHAR szLogBuf[MAX_LOG_SIZE];
	StringCbCopy(szLogBuf, MAX_LOG_SIZE, TEXT("\"api\":\"FindFirstFileW\""));
	StringCbCat(szLogBuf, MAX_LOG_SIZE, TEXT(",\"param\":[\""));
	StringCbCat(szLogBuf, MAX_LOG_SIZE, lpFileName);
	StringCbCat(szLogBuf, MAX_LOG_SIZE, TEXT("\"]"));
	SendLog(szLogBuf);
	return (realFindFirstFileW)(lpFileName, lpFindFileData);
}


BOOL WINAPI MyDeleteFileW(
	_In_ LPCWSTR lpFileName
) 
{
	TCHAR szLogBuf[MAX_LOG_SIZE];
	StringCbCopy(szLogBuf, MAX_LOG_SIZE, TEXT("\"api\":\"DeleteFileW\""));
	StringCbCat(szLogBuf, MAX_LOG_SIZE, TEXT(",\"param\":[\""));
	StringCbCat(szLogBuf, MAX_LOG_SIZE, lpFileName);
	StringCbCat(szLogBuf, MAX_LOG_SIZE, TEXT("\"]"));
	SendLog(szLogBuf);
	return (realDeleteFileW)(lpFileName);
}


BOOL WINAPI MyCopyFileW(
	_In_ LPCWSTR lpExistingFileName, 
	_In_ LPCWSTR lpNewFileName, 
	_In_ BOOL bFailIfExists
) 
{
	TCHAR szLogBuf[MAX_LOG_SIZE];
	StringCbCopy(szLogBuf, MAX_LOG_SIZE, TEXT("\"api\":\"MyCopyFileW\""));
	StringCbCat(szLogBuf, MAX_LOG_SIZE, TEXT(",\"param\":[\""));
	StringCbCat(szLogBuf, MAX_LOG_SIZE, lpExistingFileName);
	StringCbCat(szLogBuf, MAX_LOG_SIZE, TEXT("\",\""));
	StringCbCat(szLogBuf, MAX_LOG_SIZE, lpNewFileName);
	StringCbCat(szLogBuf, MAX_LOG_SIZE, TEXT("\"]"));
	SendLog(szLogBuf);
	return (realCopyFileW)(lpExistingFileName, lpNewFileName, bFailIfExists);
}


BOOL WINAPI MyMoveFileW(
	_In_ LPCWSTR lpExistingFileName, 
	_In_ LPCWSTR lpNewFileName
) 
{
	TCHAR szLogBuf[MAX_LOG_SIZE];
	StringCbCopy(szLogBuf, MAX_LOG_SIZE, TEXT("\"api\":\"MoveFileW\""));
	StringCbCat(szLogBuf, MAX_LOG_SIZE, TEXT(",\"param\":[\""));
	StringCbCat(szLogBuf, MAX_LOG_SIZE, lpExistingFileName);
	StringCbCat(szLogBuf, MAX_LOG_SIZE, TEXT("\",\""));
	StringCbCat(szLogBuf, MAX_LOG_SIZE, lpNewFileName);
	StringCbCat(szLogBuf, MAX_LOG_SIZE, TEXT("\"]"));
	SendLog(szLogBuf);
	return (realMoveFileW)(lpExistingFileName, lpNewFileName);

}


HANDLE WINAPI MyCreateFileW(
	__in     LPCWSTR lpFileName,
	__in     DWORD dwDesiredAccess,
	__in     DWORD dwShareMode,
	__in_opt LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	__in     DWORD dwCreationDisposition,
	__in     DWORD dwFlagsAndAttributes,
	__in_opt HANDLE hTemplateFile
)
{
	TCHAR szLogBuf[MAX_LOG_SIZE];
	StringCbCopy(szLogBuf, MAX_LOG_SIZE, TEXT("\"api\":\"CreateFileW\""));
	StringCbCat(szLogBuf, MAX_LOG_SIZE, TEXT(",\"param\":[\""));
	StringCbCat(szLogBuf, MAX_LOG_SIZE, lpFileName);
	StringCbCat(szLogBuf, MAX_LOG_SIZE, TEXT("\"]"));
	SendLog(szLogBuf);
	return (realCreateFileW)(lpFileName, dwDesiredAccess, dwShareMode,
		lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);

}


HANDLE WINAPI MyCreateFileA(
	__in     LPCSTR lpFileName,
	__in     DWORD dwDesiredAccess,
	__in     DWORD dwShareMode,
	__in_opt LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	__in     DWORD dwCreationDisposition,
	__in     DWORD dwFlagsAndAttributes,
	__in_opt HANDLE hTemplateFile
)
{
	TCHAR szLogBuf[MAX_LOG_SIZE];
	//logstream << hostname << " " << spy << " " << LogTime() << "account_name=" << "<" << strBuffer << ">,proc_id=<" << _getpid() << ">,proc_name=<" << ProcessName << ">,proc_thread_id=<" << GetCurrentThreadId() << ">,proc_img_path=<" << GetProcessPath() << ">,proc_func_name=<CreateFileA>,func_params=<lpFileName|" << lpFileName << ">";

	return (realCreateFileA)(lpFileName, dwDesiredAccess, dwShareMode,
		lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}