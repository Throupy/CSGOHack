#include <Windows.h>
#include <iostream>
#include <cmath>
#include "MemMan.h"
#include "Globals.h"
#include "enums.h"
#include "csgo.hpp"
#include "Trigger.h"


using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

CTrigger::CTrigger()
{

}



bool CTrigger::checkIfScoped()
{
	return MemClass.readMem<bool>(val.localPlayer + m_bIsScoped);
}


void CTrigger::getWeapon()
{
	int weapon = MemClass.readMem<int>(val.localPlayer + m_hActiveWeapon);
	int weaponEntity = MemClass.readMem<int>(val.gameModule + dwEntityList + ((weapon & 0xFFF) - 1) * 0x10);
	if (weaponEntity != NULL)
		val.weaponID = MemClass.readMem<int>(weaponEntity + m_iItemDefinitionIndex);
}

void CTrigger::shoot()
{
	Sleep(val.tbDelay);
	// Set forcelmb to 5 to shoot
	MemClass.writeMem<int>(val.gameModule + dwForceAttack, 5);
	Sleep(20);
	// Stop the ting
	MemClass.writeMem<int>(val.gameModule + dwForceAttack, 4);
}

bool CTrigger::checkTBot()
{
	int crosshair = MemClass.readMem<int>(val.localPlayer + m_iCrosshairId);
	// Check if the thing in the crosshair is a player
	if (crosshair != 0 && crosshair < 64)
	{
		// Get entity in crosshair
		uintptr_t entity = MemClass.readMem<uintptr_t>(val.gameModule + dwEntityList + ((crosshair - 1) * 0x10));
		// Get health and team
		int eTeam = MemClass.readMem<int>(entity + m_iTeamNum);
		int eHealth = MemClass.readMem<int>(entity + m_iHealth);
		if (eTeam != val.myTeam && eHealth > 0)
		{
			// Get how far the enemy is
			getWeapon();
			if (val.weaponID == 40 || val.weaponID == 9)
				return checkIfScoped();
			return true;

		}
		else
			return false;
	}
	else
		return false;
}

void CTrigger::handleTBot()
{
	if (checkTBot())
		shoot();
}



void CTrigger::ToggleTrigger()
{
	bool canTBot = false;
	bool keyHeld = false;
	while (true)
	{
		if (GetAsyncKeyState(VK_XBUTTON1) == KeyDOWN && !keyHeld)
		{
			keyHeld = true;
			canTBot = true;
		}
		if (GetAsyncKeyState(VK_XBUTTON1) == KeyUP && keyHeld)
		{
			keyHeld = false;
			canTBot = false;
		}

		if (canTBot)
			handleTBot();

		Sleep(1);
	}
}
