#include "GameInfo.h"
#include "dcf.h"
#include "mk10utils.h"
#include "dcfmenu.h"
#include <iostream>

FGGameInfo * GetGameInfo()
{
	return *(FGGameInfo**)_addr(GFG_GAME_INFO);
}

void FGGameInfo::SetStageAndCharacters(char * stage, char * p1, char * p2)
{
	((void(__thiscall*)(FGGameInfo*, char*, char*, char*))_addr(0xD89860))(this, stage,p1,p2);
}

void FGGameInfo::SetStageAndCharactersHooked(char * stage, char * p1, char * p2)
{
	if (TheMenu->m_bPlayer1Modifier)
		p1 = TheMenu->szPlayer1ModifierCharacter;

	if (TheMenu->m_bPlayer2Modifier)
		p2 = TheMenu->szPlayer2ModifierCharacter;

	if (TheMenu->m_bStageModifier)
		stage = TheMenu->szStageModifierStage;

	SetStageAndCharacters(stage, p1, p2);
}

void FGGameInfo::ResetStageInteractables()
{
	int bgnd_info = *(int*)(this + 36);
	((void(__thiscall*)(int))_addr(0xD22560))(bgnd_info);
}
