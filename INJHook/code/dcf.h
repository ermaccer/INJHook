#pragma once
#include "MKCharacter.h"
#define GFG_GAME_INFO  0x33FC6F4 

#define INJHOOK_VERSION "0.2"

enum  PLAYER_NUM
{
	INVALID_PLAYER_NUM = -1,
	PLAYER1,
	PLAYER2,
	PLAYER3,
	PLAYER4,
	MAX_PLAYERS,
	CPU_PLAYER,
	NOT_CPU_PLAYER,
	BACKGROUND_PLAYER
};

struct FVector
{
	float X;
	float Y;
	float Z;
};


struct FRotator {
	int Pitch;
	int Yaw;
	int Roll;
};


int				  GetInfo(PLAYER_NUM plr);
MKCharacter*	  GetObj(PLAYER_NUM plr);


void 				ResetStageInteractables();
void  SetCharacterMeter(int obj, float meter);


namespace INJHooks {
	void  HookProcessStuff();

	void  SetupFight();

}