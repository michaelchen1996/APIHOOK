#pragma once

#include "CreateRemoteThreadInject.h"

#ifndef __DLL_INJECT__
#define __DLL_INJECT__


void ReadTargetList(vector<LPTSTR> *szTargetList);
BOOL SetPrivilege(LPCTSTR lpszPrivilege, BOOL bEnablePrivilege);


#endif // !__DLL_INJECT__
