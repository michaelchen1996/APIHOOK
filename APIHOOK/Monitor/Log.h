#pragma once

#ifndef __LOG__
#define __LOG__
#include "Monitor.h"
#endif // !__LOG__


#define MAX_LOG_SIZE 260
#define MAX_FILE_SIZE 1024 * 1024


void Log();
void RefreshFileName(PTCHAR szCurrentLogPath, LPCTSTR szCurrentDirectory);
