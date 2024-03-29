#include "dcf.h"
#include <iostream>
#include <Windows.h>
#include "dcfmenu.h"
#include "eNotifManager.h"
#include "eSettingsManager.h"
#include "mk10utils.h"
#include "GameInfo.h"

PlayerInfo* GetInfo(PLAYER_NUM plr)
{
	return GetGameInfo()->GetInfo(plr);
}

MKCharacter* GetObj(PLAYER_NUM plr)
{
	return ((MKCharacter*(__thiscall*)(int, int))_addr(0xDAD780))((int)GetInfo(plr), 1);
}

void ResetStageInteractables()
{
	GetGameInfo()->ResetStageInteractables();
}

void SetCharacterScale(PLAYER_NUM plr, FVector* scale)
{
	int obj = (int)GetObj(plr);
	int actor = *(int*)(obj + 16);
	*(FVector*)(actor + 0x114) = *scale;
}

void SetCharacterSpeed(PLAYER_NUM plr, float speed)
{
	int obj = (int)GetObj(plr);
	int actor = *(int*)(obj + 16);
	*(float*)(actor + 0x8C) = speed;
}

void GetCharacterPosition(PLAYER_NUM plr, FVector* pos)
{
	int obj = (int)GetObj(plr);
	int actor = *(int*)(obj + 16);
	FVector location = *(FVector*)(actor + 0xE4);
	*pos = location;
}

void SetGameSpeed(float speed)
{
	GetGameInfo()->SetGameSpeed(speed);
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

	if (TheMenu->m_bSlowMotion)
	{
		if (GetGameInfo()) GetGameInfo()->SetGameSpeed(TheMenu->m_fSlowMotionSpeed);
	}
	if (TheMenu->m_bInfiniteMeterP1)
	{
		if (GetObj(PLAYER1))
			GetInfo(PLAYER1)->SetMeter(1.0f);

	}
	if (TheMenu->m_bInfiniteMeterP2)
	{
		if (GetObj(PLAYER2))
			GetInfo(PLAYER2)->SetMeter(1.0f);
	}
	if (TheMenu->m_bZeroMeterP1)
	{
		if (GetObj(PLAYER1))
			GetInfo(PLAYER1)->SetMeter(0.0f);
	}
	if (TheMenu->m_bZeroMeterP2)
	{
		if (GetObj(PLAYER2))
			GetInfo(PLAYER2)->SetMeter(0.0f);
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

	if (TheMenu->m_bChangePlayerScale)
	{
		if (GetObj(PLAYER1))
			SetCharacterScale(PLAYER1, &TheMenu->m_vP1Scale);
		if (GetObj(PLAYER2))
			SetCharacterScale(PLAYER2, &TheMenu->m_vP2Scale);
	}
	if (TheMenu->m_bChangePlayerSpeed)
	{
		if (GetObj(PLAYER1))
			SetCharacterSpeed(PLAYER1, TheMenu->m_fP1Speed);
		if (GetObj(PLAYER2))
			SetCharacterSpeed(PLAYER2, TheMenu->m_fP2Speed);
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
