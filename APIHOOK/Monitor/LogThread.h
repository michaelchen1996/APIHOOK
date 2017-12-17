#pragma once

#define MAX_LOG_SIZE 260
#define MAX_FILE_SIZE 1024 * 1024

extern HANDLE hSemaphoreInject;
extern WCHAR szCurrentDirectory[MAX_PATH];

DWORD WINAPI LogThreadProc(LPVOID lpParameter);
VOID RefreshFileName(PWCHAR szCurrentLogPath);
VOID GetModuleDirectory(PWCHAR szCurrentDirectory);