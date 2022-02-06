#include "..\pch.h"
#include "mk10utils.h"

int GetMKXEntryPoint()
{
	static __int64 addr = reinterpret_cast<__int64>(GetModuleHandle(nullptr));
	return addr;
}

int _addr(int addr)
{
	return GetMKXEntryPoint() - 0x400000 + addr;
}
