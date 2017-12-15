#include "stdafx.h"
#include "LogThread.h"
#include "Monitor.h"

//HANDLE hSemaphoreInject;

DWORD WINAPI LogThreadProc(LPVOID lpParameter)
{
	OutputDebugString(L"This in LogThread\n");

	HANDLE hSemaphoreStatus = NULL;


	hSemaphoreStatus = CreateSemaphore(NULL, 0, 1, L"APIHOOK_Monitor_Semaphore_Status");
	if (!hSemaphoreStatus)
	{
		OutputDebugString(L"CreateSemaphore ERROR\n");
		return 0;
	}

	//create slot

	ReleaseSemaphore(hSemaphoreInject, 1, NULL);

	//read from slot and write to file
	//WaitForSingleObject(hSemaphoreStatus, 0);
	
	CloseHandle(hSemaphoreStatus);
	hSemaphoreStatus = NULL;
	return 0;
}