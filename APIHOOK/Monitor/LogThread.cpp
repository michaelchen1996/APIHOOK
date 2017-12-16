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


	hSemaphoreStatus = CreateSemaphore(NULL, 0, 1, L"APIHOOK_Monitor_Semaphore_Status");
	if (!hSemaphoreStatus)
	{
		OutputDebugString(L"CreateSemaphore ERROR\n");
		return 0;
	}

	//create slot
	hMailslotLog = CreateMailslot(L"\\\\.\\mailslot\\APIHOOK\\Monitor\\Log", 0, 0, NULL);
	if (INVALID_HANDLE_VALUE == hMailslotLog)
	{
		OutputDebugString(L"CreateMailslot ERROR\n");
		return 0;
	}

	ReleaseSemaphore(hSemaphoreInject, 1, NULL);
	//WaitForSingleObject(hSemaphoreStatus, INFINITE);
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
			//OutputDebugString(L"\n");
			printf("messagesize: %u\n", dwMessageSize);
			//use new file or not
			if (dwFileSize > MAX_FILE_SIZE)
			{
				if (hLogFile)
				{
					CloseHandle(hLogFile);
				}
				RefreshFileName(szCurrentLogPath);
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


void RefreshFileName(PWCHAR szCurrentLogPath)
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	WCHAR szBuf[MAX_PATH];
	swprintf_s(szBuf,
		L"C:\\Users\\michael\\Documents\\Logs\\ALIHOOK_Monitor_Log_%hu_%hu_%hu_%hu_%hu_%hu_%hu.txt", 
		st.wYear, 
		st.wMonth,
		st.wDay,
		st.wHour,
		st.wMinute,
		st.wSecond,
		st.wMilliseconds
	);
	StringCbCopy(szCurrentLogPath, MAX_PATH, szBuf);
}