#include "pattern.h"

int8_t aob[0xFF];
char mask[0xFF];
int g_foundPatterns;
int g_totalPatterns;
size_t sigByteCount(char const* sig) {
	size_t count = 0;
	for (size_t i = 0; sig[i]; ++i)
		if (sig[i] == ' ')
			++count;
	return ++count;
}
int hexCharToInt(char const c) {
	if (c >= 'a' && c <= 'f')
		return (int)c - 87;
	if (c >= 'A' && c <= 'F')
		return (int)c - 55;
	if (c >= '0' && c <= '9')
		return (int)c - 48;
	return 0;
}
char makeHexByteIntoChar(char first, char second) { return (char)(hexCharToInt(first) * 0x10 + hexCharToInt(second) & 0xFF); }
void generateAob(char const* sig) {
	size_t aobCursor = 0;
	for (size_t sigCursor = 0; sigCursor <= strlen(sig);) {
		if (sig[sigCursor] == '?')
			aob[aobCursor] = '?', ++aobCursor, sigCursor += 2;
		else if (sig[sigCursor] == ' ')
			++sigCursor;
		else
			aob[aobCursor] = makeHexByteIntoChar(sig[sigCursor], sig[sigCursor + 1]), ++aobCursor, sigCursor += 3;
	}
}
void generateMask(char const* sig) {
	size_t maskCursor = 0;
	for (size_t sigCursor = 0; sigCursor < strlen(sig) - 1;) {
		if (sig[sigCursor] == '?')
			mask[maskCursor] = '?', ++maskCursor, sigCursor += 2;
		else if (sig[sigCursor] == ' ')
			++sigCursor;
		else
			mask[maskCursor] = 'x', ++maskCursor, sigCursor += 3;
	}
}
void zeroAobAndMaskBuffers(void) {
	memset(aob, NULL, 0xFF);
	memset(mask, NULL, 0xFF);
}
void fillAobAndMaskBuffers(char const* sig) {
	zeroAobAndMaskBuffers();
	generateAob(sig);
	generateMask(sig);
}
bool doesSigMatch(int8_t const* scanCursor) {
	for (size_t cursor = 0; cursor < strlen(mask); ++cursor)
		if (mask[cursor] != '?' && aob[cursor] != scanCursor[cursor])
			return false;
	return true;
}
int8_t* rip(int8_t* address) { 
	return address ? address + *(int*)address + 4 : NULL;
}
int8_t* scan(void* baseAdr, size_t imgSize, char const* name, char const* sig, int64_t offset) {
	fillAobAndMaskBuffers(sig);
	g_totalPatterns++;
	int8_t* scanEnd = ((int8_t*)baseAdr + imgSize) - sigByteCount(sig);
	for (int8_t* scanCursor = baseAdr; scanCursor < scanEnd; ++scanCursor)
		if (doesSigMatch(scanCursor)) {
			g_foundPatterns++;
			sendLog(consoleGrayOnBlack, "Patterns", "Found %s", name);
			return scanCursor + offset;
		}
	sendLog(consoleGrayOnBlack, "Patterns", "Failed to find %s", name);
	return NULL;
}