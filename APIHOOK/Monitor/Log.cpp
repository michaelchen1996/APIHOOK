#include "stdafx.h"
#include "Log.h"

void Log()
{
	OutputDebugString(TEXT("This in LogThread\n"));

	HANDLE hSemaphoreStatus = NULL;
	HANDLE hMailslotLog = NULL;
	HANDLE hLogFile = NULL;
	DWORD dwMessageSize = 0;
	DWORD dwMessageRemain = 0;
	DWORD dwFileSize = MAX_FILE_SIZE+1;
	DWORD dwWrittenSize = 0;
	BOOL isStopped = FALSE;
	TCHAR szReadBuf[MAX_LOG_SIZE];
	TCHAR szCurrentLogPath[MAX_PATH];
	TCHAR szCurrentDirectory[MAX_PATH];

	//Get log directory, in order to read config file
	GetCurrentDirectory(MAX_PATH, szCurrentDirectory);
	StringCbCopy(szCurrentLogPath, MAX_PATH, szCurrentDirectory);
	StringCbCat(szCurrentLogPath, MAX_PATH, TEXT("\\Logs\\"));
	if (CreateDirectory(szCurrentLogPath, NULL))
	{
		OutputDebugString(TEXT("Create New Log Directory\n"));
	}
	else if (ERROR_ALREADY_EXISTS == GetLastError())
	{
		OutputDebugString(TEXT("Log Directory Exists\n"));
	}
	else
	{
		OutputDebugString(TEXT("CreateDirectory ERROR\n"));
		return;
	}
	
	//create status semaphore
	hSemaphoreStatus = CreateSemaphore(NULL, 0, 2, TEXT("APIHOOK_Monitor_Semaphore_Status"));
	if (!hSemaphoreStatus)
	{
		OutputDebugString(TEXT("CreateSemaphore ERROR\n"));
		return;
	}

	//create mailslot
	hMailslotLog = CreateMailslot(TEXT("\\\\.\\mailslot\\APIHOOK\\Monitor\\Log"), 0, 0, NULL);
	if (INVALID_HANDLE_VALUE == hMailslotLog)
	{
		OutputDebugString(TEXT("CreateMailslot ERROR\n"));
		return;
	}

	//it is time to create the new process DllInject.exe
	MyCreateProcess(TEXT("DllInject.exe"));

	//read from slot and write to file
	while (!isStopped || 1 < dwMessageRemain)
	{
		if (!isStopped && WAIT_OBJECT_0 == WaitForSingleObject(hSemaphoreStatus, 0))
		{
			isStopped = TRUE;
		}
		GetMailslotInfo(hMailslotLog, NULL, &dwMessageSize, &dwMessageRemain, NULL);
		if (0 < dwMessageRemain)
		{
			//read
			ReadFile(hMailslotLog, szReadBuf, dwMessageSize, NULL, NULL);
			szReadBuf[dwMessageSize/sizeof(WCHAR)] = TEXT('\0');
			OutputDebugString(szReadBuf);

			//use new file or not
			if (dwFileSize > MAX_FILE_SIZE)
			{
				if (hLogFile)
				{
					CloseHandle(hLogFile);
				}
				RefreshFileName(szCurrentLogPath, szCurrentDirectory);
				hLogFile = CreateFile(szCurrentLogPath, GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
				if (INVALID_HANDLE_VALUE == hLogFile)
				{
					OutputDebugString(TEXT("CreateFile ERROR\n"));
					return;
				}
				dwFileSize = 0;
			}
			//do write
			WriteFile(hLogFile, szReadBuf, dwMessageSize, &dwWrittenSize, NULL);
			if (dwMessageSize != dwWrittenSize)
			{
				OutputDebugString(TEXT("WriteFile ERROR\n"));
				return;
			}
			dwFileSize += dwMessageSize;
		}
		if (!isStopped && dwMessageRemain <= 1)
		{
			Sleep(1000);
			OutputDebugString(TEXT("Sleep Here\n"));
		}
	}
	
	CloseHandle(hLogFile);
	hLogFile = NULL;
	CloseHandle(hSemaphoreStatus);
	hSemaphoreStatus = NULL;

	OutputDebugString(TEXT("LogThread Finish\n"));

	return;
}


void RefreshFileName(PTCHAR szCurrentLogPath, LPCTSTR szCurrentDirectory)
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	TCHAR szBuf[MAX_PATH];
	swprintf_s(szBuf,
		TEXT("\\Logs\\ALIHOOK_Monitor_Log_%hu_%hu_%hu_%hu_%hu_%hu_%hu.txt"),
		st.wYear, 
		st.wMonth,
		st.wDay,
		st.wHour,
		st.wMinute,
		st.wSecond,
		st.wMilliseconds
	);
	StringCbCopy(szCurrentLogPath, MAX_PATH, szCurrentDirectory);
	StringCbCat(szCurrentLogPath, MAX_PATH, szBuf);
}