﻿// TEST_FileAPI.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>


int main()
{
	system("PAUSE");
	SetFileTime(NULL, NULL, NULL, NULL);
	SetFileValidData(NULL, 0);
	SetEndOfFile(NULL);
	CreateHardLinkW(L"test1", L"test2", NULL);
	SetFileAttributesW(L"test1", 0);
	//FindNextFileW(NULL, NULL);
	//FindFirstFileW(L"test1", NULL);
	DeleteFileW(L"test3");
	CopyFileW(L"test1", L"test2", FALSE);
	MoveFileW(L"test1", L"test2");
	CreateFileW(L"test1", 0, 0, NULL, 0, 0, NULL);
	ReadFile(NULL, NULL, 0, NULL, NULL);
    return 0;
}

