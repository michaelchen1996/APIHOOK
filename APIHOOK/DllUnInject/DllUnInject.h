#pragma once

#define MAX_TARGET_NUM 10

void DoSearchProcess(LPCWCHAR dwProcesName);
void DoSearchModule(DWORD dwProcessId);
void DoDllUnInject(DWORD dwProcessId, HMODULE hEasyHook64, HMODULE hHookDll);
void DoReleaseSemaphoreStatus();
BOOL SetPrivilege(LPCTSTR lpszPrivilege, BOOL bEnablePrivilege);