#include "dcf.h"
#include <iostream>
#include <Windows.h>
#include "dcfmenu.h"
#include "eNotifManager.h"
#include "eSettingsManager.h"
#include "mk10utils.h"
#include "GameInfo.h"

int GetInfo(PLAYER_NUM plr)
{
	int gameinfo = *(int*)(_addr(GFG_GAME_INFO));
	return ((int(__thiscall*)(int, PLAYER_NUM))_addr(0xD664C0))(gameinfo, plr);
}

MKCharacter* GetObj(PLAYER_NUM plr)
{
	return ((MKCharacter*(__thiscall*)(int, int))_addr(0xDAD780))(GetInfo(plr), 1);
}

void ResetStageInteractables()
{
	GetGameInfo()->ResetStageInteractables();
}

void SetCharacterMeter(int obj, float meter)
{
	((void(__thiscall*)(int, float))_addr(0xDBE230))(obj, meter);
}

void SetCharacter(PLAYER_NUM plr, int unk, char * name)
{
	((void(__cdecl*)(PLAYER_NUM, int, char*))0x8141A0)(plr, unk, name);
}

void SetStage(const char * stage)
{
	((void(__cdecl*)(const char*))0x811DD0)(stage);
}


void INJHooks::HookProcessStuff()
{
	Notifications->Update();
	TheMenu->Process();


	if (TheMenu->m_bInfiniteMeterP1)
	{
		if (GetObj(PLAYER1))
			SetCharacterMeter(GetInfo(PLAYER1), 1.0f);

	}
	if (TheMenu->m_bInfiniteMeterP2)
	{
		if (GetObj(PLAYER2))
			SetCharacterMeter(GetInfo(PLAYER2), 1.0f);
	}
	if (TheMenu->m_bZeroMeterP1)
	{
		if (GetObj(PLAYER1))
			SetCharacterMeter(GetInfo(PLAYER1), 0.0f);
	}
	if (TheMenu->m_bZeroMeterP2)
	{
		if (GetObj(PLAYER2))
			SetCharacterMeter(GetInfo(PLAYER2), 0.0f);
	}
	if (TheMenu->m_bInfiniteHealthP1)
	{
		if (GetObj(PLAYER1))
			GetObj(PLAYER1)->SetLife(1.0f);
	}
	if (TheMenu->m_bInfiniteHealthP2)
	{
		if (GetObj(PLAYER2))
			GetObj(PLAYER2)->SetLife(1.0f);
	}
	if (TheMenu->m_bNoHealthP1)
	{
		if (GetObj(PLAYER1))
			GetObj(PLAYER1)->SetLife(0.0f);
	}
	if (TheMenu->m_bNoHealthP2)
	{
		if (GetObj(PLAYER2))
			GetObj(PLAYER2)->SetLife(0.0);
	}
}

void INJHooks::SetupFight()
{
	printf("INJHook::Info() | Starting a new fight!\n");

	TheMenu->m_bYObtained = false;

	if (TheMenu->m_bStageModifier)
		SetStage(TheMenu->szStageModifierStage);
	if (TheMenu->m_bPlayer1Modifier)
		SetCharacter(PLAYER1, 0, TheMenu->szPlayer1ModifierCharacter);
	if (TheMenu->m_bPlayer2Modifier)
		SetCharacter(PLAYER2, 0, TheMenu->szPlayer2ModifierCharacter);



	printf("INJHook::Info() | %s VS %s\n",0,0);
}
