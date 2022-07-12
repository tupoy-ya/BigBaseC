#pragma once
#include "pointers.h"

inline void* getScriptGlobalPtr(int64_t index) {
	return g_pointers.m_scriptGlobals[index >> 0x12 & 0x3F] + (index & 0x3FFFF);
}