#pragma once
#include "classes.h"
#include "pointers.h"
typedef struct lbls {
	char const* label;
	char const* contents;
} lbls;
#define lbls(label, contents) (lbls){ label, contents }

extern enum eNetworkEvents;

extern lbls m_gameLabels[100];
extern int g_labelNum;
GtaThread* getCurScrThr();
void setCurScrThr(char* tls, GtaThread* thr);
GtaThread* getGtaThreadByHash(uint hash);

inline void lbls_addText(char const* lbl, char const* cnts) {
	if (g_labelNum > 0) {
		for (int i = 0; i < g_labelNum; i++) {
			if (strcmp(m_gameLabels[i].label, lbl)) {
				m_gameLabels[g_labelNum] = lbls(lbl, cnts);
				g_labelNum++;
			}
		}
	}
	else {
		m_gameLabels[g_labelNum] = lbls(lbl, cnts);
		g_labelNum++;
	}
}
inline void lbls_removeText(char const* lbl) {
	if (g_labelNum > 0) {
		for (int i = 0; i < g_labelNum; i++) {
			if (!strcmp(m_gameLabels[i].label, lbl)) {
				memset(m_gameLabels[g_labelNum].label, NULL, sizeof(m_gameLabels[g_labelNum].label));
				memset(m_gameLabels[g_labelNum].contents, NULL, sizeof(m_gameLabels[g_labelNum].contents));
				g_labelNum--;
			}
		}
	}
}

void initHooks();
void uninitHooks();