#include "logger.h"

bool consoleEnabled = true;
static char logBuf[0xFFF];

void sendLog(uint16_t color, char const* info, char const* fmt, ...) {
	if (!consoleEnabled)
		return;
	ZeroMemory(logBuf, sizeof(logBuf));
	va_list valist;
	va_start(valist, fmt);
	vsprintf_s(logBuf, sizeof(logBuf), fmt, valist);
	va_end(valist);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	time_t t = time(NULL);
	struct tm* tStruct = localtime(&t);
	printf("%i:%i:%i | %s | %s\n", tStruct->tm_hour, tStruct->tm_min, tStruct->tm_sec, info, logBuf);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), consoleWhiteOnBlack);
}
void createConsoleAndRedirectIo() {
	if (!consoleEnabled)
		return;
	if (!AttachConsole(GetCurrentProcessId()))
		AllocConsole();
	SetConsoleTitleA("BigBaseC");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
}
void removeConsoleAndIoRedirect() {
	if (!consoleEnabled)
		return;
	fclose(stdout);
	FreeConsole();
}