// Monitor.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Monitor.h"

int wmain(int argc, wchar_t *argv[], wchar_t *envp[])
{

	if (2 != argc) {
		ShowHelp();
		int i;
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
		}
	}
	else if (CSTR_EQUAL == CompareString(LOCALE_SYSTEM_DEFAULT, LINGUISTIC_IGNORECASE, argv[1], -1, L"start", -1))
	{
		StartMonitor();
	}
	else if (CSTR_EQUAL == CompareString(LOCALE_SYSTEM_DEFAULT, LINGUISTIC_IGNORECASE, argv[1], -1, L"stop", -1))
	{
		StopMonitor();
	}
	else if (CSTR_EQUAL == CompareString(LOCALE_SYSTEM_DEFAULT, LINGUISTIC_IGNORECASE, argv[1], -1, L"restart", -1))
	{
		RestartMonitor();
	}
	else
	{
		OutputDebugString(L"Tooooooo Many\n");
		ShowHelp();
	}

	system("PAUSE");
    return 0;
}

void ShowHelp()
{
	OutputDebugString(L"Help: Monitor.exe start|stop|restart\n");
	//TODO: showhelp
}

void StartMonitor()
{
	OutputDebugString(L"Do start \n");

	HANDLE hMutexSingleton = NULL;
	HANDLE hThreadLog = NULL;
	WCHAR szDllInjectPath[MAX_PATH];

	hMutexSingleton = CreateMutex(NULL, TRUE, L"APIHOOK_Monitor_Mutex_Singleton");
	if (ERROR_ALREADY_EXISTS == GetLastError())
	{
		OutputDebugString(L"ERROR_ALREADY_EXISTS\n");
		printf("ERROR_ALREADY_EXISTS\n");
		ShowHelp();
		return;
	}
	if (!hMutexSingleton)
	{
		OutputDebugString(L"CreateMutex ERROR\n");
		return;
	}

	hSemaphoreInject = CreateSemaphore(NULL, 0, 1, L"APIHOOK_Monitor_Semaphore_Inject");
	if (!hSemaphoreInject)
	{
		OutputDebugString(L"CreateSemaphore ERROR\n");
		return;
	}

	//create LogThread
	hThreadLog = CreateThread(NULL, 0, LogThreadProc, NULL, 0, NULL);
	if (!hThreadLog)
	{
		OutputDebugString(L"CreateThread ERROR\n");
		return;
	}
	WaitForSingleObject(hSemaphoreInject, INFINITE);

	//create DllInject.exe process
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	StringCbCopy(szDllInjectPath, MAX_PATH, szCurrentDirectory);
	StringCbCat(szDllInjectPath, MAX_PATH, L"DllInject.exe");
	if (!CreateProcess(szDllInjectPath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		OutputDebugString(L"CreateProcess DllInject.exe ERROR\n");
		return;
	}
	OutputDebugString(L"CreateProcess DllInject.exe\n");
	WaitForSingleObject(pi.hProcess, INFINITE);
	OutputDebugString(L"DllInject.exe Finished\n");

	WaitForSingleObject(hThreadLog, INFINITE);
	ReleaseMutex(hMutexSingleton);
	CloseHandle(hMutexSingleton);
	hMutexSingleton = NULL;
	CloseHandle(hSemaphoreInject);
	hSemaphoreInject = NULL;
}

void StopMonitor()
{
	OutputDebugString(L"Do stop \n");

	WCHAR szDllUnInjectPath[MAX_PATH];
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	StringCbCopy(szDllUnInjectPath, MAX_PATH, szCurrentDirectory);
	StringCbCat(szDllUnInjectPath, MAX_PATH, L"DllUnInject.exe");
	if (!CreateProcess(szDllUnInjectPath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		OutputDebugString(L"CreateProcess DllUnInject.exe ERROR\n");
		return;
	}
	OutputDebugString(L"CreateProcess DllUnInject.exe\n");
	WaitForSingleObject(pi.hProcess, INFINITE);
	OutputDebugString(L"DllUnInject.exe Finished\n");

}

void RestartMonitor()
{
	OutputDebugString(L"Do restart \n");
	StopMonitor();
	StartMonitor();
}