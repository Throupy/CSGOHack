#include <Windows.h>
#include <iostream>
#include <cmath>
#include <thread>
#include "MemMan.h"
#include "enums.h"
#include "csgo.hpp"
#include "BHop.h"
#include "Trigger.h"
#include "Antiflash.h"
#include "Glow.h"
#include "Globals.h"

using namespace hazedumper::netvars;
using namespace hazedumper::signatures;
using namespace std;

void InitializeCheat()
{
	val.process = MemClass.getProcess(L"csgo.exe");
	val.gameModule = MemClass.getModule(val.process, L"client_panorama.dll");
	val.localPlayer = MemClass.readMem<uintptr_t>(val.gameModule + dwLocalPlayer);
}

void toggleCheat(thread threadToStart)
{

}

int main()
{
	InitializeCheat();
	CBhop bhop = CBhop();
	CTrigger trigger = CTrigger();
	CAntiflash antiflash = CAntiflash();
	CGlow glow = CGlow();

	thread tBhop(&CBhop::ToggleBhop, &bhop);
	thread tTrigger(&CTrigger::ToggleTrigger, &trigger);
	thread tAntiflash(&CAntiflash::ToggleAntiflash, &antiflash);
	thread tGlow(&CGlow::ToggleGlow, &glow);

	while (true)
	{
		Sleep(5);
	}
}
