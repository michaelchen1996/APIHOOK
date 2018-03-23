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
		//SendLog(szLogBuf);
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
	LPCTSTR szParamList[1];
	int n = 0;
	if (hFile != NULL)
	{
		GetFinalPathNameByHandle(hFile, szFilepath, MAX_PATH, VOLUME_NAME_DOS);
		szParamList[0] = szFilepath;
		n = 1;	
	}
	SendLog(TEXT("ReadFile"), szParamList, n);
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
	LPCTSTR szParamList[1];
	int n = 0;
	if (hFile != NULL)
	{
		GetFinalPathNameByHandle(hFile, szFilepath, MAX_PATH, VOLUME_NAME_DOS);
		szParamList[0] = szFilepath;
		n = 1;
	}
	SendLog(TEXT("SetFileTime"), szParamList, n);
	return (realSetFileTime)(hFile, lpCreationTime, lpLastAccessTime, lpLastWriteTime);
}


BOOL WINAPI MySetFileValidData(
	_In_ HANDLE hFile, 
	_In_ LONGLONG ValidDataLength
) 
{
	TCHAR szLogBuf[MAX_LOG_SIZE];
	TCHAR szFilepath[MAX_PATH];
	LPCTSTR szParamList[1];
	int n = 0;
	if (hFile != NULL)
	{
		GetFinalPathNameByHandle(hFile, szFilepath, MAX_PATH, VOLUME_NAME_DOS);
		szParamList[0] = szFilepath;
		n = 1;
	}
	SendLog(TEXT("SetFileValidData"), szParamList, n);

	return (realSetFileValidData)(hFile, ValidDataLength);
}


BOOL WINAPI MySetEndOfFile(
	_In_ HANDLE hFile
) 
{
	TCHAR szLogBuf[MAX_LOG_SIZE];
	TCHAR szFilepath[MAX_PATH];
	LPCTSTR szParamList[1];
	int n = 0;
	if (hFile != NULL)
	{
		GetFinalPathNameByHandle(hFile, szFilepath, MAX_PATH, VOLUME_NAME_DOS);
		szParamList[0] = szFilepath;
		n = 1;
	}
	SendLog(TEXT("SetEndOfFile"), szParamList, n);
	return (realSetEndOfFile)(hFile);
}


BOOL WINAPI MyCreateHardLinkW(
	_In_ LPCWSTR lpFileName, 
	_In_ LPCWSTR lpExistingFileName, 
	_Reserved_ LPSECURITY_ATTRIBUTES lpSecurityAttributes
) 
{
	TCHAR szLogBuf[MAX_LOG_SIZE];
	LPCTSTR szParamList[] = { lpFileName , lpExistingFileName };
	SendLog(TEXT("CreateHardLinkW"), szParamList, 2);
	return (realCreateHardLinkW)(lpFileName, lpExistingFileName, lpSecurityAttributes);
}


BOOL WINAPI MySetFileAttributesW(
	_In_ LPCWSTR lpFileName, 
	_In_ DWORD dwFileAttributes
) 
{
	TCHAR szLogBuf[MAX_LOG_SIZE];
	LPCTSTR szParamList[] = { lpFileName };
	SendLog(TEXT("SetFileAttributesW"), szParamList, 1);
	return (realSetFileAttributesW)(lpFileName, dwFileAttributes);
}


BOOL WINAPI MyFindNextFileW(
	_In_ HANDLE hFindFile, 
	_Out_ LPWIN32_FIND_DATAW lpFindFileData
) 
{
	TCHAR szLogBuf[MAX_LOG_SIZE];
	TCHAR szFilepath[MAX_PATH];
	LPCTSTR szParamList[1];
	int n = 0;
	if (hFindFile != NULL)
	{
		GetFinalPathNameByHandle(hFindFile, szFilepath, MAX_PATH, VOLUME_NAME_DOS);
		n++;
		szParamList[0] = szFilepath;
	}
	SendLog(TEXT("FindNextFileW"), szParamList, n);
	return (realFindNextFileW)(hFindFile, lpFindFileData);
}


HANDLE WINAPI MyFindFirstFileW(
	_In_ LPCWSTR lpFileName, 
	_Out_ LPWIN32_FIND_DATAW lpFindFileData
) 
{
	TCHAR szLogBuf[MAX_LOG_SIZE];
	LPCTSTR szParamList[] = { lpFileName };
	SendLog(TEXT("FindFirstFileW"), szParamList, 1);
	return (realFindFirstFileW)(lpFileName, lpFindFileData);
}


BOOL WINAPI MyDeleteFileW(
	_In_ LPCWSTR lpFileName
) 
{
	TCHAR szLogBuf[MAX_LOG_SIZE];
	LPCTSTR szParamList[] = { lpFileName };
	SendLog(TEXT("DeleteFileW"), szParamList, 1);
	return (realDeleteFileW)(lpFileName);
}


BOOL WINAPI MyCopyFileW(
	_In_ LPCWSTR lpExistingFileName, 
	_In_ LPCWSTR lpNewFileName, 
	_In_ BOOL bFailIfExists
) 
{
	TCHAR szLogBuf[MAX_LOG_SIZE];
	LPCTSTR szParamList[] = { lpExistingFileName, lpNewFileName };
	SendLog(TEXT("CopyFileW"), szParamList, 2);
	return (realCopyFileW)(lpExistingFileName, lpNewFileName, bFailIfExists);
}


BOOL WINAPI MyMoveFileW(
	_In_ LPCWSTR lpExistingFileName, 
	_In_ LPCWSTR lpNewFileName
) 
{
	TCHAR szLogBuf[MAX_LOG_SIZE];
	LPCTSTR szParamList[] = { lpExistingFileName, lpNewFileName };
	SendLog(TEXT("MoveFileW"), szParamList, 2);
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
	LPCTSTR szParamList[] = { lpFileName };
	SendLog(TEXT("CreateFileW"), szParamList, 1);
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