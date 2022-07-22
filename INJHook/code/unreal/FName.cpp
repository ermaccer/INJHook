#include "FName.h"
#include "..\mk10utils.h"

FName::FName(const char* Name, EFindName FindType, int formal)
{
	((void(__thiscall*)(FName*, const char*, EFindName, int))_addr(0x47AB90))(this, Name, FindType, formal);
}

int FName::GetIndex()
{
	return Index;
}
