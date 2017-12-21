#pragma once

#ifndef __CREATE_REMOTE_THREAD_INJECT__
#define __CREATE_REMOTE_THREAD_INJECT__


void DoSingleInject(vector<LPTSTR> *szTargetList);
void DoContinualInject(vector<LPTSTR> *szTargetList);
DWORD GetProcessID(LPTSTR pName);
BOOL isInjected(DWORD dwProcessId);
void DoInject(HANDLE hProcess, TCHAR *dllName);


#endif // !__CREATE_REMOTE_THREAD_INJECT__
