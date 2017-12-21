#pragma once

#ifndef __MONITOR__
#define __MONITOR__
#include "Log.h"
#endif // !__MONITOR__


void ShowHelp();
void StartMonitor();
void StopMonitor();
void RestartMonitor();
HANDLE MyCreateProcess(LPCTSTR szProcessName);