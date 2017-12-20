// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "HookDll.h"


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
	{
		OutputDebugString(L"HookDll DllMain: DLL_PROCESS_ATTACH\n");	

		Prepare();
		DoHook();
		
		break;
	}

	case DLL_THREAD_ATTACH:
	{
		OutputDebugString(L"HookDll DllMain: DLL_THREAD_ATTACH\n");
		
		break;
	}
    
	case DLL_THREAD_DETACH:
	{
		OutputDebugString(L"HookDll DllMain: DLL_THREAD_DETACH\n");
	
		break;
	}
    
	case DLL_PROCESS_DETACH:
	{
		OutputDebugString(L"HookDll DllMain: DLL_PROCESS_DETACH\n");
	
		DoUnHook();
		Finish();
	
		break;
	}
    }
    return TRUE;
}

