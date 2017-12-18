#pragma once

void GetModuleDirectory(PWCHAR szCurrentDirectory);
void ReadTargetListAndDo(LPCWCHAR szCurrentDirectory);
void DoSearchProcess(LPCWCHAR dwProcesName);
void DoSearchModule(DWORD dwProcessId);
void DoDllUnInject(DWORD dwProcessId, HMODULE hModule);
void DoReleaseSemaphoreStatus();
BOOL SetPrivilege(LPCTSTR lpszPrivilege, BOOL bEnablePrivilege);