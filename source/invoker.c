#include "invoker.h"
#include "pattern.h"
#include "crossmap.h"
#include "logger.h"
#include "pointers.h"

nativeCtx g_context;
scrNativeHash g_hash;

void initInvoker() {
	g_context.m_base.m_res = &g_context.m_resStack[0];
	g_context.m_base.m_args = &g_context.m_argStack[0];
}

void nativeInit(scrNativeHash hash) {
	for (int i = 0; i < 6093; i++) {
		if (g_crossmap[i].m_u323 == hash) {
			hash = g_crossmap[i].m_u2660;
		}
	}
	g_hash = hash;
	g_context.m_base.m_argCount = 0;
	g_context.m_base.m_dataCount = 0;
}
void* nativeCall() {
	scrNativeHandler handler = g_pointers.m_getNativeHandler(g_pointers.m_nativeRegTbl, g_hash);
	if (handler == 0)
		return NULL;
	handler(&g_context.m_base);
	g_pointers.m_fixVectors(&g_context.m_base);
	return &g_context.m_resStack[0];
}