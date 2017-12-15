#include "stdafx.h"
#include "LogThread.h"

DWORD WINAPI LogThreadProc(LPVOID lpParameter)
{
	OutputDebugString(L"This in LogThread\n");

	HANDLE hSemaphoreStatus = NULL;
	HANDLE hMailslotLog = NULL;
	DWORD dwMessageSize = 0;
	DWORD dwMessageRemain = 0;
	BOOL isStopped = FALSE;


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
			//write
		}
	}
	
	CloseHandle(hSemaphoreStatus);
	hSemaphoreStatus = NULL;

	OutputDebugString(L"LogThread Finish\n");

	return 0;
}