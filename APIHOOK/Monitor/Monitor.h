#pragma once

#include "LogThread.h"

HANDLE hSemaphoreInject = NULL;
WCHAR szCurrentDirectory[MAX_PATH];

void ShowHelp();
void StartMonitor();
void StopMonitor();
void RestartMonitor();