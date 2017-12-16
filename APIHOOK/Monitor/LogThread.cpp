#include "stdafx.h"
#include "LogThread.h"

DWORD WINAPI LogThreadProc(LPVOID lpParameter)
{
	OutputDebugString(L"This in LogThread\n");

	HANDLE hSemaphoreStatus = NULL;
	HANDLE hMailslotLog = NULL;
	HANDLE hLogFile = NULL;
	DWORD dwMessageSize = 0;
	DWORD dwMessageRemain = 0;
	DWORD dwFileSize = MAX_FILE_SIZE+1;
	DWORD dwWrittenSize = 0;
	BOOL isStopped = FALSE;
	WCHAR szReadBuf[MAX_LOG_SIZE];
	WCHAR szCurrentLogPath[MAX_PATH];
	WCHAR szCurrentDirectory[MAX_PATH];

	//Get Monitor.exe directory, in order to read config file
	GetModuleDirectory(szCurrentDirectory);
	StringCbCopy(szCurrentLogPath, MAX_PATH, szCurrentDirectory);
	StringCbCat(szCurrentLogPath, MAX_PATH, L"Logs\\");
	if (CreateDirectory(szCurrentLogPath, NULL))
	{
		OutputDebugString(L"Create New Log Directory\n");
	}
	else if (ERROR_ALREADY_EXISTS == GetLastError())
	{
		OutputDebugString(L"Log Directory Exists\n");
	}
	else
	{
		OutputDebugString(L"CreateDirectory ERROR\n");
		return 0;
	}
	
	//create status semaphore
	hSemaphoreStatus = CreateSemaphore(NULL, 0, 1, L"APIHOOK_Monitor_Semaphore_Status");
	if (!hSemaphoreStatus)
	{
		OutputDebugString(L"CreateSemaphore ERROR\n");
		return 0;
	}

	//create mailslot
	hMailslotLog = CreateMailslot(L"\\\\.\\mailslot\\APIHOOK\\Monitor\\Log", 0, 0, NULL);
	if (INVALID_HANDLE_VALUE == hMailslotLog)
	{
		OutputDebugString(L"CreateMailslot ERROR\n");
		return 0;
	}

	//it is time to create the new process DllInject.exe
	ReleaseSemaphore(hSemaphoreInject, 1, NULL);

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
			szReadBuf[dwMessageSize/sizeof(WCHAR)] = L'\0';
			OutputDebugString(szReadBuf);

			//use new file or not
			if (dwFileSize > MAX_FILE_SIZE)
			{
				if (hLogFile)
				{
					CloseHandle(hLogFile);
				}
				RefreshFileName(szCurrentLogPath,szCurrentDirectory);
				hLogFile = CreateFile(szCurrentLogPath, GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
				if (INVALID_HANDLE_VALUE == hLogFile)
				{
					OutputDebugString(L"CreateFile ERROR\n");
					return 0;
				}
				dwFileSize = 0;
			}
			//do write
			WriteFile(hLogFile, szReadBuf, dwMessageSize, &dwWrittenSize, NULL);
			if (dwMessageSize != dwWrittenSize)
			{
				OutputDebugString(L"WriteFile ERROR\n");
				return 0;
			}
			dwFileSize += dwMessageSize;
		}
	}
	
	CloseHandle(hLogFile);
	hLogFile = NULL;
	CloseHandle(hSemaphoreStatus);
	hSemaphoreStatus = NULL;

	OutputDebugString(L"LogThread Finish\n");

	return 0;
}


VOID RefreshFileName(PWCHAR szCurrentLogPath, LPCWCHAR szCurrentDirectory)
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	WCHAR szBuf[MAX_PATH];
	swprintf_s(szBuf,
		L"Logs\\ALIHOOK_Monitor_Log_%hu_%hu_%hu_%hu_%hu_%hu_%hu.txt", 
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


VOID GetModuleDirectory(PWCHAR szCurrentDirectory)
{
	DWORD dwCurDirPathLen;
	dwCurDirPathLen = GetModuleFileName(NULL, szCurrentDirectory, MAX_PATH);
	if (!dwCurDirPathLen)
	{
		OutputDebugString(L"GetModuleFileName ERROR\n");
		return;
	}
	SIZE_T i = 0;
	StringCbLengthW(szCurrentDirectory, MAX_PATH, &i);
	if (0 == i)
	{
		OutputDebugString(L"GetModuleFileName ERROR\n");
		return;
	}
	for (; i > 0 && L'\\' != szCurrentDirectory[i - 1]; i--) {}
	szCurrentDirectory[i] = L'\0';
	OutputDebugString(szCurrentDirectory);
	OutputDebugString(L"\n");
}