#pragma once
#include <Windows.h>
#include "GoldenKeys.h"

class Game
{
private:
	DWORD BaseAddress;

public:
	DWORD GetBaseAddress();

	void SetRifleAmmo(int Ammo);

	float GetXP();
	void SetXP(float XP);

	float GetHealth();
	void SetHealth(float Health);

	DWORD GetXPAddy();
	DWORD GetHealthAddy();

	CGoldenKeys* GoldenKeys = new CGoldenKeys();
};

extern Game* g_Game;