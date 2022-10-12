#pragma once
#include "PlayerInfo.h"
#include "mk10utils.h"

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


class MKScript {
public:
	int GetFunctionID(char* name);
};

class FGGameInfo {
public:
	void SetStage(const char* stage);
	void SetStageHooked(const char* stage);

	void SetStageAndCharacters(char* stage, char* p1, char* p2);
	void SetStageAndCharactersHooked(char* stage, char* p1, char* p2);

	MKScript* GetFightScript();
	MKScript* GetGenericScript();
	void ResetStageInteractables();

	PlayerInfo* GetInfo(PLAYER_NUM plr);

	void SetGameSpeed(float value);
};

FGGameInfo* GetGameInfo();

MKScript* GetScript(const char* name);