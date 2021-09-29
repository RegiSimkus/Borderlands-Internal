#pragma once
#include <Windows.h>

class CGoldenKeys
{
public:
	 DWORD IntToKeys(int Value); // Turns the encrypted value into a real number
	 int KeysToInt(DWORD Amount); // Turns a real number into an encrypted value for writing

//public:
	int GetKeys();
	void SetKeys(int Keys);
	void AddKeys(int Keys);
};