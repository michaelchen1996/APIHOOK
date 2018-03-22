#include "stdafx.h"
#include "SendLog.h"


HANDLE hWriteMailslot = NULL;


void SendLog(LPCTSTR szAPIMessage)
{
	TCHAR szLogMessage[MAX_LOG_SIZE];
	SIZE_T dwLogLength;
	DWORD dwMailslotWritten;

	StringCbCopy(szLogMessage, MAX_LOG_SIZE, TEXT("{\"time\":\""));
	CatLogTime(szLogMessage);
	StringCbCat(szLogMessage, MAX_LOG_SIZE, TEXT("\",\"path\":\""));
	CatProcessPath(szLogMessage);
	StringCbCat(szLogMessage, MAX_LOG_SIZE, TEXT("\","));
	StringCbCat(szLogMessage, MAX_LOG_SIZE, szAPIMessage);
	StringCbCat(szLogMessage, MAX_LOG_SIZE, TEXT("}\r\n"));
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