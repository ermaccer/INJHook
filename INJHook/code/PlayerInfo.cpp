#include "PlayerInfo.h"
#include "mk10utils.h"
#include "GameInfo.h"
#include "dcfmenu.h"

void PlayerInfo::SetCharacter(char* name)
{
	((void(__thiscall*)(PlayerInfo*, char*))_addr(0xDC3E90))(this, name);
}

void PlayerInfo::SetMeter(float value)
{
	((void(__thiscall*)(PlayerInfo*, float))_addr(0xDBE230))(this, value);
}

void PlayerInfo::SetCharacterHooked(char* name)
{
	if (this == GetInfo(PLAYER1) && TheMenu->m_bPlayer1Modifier)
		name = TheMenu->szPlayer1ModifierCharacter;
	if (this == GetInfo(PLAYER2) && TheMenu->m_bPlayer2Modifier)
		name = TheMenu->szPlayer2ModifierCharacter;

	SetCharacter(name);
}
