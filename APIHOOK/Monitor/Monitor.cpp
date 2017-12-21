// Monitor.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Monitor.h"

int wmain(int argc, wchar_t *argv[], wchar_t *envp[])
{
	if (2 != argc) {
		ShowHelp();
		int i;
		printf_s("1.start\n2.stop\n3.restart\n\ninput:");
		scanf_s("%d", &i);
		switch(i)
		{
		case 1:
			StartMonitor();
			break;
		case 2:
			StopMonitor();
			break;
		case 3:
			RestartMonitor();
			break;
		default:
			ShowHelp();
		}
	}
	else if (CSTR_EQUAL == CompareString(LOCALE_SYSTEM_DEFAULT, LINGUISTIC_IGNORECASE, argv[1], -1, TEXT("start"), -1))
	{
		StartMonitor();
	}
	else if (CSTR_EQUAL == CompareString(LOCALE_SYSTEM_DEFAULT, LINGUISTIC_IGNORECASE, argv[1], -1, TEXT("stop"), -1))
	{
		StopMonitor();
	}
	else if (CSTR_EQUAL == CompareString(LOCALE_SYSTEM_DEFAULT, LINGUISTIC_IGNORECASE, argv[1], -1, TEXT("restart"), -1))
	{
		RestartMonitor();
	}
	else
	{
		OutputDebugString(TEXT("Tooooooo Many\n"));
		ShowHelp();
	}

	system("PAUSE");
    return 0;
}


void ShowHelp()
{
	printf_s("Help: Monitor.exe start|stop|restart\n");
}


void StartMonitor()
{
	OutputDebugString(TEXT("Do start \n"));

	/*
	HANDLE hMutexSingleton = NULL;

	hMutexSingleton = CreateMutex(NULL, TRUE, TEXT("APIHOOK_Monitor_Mutex_Singleton"));
	if (ERROR_ALREADY_EXISTS == GetLastError())
	{
		OutputDebugString(TEXT("ERROR_ALREADY_EXISTS\n"));
		printf("ERROR_ALREADY_EXISTS\n");
		ShowHelp();
		return;
	}
	if (!hMutexSingleton)
	{
		OutputDebugString(TEXT("CreateMutex ERROR\n"));
		return;
	}
	*/

	HANDLE hTargetListFile = NULL;
	TCHAR szTargetListFilePath[MAX_PATH];

	GetCurrentDirectory(MAX_PATH, szTargetListFilePath);
	StringCbCat(szTargetListFilePath, MAX_PATH, TEXT("\\TargetList.txt"));
	hTargetListFile = CreateFile(szTargetListFilePath, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hTargetListFile)
	{
		OutputDebugString(TEXT("CreateFile ERROR\n"));
		switch (GetLastError())
		{
		case ERROR_FILE_NOT_FOUND:
			OutputDebugString(TEXT("TargetList.txt is not found\n"));
			printf_s("TargetList.txt is not found\n");
			break;
		case ERROR_SHARING_VIOLATION:
			OutputDebugString(TEXT("Monitor.exe is already running\n"));
			printf_s("Monitor.exe is already running\n");
			break;
		default:
			printf_s("create file targetlist error: %d\n", GetLastError());
			break;
		}
		return;
	}

	Log();

	CloseHandle(hTargetListFile);
	hTargetListFile = NULL;

	/*
	ReleaseMutex(hMutexSingleton);
	CloseHandle(hMutexSingleton);
	hMutexSingleton = NULL;
	*/
}


void StopMonitor()
{
	OutputDebugString(TEXT("Do stop \n"));
	HANDLE hProcess = NULL;
	hProcess = MyCreateProcess(TEXT("DllUnInject.exe"));
	WaitForSingleObject(hProcess, INFINITE);

}


void RestartMonitor()
{
	OutputDebugString(TEXT("Do restart \n"));
	StopMonitor();
	StartMonitor();
}


HANDLE MyCreateProcess(LPCTSTR szProcessName)
{
	TCHAR szProcessPath[MAX_PATH];
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	GetCurrentDirectory(MAX_PATH, szProcessPath);
	StringCbCat(szProcessPath, MAX_PATH, TEXT("\\"));
	StringCbCat(szProcessPath, MAX_PATH, szProcessName);
	OutputDebugString(TEXT("CreateProcess "));
	OutputDebugString(szProcessPath);
	OutputDebugString(TEXT("\n"));
	if (!CreateProcess(szProcessPath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		OutputDebugString(TEXT("CreateProcess "));
		OutputDebugString(szProcessName);
		OutputDebugString(TEXT(" ERROR\n"));
		return NULL;
	}
	/*WaitForSingleObject(pi.hProcess, INFINITE);
	OutputDebugString(szProcessName);
	OutputDebugString(TEXT(" Finished\n"));*/
	return pi.hProcess;
}
