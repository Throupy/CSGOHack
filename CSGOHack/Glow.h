#pragma once
#include "Globals.h"

class CGlow {
public:
	CGlow();
	void ToggleGlow();
	GlowStruct SetGlowColor(GlowStruct glow, uintptr_t entity);
	void SetTeamGlow(uintptr_t entity, int glowIndex);
	void SetEnemyGlow(uintptr_t entity, int glowIndex);
	void HandleGlow();
};