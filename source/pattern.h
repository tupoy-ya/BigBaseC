#pragma once
#include "logger.h"

extern int g_foundPatterns;
extern int g_totalPatterns;
int8_t* rip(int8_t* address);
int8_t* scan(void* baseAdr, size_t imgSize, char const* name, char const* sig, int64_t offset);
inline void printPatternNumbers() {
	sendLog(consoleGrayOnBlack, "Patterns", "Found %i/%i patterns", g_foundPatterns, g_totalPatterns);
}