#include "pch.h"
#include <Windows.h>
#include "offsets.h"
#include "Borderlands.h"

DWORD Game::GetBaseAddress()
{
	if (!BaseAddress)
	{
		BaseAddress = (DWORD)GetModuleHandleA("Borderlands2.exe");
	}
	return BaseAddress;
}

void Game::SetRifleAmmo(int Ammo)
{
	*(float*)((*(uintptr_t*)(GetBaseAddress() + Offsets::Ammo::Rifle::Base)) + Offsets::Ammo::Rifle::Offset) = (float)Ammo;
}

DWORD Game::GetXPAddy()
{
	return (*(DWORD*)(*(DWORD*)(*(DWORD*)(GetBaseAddress() + Offsets::XP::Base) + Offsets::XP::Offset1) + Offsets::XP::Offset2) + Offsets::XP::Offset3);
}

DWORD Game::GetHealthAddy()
{
	return (*(DWORD*)(*(DWORD*)(*(DWORD*)(GetBaseAddress() + Offsets::Health::Base) + Offsets::Health::Offset1) + Offsets::Health::Offset2) + Offsets::Health::Offset3);
}

void Game::SetHealth(float Health)
{
	*(float*)GetHealthAddy() = Health;
}

float Game::GetHealth()
{
	return *(float*)GetHealthAddy();
}

void Game::SetXP(float XP)
{
	*(float*)GetXPAddy() = XP;
}

float Game::GetXP()
{
	return *(float*)GetXPAddy();
}

