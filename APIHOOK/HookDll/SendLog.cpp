#include "stdafx.h"
#include "SendLog.h"


HANDLE hWriteMailslot = NULL;


void SendLog(LPCTSTR szAPI, LPCTSTR szParamList[], int n)
{
	TCHAR szLogMessage[MAX_LOG_SIZE];
	SIZE_T dwLogLength;
	DWORD dwMailslotWritten;

	StringCbCopy(szLogMessage, MAX_LOG_SIZE, TEXT("{\"time\":\""));
	CatLogTime(szLogMessage);
	StringCbCat(szLogMessage, MAX_LOG_SIZE, TEXT("\",\"process\":\""));
	CatProcessPath(szLogMessage);
	StringCbCat(szLogMessage, MAX_LOG_SIZE, TEXT("\",\"api\":\""));
	StringCbCat(szLogMessage, MAX_LOG_SIZE, szAPI);
	StringCbCat(szLogMessage, MAX_LOG_SIZE, TEXT("\",\"param\":["));
	for (int i = 0; i < n; i++)
	{
		if (i > 0)
		{
			StringCbCat(szLogMessage, MAX_LOG_SIZE, TEXT(","));
		}
		StringCbCat(szLogMessage, MAX_LOG_SIZE, TEXT("\""));
		StringCbCat(szLogMessage, MAX_LOG_SIZE, szParamList[i]);
		StringCbCat(szLogMessage, MAX_LOG_SIZE, TEXT("\""));
	}
	StringCbCat(szLogMessage, MAX_LOG_SIZE, TEXT("]}\r\n"));
	OutputDebugString(szLogMessage);
	StringCbLength(szLogMessage, MAX_LOG_SIZE, &dwLogLength);
	if (dwLogLength > MAX_LOG_SIZE)
	{
		dwLogLength = MAX_LOG_SIZE;
	}
	WriteFile(hWriteMailslot, szLogMessage, dwLogLength, &dwMailslotWritten, NULL);
	if (dwLogLength != dwMailslotWritten)
	{
		OutputDebugString(TEXT("Write Log Mailslot ERROR\n"));
	}
}

void CatProcessPath(LPTSTR szLogMessage) {
	TCHAR szPathName[MAX_PATH];
	GetModuleFileNameEx(GetCurrentProcess(), NULL, szPathName, MAX_PATH);
	StringCbCat(szLogMessage, MAX_LOG_SIZE, szPathName);
}

void CatLogTime(LPTSTR szLogMessage) {
	TCHAR szTime[MAX_LOG_SIZE];
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	wsprintf(
		szTime, 
		TEXT("%4d-%02d-%02d-%02d-%02d-%02d-%03d\0"), 
		sys.wYear, 
		sys.wMonth, 
		sys.wDay, 
		sys.wHour, 
		sys.wMinute, 
		sys.wSecond, 
		sys.wMilliseconds
	);
	StringCbCat(szLogMessage, MAX_LOG_SIZE, szTime);
}