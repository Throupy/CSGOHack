#include <Windows.h>
#include <iostream>
#include <cmath>
#include "MemMan.h"
#include "Globals.h"
#include "enums.h"
#include "csgo.hpp"
#include "Glow.h"


using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

CGlow::CGlow()
{

}

void CGlow::ToggleGlow()
{
	while (true)
	{
		if (GetKeyState(VK_NUMPAD0) & 1)
			HandleGlow();
		Sleep(1);
	}
}

GlowStruct CGlow::SetGlowColor(GlowStruct Glow, uintptr_t entity)
{
	bool defusing = MemClass.readMem<bool>(entity + m_bIsDefusing);
	if (defusing)
	{
		Glow.red = 1.0f;
		Glow.green = 1.0f;
		Glow.blue = 1.0f;
	}
	else
	{
		int health = MemClass.readMem<int>(entity + m_iHealth);
		Glow.red = health * -0.01 + 1;
		Glow.green = health * 0.01;
	}
	Glow.alpha = 1.0f;
	Glow.renderWhenOccluded = true;
	Glow.renderWhenUnOccluded = false;
	return Glow;
}

void CGlow::SetTeamGlow(uintptr_t entity, int glowIndex)
{
	GlowStruct TGlow;
	TGlow = MemClass.readMem<GlowStruct>(val.glowObject + (glowIndex * 0x38));

	TGlow.blue = 1.0f;
	TGlow.alpha = 1.0f;
	TGlow.renderWhenOccluded = true;
	TGlow.renderWhenUnOccluded = false;
	MemClass.writeMem<GlowStruct>(val.glowObject + (glowIndex * 0x38), TGlow);
}

void CGlow::SetEnemyGlow(uintptr_t entity, int glowIndex)
{
	GlowStruct EGlow;
	EGlow = MemClass.readMem<GlowStruct>(val.glowObject + (glowIndex * 0x38));
	EGlow = SetGlowColor(EGlow, entity);
	MemClass.writeMem<GlowStruct>(val.glowObject + (glowIndex * 0x38), EGlow);
}

void CGlow::HandleGlow()
{
	val.glowObject = MemClass.readMem<uintptr_t>(val.gameModule + dwGlowObjectManager);
	int myTeam = MemClass.readMem<int>(val.localPlayer + m_iTeamNum);

	for (short int i = 0; i < 64; i++)
	{
		uintptr_t entity = MemClass.readMem<uintptr_t>(val.gameModule + dwEntityList + i * 0x10);
		if (entity != NULL)
		{
			int glowIndx = MemClass.readMem<int>(entity + m_iGlowIndex);
			int entityTeam = MemClass.readMem<int>(entity + m_iTeamNum);

			if (myTeam == entityTeam)
				SetTeamGlow(entity, glowIndx);
			else
				SetEnemyGlow(entity, glowIndx);
		}
	}
}