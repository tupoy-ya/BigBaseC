#pragma once

typedef unsigned int uint;
typedef unsigned char byte;
typedef unsigned char uchar;
typedef unsigned short ushort;

#include <stdbool.h>
#include <windows.h>
#include <stdarg.h>
#include <stdint.h>
#include <shlwapi.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>

#if defined(__MINGW32__)
#include <_mingw.h>
#endif

#include "include/MinHook.h"

extern HANDLE g_mainThread;
extern HMODULE g_hmod;
extern bool g_running;
