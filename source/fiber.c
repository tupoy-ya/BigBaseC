#include "fiber.h"
#include <winbase.h>

void fbrInit(fbr* this, void(*fn)()) {
	this->m_scrFbr = CreateFiber(0, (LPFIBER_START_ROUTINE)fn, this);
	this->m_fn = fn;
	this->m_wakeAt = GetTickCount();
}
void fbrUninit(fbr* this) {
	if (this->m_scrFbr)
		DeleteFiber(this->m_scrFbr);
}
void fbrTick(fbr* this) {
	if (this->m_wakeAt <= GetTickCount()) {
		this->m_mainFbr = IsThreadAFiber() ? GetCurrentFiber() : ConvertThreadToFiber(NULL);
		SwitchToFiber(this->m_scrFbr);
	}
}
void fbrYield(fbr* this, uint32_t time) {
	this->m_wakeAt = GetTickCount() + time;
	SwitchToFiber(this->m_mainFbr);
}
fbr* getCurFbr() { return (fbr*)(GetFiberData()); }
