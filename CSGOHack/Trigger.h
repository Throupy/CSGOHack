#pragma once

class CTrigger {
public:
	CTrigger();
	void ToggleTrigger();
	bool checkIfScoped();
	void getWeapon();
	void shoot();
	bool checkTBot();
	void handleTBot();
};