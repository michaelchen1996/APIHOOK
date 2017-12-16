#pragma once

#define MAX_LOG_SIZE 260
#define MAX_FILE_SIZE 1024 * 1024

extern HANDLE hSemaphoreInject;

DWORD WINAPI LogThreadProc(LPVOID lpParameter);
void RefreshFileName(PWCHAR szCurrentLogPath);