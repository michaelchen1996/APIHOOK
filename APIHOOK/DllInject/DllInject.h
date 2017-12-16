#pragma once

VOID GetModuleDirectory(PWCHAR szCurrentDirectory);
DWORD ReadTargetList(LPCWCHAR szCurrentDirectory, LPDWORD dwPIdList);
VOID DoInject(HANDLE hProcess, WCHAR *dllName);
DWORD GetProcessID(WCHAR *pName);
BOOL SetPrivilege(LPCTSTR lpszPrivilege, BOOL bEnablePrivilege);