#pragma once

typedef struct fbr {
	void* m_mainFbr;
	void* m_scrFbr;
	void (*m_fn)();
	uint32_t m_wakeAt;
} fbr;
void fbrInit(fbr* this, void(*fn)());
void fbrUninit(fbr* this);
void fbrTick(fbr* this);
void fbrYield(fbr* this, uint32_t time);
fbr* getCurFbr();

inline void WAIT(uint32_t time) { fbrYield(getCurFbr(), time); }