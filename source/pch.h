#pragma once

#define true 1
#define false 0
typedef unsigned int uint;
typedef unsigned char byte;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef int bool;

#include <Windows.h>
#include <stdarg.h>
#include <stdint.h>
#include <Shlwapi.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>

#include "../MinHook/includes/MinHook.h"

extern HANDLE g_mainThread;
extern HMODULE g_hmod;
extern bool g_running;