#pragma once

typedef struct scrNativeCallContext {
	uint64_t* m_res;
	uint32_t m_argCount;
	uint64_t* m_args;
	uint32_t m_dataCount;
	uint8_t m_data[0xC0];
} scrNativeCallContext;
typedef struct scrNativeRegistrationTable scrNativeRegistrationTable;
typedef void(*scrNativeHandler)(scrNativeCallContext*);
typedef uint64_t scrNativeHash;
typedef struct nativeCacheEntry {
	scrNativeHash m_hash;
	scrNativeHandler m_handler;
	struct nativeCacheEntry* m_next;
} nativeCacheEntry;
typedef struct nativeCtx {
	scrNativeCallContext m_base;
	uint64_t m_resStack[3];
	uint64_t m_argStack[64];
} nativeCtx;

extern nativeCtx g_context;
extern scrNativeHash g_hash;
void initInvoker();

/*
DECLSPEC_NOINLINE void nativeInit(scrNativeHash hash);
FORCEINLINE void nativePush(uint64_t value) {
	g_context.m_argStack[g_context.m_base.m_argCount++] = value;
}
DECLSPEC_NOINLINE void* nativeCall();
 * add this to MSVC only block
*/


__attribute__((noinline)) void nativeInit(scrNativeHash hash);
inline void nativePush(uint64_t value) {
	g_context.m_argStack[g_context.m_base.m_argCount++] = value;
}
__attribute__((noinline)) void* nativeCall();

typedef uint32_t Any;
typedef uint32_t Hash;
typedef int Entity;
typedef int Player;
typedef int Ped;
typedef int Vehicle;
typedef int Cam;
typedef int Pickup;
typedef int Object;
typedef int Blip;
typedef int Camera;
typedef int ScrHandle;

typedef struct RGB {
	int r, g, b;
} RGB;
typedef struct RGBA {
	int r, g, b, a;
} RGBA;
typedef struct Vector2 {
	float x;
	float y;
} Vector2;
typedef struct Vector3 {
	float x;
	char pad1[4];
	float y;
	char pad2[4];
	float z;
	char pad3[4];
} Vector3;
#define RGB(r, g, b) (RGB){ r, g, b }
#define RGBA(r, g, b, a) (RGBA){ r, g, b, a }
#define Vector2(x, y) (Vector2){ x, y }
#define Vector3(x, y, z) (Vector3){ x, y, z}
