#pragma once

#define MAX_TARGET_NUM 10

void DoSearchProcess(LPCWCHAR dwProcesName);
void DoSearchModule(DWORD dwProcessId);
void DoDllUnInject(DWORD dwProcessId, HMODULE hModule);
void DoReleaseSemaphoreStatus();
BOOL SetPrivilege(LPCTSTR lpszPrivilege, BOOL bEnablePrivilege);