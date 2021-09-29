#include "GoldenKeys.h"
#include "Borderlands.h"
#include "offsets.h"
#include <Windows.h>
#include "math.h"


DWORD CGoldenKeys::IntToKeys(int Amount)
{
	return (DWORD)(16777216 * Amount);
}

int CGoldenKeys::KeysToInt(DWORD Value)
{
	return (int)(Value / 16777216);
}

int CGoldenKeys::GetKeys()
{
	return KeysToInt(*(int*)(*(uintptr_t*)(g_Game->GetBaseAddress() + Offsets::GoldenKeys::Base) + Offsets::GoldenKeys::Offset));
}

void CGoldenKeys::SetKeys(int Keys) // max is 250
{
	*(int*)(*(uintptr_t*)(g_Game->GetBaseAddress() + Offsets::GoldenKeys::Base) + Offsets::GoldenKeys::Offset) = IntToKeys(Math::Clamp<int>(Keys, 0, 250));
}

void CGoldenKeys::AddKeys(int Keys)
{
	*(int*)(*(uintptr_t*)(g_Game->GetBaseAddress() + Offsets::GoldenKeys::Base) + Offsets::GoldenKeys::Offset) = IntToKeys(Math::Clamp<int>(GetKeys() + Keys, 0, 250));
}
