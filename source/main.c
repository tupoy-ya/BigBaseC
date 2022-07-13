#include "logger.h"
#include "hooks.h"
#include "script.h"
#include "invoker.h"

HANDLE g_mainThread;
HMODULE g_hmod;
bool g_running = true;

DWORD WINAPI initialize(LPVOID lpParam) {
	char* baseAdr = (char*)GetModuleHandleA(NULL);
	IMAGE_DOS_HEADER* dosHdr = (IMAGE_DOS_HEADER*)baseAdr;
	IMAGE_NT_HEADERS* ntHdr = (IMAGE_NT_HEADERS*)(baseAdr + dosHdr->e_lfanew);
	DWORD imgSize = ntHdr->OptionalHeader.SizeOfImage;
	createConsoleAndRedirectIo();
	sendLog(consoleGrayOnBlack, "Info", "Init console");
	MH_Initialize();
	sendLog(consoleGrayOnBlack, "Info", "Init MinHook");
	scanPointers(baseAdr, imgSize);
	sendLog(consoleGrayOnBlack, "Info", "Init pointers");
	initInvoker();
	sendLog(consoleGrayOnBlack, "Info", "Init invoker");
	initScr();
	sendLog(consoleGrayOnBlack, "Info", "Init fiber");
	initHooks();
	sendLog(consoleGrayOnBlack, "Info", "Init hooks");
	while (g_running) {
		if (GetAsyncKeyState(VK_END))
			g_running = false;
		Sleep(1);
	}
	MH_Uninitialize();
	sendLog(consoleGrayOnBlack, "Info", "Uninit MinHook");
	uninitScr();
	sendLog(consoleGrayOnBlack, "Info", "Uninit fiber");
	uninitHooks();
	sendLog(consoleGrayOnBlack, "Info", "Uninit hooks");
	removeConsoleAndIoRedirect();
	CloseHandle(g_mainThread);
	FreeLibraryAndExitThread(g_hmod, 0);
}
BOOL APIENTRY DllMain(HINSTANCE hmod, DWORD reason, LPVOID lpvReversed) {
	if (DLL_PROCESS_ATTACH == reason) {
		g_hmod = hmod;
		g_mainThread = CreateThread(NULL, 0, initialize, hmod, 0, NULL);
	}
	return TRUE;
}
