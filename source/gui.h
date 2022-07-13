#pragma once
#include "natives.h"

extern bool g_opened;
//Positoning
extern float g_posX;
extern float g_posY;
extern float g_width;
//Colors
extern RGBA g_fontColor;
extern RGBA g_rectColor;
extern RGBA g_subtitleColor;
extern RGBA g_subtitleTextColor;
extern RGBA g_submenuarrowColor;
extern RGBA g_submenuarrowSelectedColor;
extern RGBA g_optionText;
extern RGBA g_selectedOptionText;
extern RGBA g_optionColor;
extern RGBA g_scrollerColor;
extern RGBA g_footerColor;
//Keypresses
extern bool g_selectPressed;
extern bool g_leftPressed;
extern bool g_rightPressed;
extern int m_delay;
extern int g_previousTick;
//Smooth scroll handling
extern float g_target, g_current, g_speed;
//Option handling
extern int g_maxVisOptions;
extern int g_optionCount;
extern int g_currentOption;
extern int g_menuLevel;
extern void(*g_currentMenu)();
extern void(*g_menuArray[1000])();
extern int g_optionArray[1000];
extern char const* g_currentSubmenu;
extern char const* g_submenuArray[1000];
extern char const* g_currentDescription;

char const* charKeyboard(char const* windowName, int maxInput, char const* defaultText);
char const* toString(int value);
char const* toStringFloat(float value);
char const* getText(int currentValue, int max);
char const* getTextFloat(float currentValue, float max);
float getTextWidth(char const* text, int32_t font, float scaleOverride);

void drawText(char const* text, RGBA color, Vector2 position, Vector2 size, int font);
void drawSprite(char const* dict, char const* texture, Vector2 pos, Vector2 size, float rotation, RGBA color);
void drawRect(RGBA color, Vector2 position, Vector2 size);

void updateScroller();
void forwardMenu(void(*menu)(), char const* submenu);
void backMenu();

void drawTitle(char const* title);
void drawSubtitle(char const* title);
bool drawOption(char const* option, char const* description);
bool drawSub(char const* option, char const* description, void(*sub)());
bool drawToggle(char const* option, char const* description, bool* toggle);
bool drawInt(char const* option, char const* description, int* inttochange, int min, int max, int step);
bool drawFloat(char const* option, char const* description, float* floattochange, float min, float max, float step);
void drawEnd();
void drawDescription();

void playFrontendSound(char const* soundName);
void inputHandler();