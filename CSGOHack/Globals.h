#pragma once

#include "BHop.h"

#define KeyDOWN -32768
#define KeyUP 0

struct values {
	uintptr_t localPlayer;
	uintptr_t process;
	uintptr_t gameModule;
	uintptr_t glowObject;
	BYTE flag;
	int myTeam;
	int tbDelay;
	int weaponID;
};

struct vector {
	float x, y, z;
};

struct GlowStruct
{
	BYTE base[4];
	float red;
	float green;
	float blue;
	float alpha;
	BYTE buffer[16];
	bool renderWhenOccluded;
	bool renderWhenUnOccluded;
	bool fullBloom;
	BYTE buffer1[5];
	int glowStyle;
};

extern MemMan MemClass;
extern struct values val;
extern MemMan MemClass;
