#include <Windows.h>
#include <iostream>
#include <cmath>
#include "MemMan.h"
#include "Globals.h"
#include "enums.h"
#include "csgo.hpp"
#include "Antiflash.h"


using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

CAntiflash::CAntiflash()
{

}

void CAntiflash::ToggleAntiflash()
{
	int flashDur = 0;
	while (true)
	{
		flashDur = MemClass.readMem<int>(val.localPlayer + m_flFlashDuration);
		if (flashDur > 0)
			MemClass.writeMem<int>(val.localPlayer + m_flFlashDuration, 0);
	}
}