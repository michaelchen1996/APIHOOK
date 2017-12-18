// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
	{
		OutputDebugString(L"DllMain: DLL_PROCESS_ATTACH\n");
		printf("%s", "DllMain: DLL_PROCESS_ATTACH\n");
	}
    case DLL_THREAD_ATTACH:
	{
		OutputDebugString(L"DllMain: DLL_THREAD_ATTACH\n");
		printf("%s", "DllMain: DLL_THREAD_ATTACH\n");
	}
    case DLL_THREAD_DETACH:
	{
		OutputDebugString(L"DllMain: DLL_THREAD_DETACH\n");
		printf("%s", "DllMain: DLL_THREAD_DETACH\n");
	}
    case DLL_PROCESS_DETACH:
	{
		OutputDebugString(L"DllMain: DLL_PROCESS_DETACH\n");
		printf("%s", "DllMain: DLL_PROCESS_DETACH\n");
	}
        break;
    }
    return TRUE;
}

