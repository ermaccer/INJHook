#pragma once
#include "MKCharacter.h"
#include "unreal/FVector.h"
#include "unreal/FRotator.h"
#include "GameInfo.h"
#include "PlayerInfo.h"


#define GFG_GAME_INFO  0x33FC6F4 

#define INJHOOK_VERSION "0.3.3"


PlayerInfo*		  GetInfo(PLAYER_NUM plr);
MKCharacter*	  GetObj(PLAYER_NUM plr);


void 				ResetStageInteractables();
void  SetCharacterScale(PLAYER_NUM plr, FVector* scale);
void  SetCharacterSpeed(PLAYER_NUM plr, float speed);

void  GetCharacterPosition(PLAYER_NUM plr, FVector* pos);

void SetGameSpeed(float speed);


namespace INJHooks {
	void  HookProcessStuff();

	void  SetupFight();

}