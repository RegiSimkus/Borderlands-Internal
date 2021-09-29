#pragma once
#include <Windows.h>


// 0x6C tends to be to get the value of a variable
// 0x16949D8 + 0x2C might be the localplayer?

namespace Offsets
{
	namespace XP
	{
		static uintptr_t Base = 0x16949D8;
		static uintptr_t Offset1 = 0x2C;
		static uintptr_t Offset2 = 0x1A8;
		static uintptr_t Offset3 = 0x6C;
	}

	namespace Health
	{
		static uintptr_t Base = 0x16949D8;
		static uintptr_t Offset1 = 0x2C;
		static uintptr_t Offset2 = 0x1B4;
		static uintptr_t Offset3 = 0x6C;
	}

	namespace Weapon
	{
		static uintptr_t MaxAmmo = 0x58;
		static uintptr_t AmmoHeld = 0x6C;
	}

	namespace Ammo
	{
		namespace SMG
		{
			static uintptr_t Base = 0x1649050;
			static uintptr_t Offset = 0x6C;
			static uintptr_t MaxAmmo = 0x58;
		}

		namespace Rifle
		{
			static uintptr_t Base = 0x1652654;
			static uintptr_t Offset = 0x6C;
			static uintptr_t MaxAmmo = 0x58;
		}
	}

	namespace GoldenKeys
	{
		static uintptr_t Base = 0x015DA980;
		static uintptr_t Offset = 0xE74;
	}
}