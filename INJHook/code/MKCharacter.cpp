#include "MKCharacter.h"
#include "mk10utils.h"
#include <iostream>
#include <Windows.h>
void MKCharacter::SetLife(float life)
{
	((void(__thiscall*)(MKCharacter*, float))_addr(0xD29C00))(this, life);
}

void MKCharacter::SetMeter(float value)
{
	((void(__thiscall*)(MKCharacter*, float))_addr(0xDBE230))(this, value);
}


void MKCharacter::ExecuteScript(MKScript* script, int function)
{
	((void(__thiscall*)(int, MKScript*, int))_addr(0xA9A4B0))(*(int*)((int)this + 0x2D8), script, function);
}
