#pragma once

#ifndef __SEND_LOG__
#define __SEND_LOG__

#define MAX_LOG_SIZE 2600

extern HANDLE hWriteMailslot;

void SendLog(LPCTSTR szAPI, LPCTSTR szParamList[], int n);
void CatProcessPath(LPTSTR szLogMessage);
void CatLogTime(LPTSTR szLogMessage);

#endif // !__SEND_LOG__

