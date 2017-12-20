#include "stdafx.h"
#include "SendLog.h"


HANDLE hWriteMailslot = NULL;


void SendLog(LPCTSTR szLogMessage)
{
	OutputDebugString(szLogMessage);
	
	SIZE_T dwLogLength;
	DWORD dwMailslotWritten;

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