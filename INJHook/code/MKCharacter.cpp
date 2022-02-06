#include "MKCharacter.h"
#include "mk10utils.h"

void MKCharacter::SetLife(float life)
{
	((void(__thiscall*)(MKCharacter*, float))_addr(0xD29C00))(this, life);
}

void MKCharacter::SetMeter(float value)
{
	((void(__thiscall*)(MKCharacter*, float))_addr(0xDBE230))(this, value);
}
