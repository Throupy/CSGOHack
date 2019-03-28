#include <Windows.h>
#include <iostream>
#include <cmath>
#include "MemMan.h"
#include "Globals.h"
#include "enums.h"
#include "csgo.hpp"

using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

CBhop::CBhop()
{

}

void CBhop::ToggleBhop()
{
	while (true)
	{
		val.flag = MemClass.readMem<BYTE>(val.localPlayer + m_fFlags);
		// Next I check if the player pressing space and is on the ground
		if (GetAsyncKeyState(VK_SPACE) && val.flag & (1 << 0))
			// Change flags offset - make the player jump
			MemClass.writeMem<uintptr_t>(val.gameModule + dwForceJump, 6);
	}
}