#include "GameInfo.h"
#include "dcf.h"
#include "mk10utils.h"
#include "dcfmenu.h"
#include <iostream>

FGGameInfo * GetGameInfo()
{
	return *(FGGameInfo**)_addr(GFG_GAME_INFO);
}

MKScript* GetScript(const char* name)
{
	int package = ((int(__cdecl*)(int, const char*))_addr(0x4DB600))(0,"SystemArt");
	if (package)
	{
		MKScript* script = ((MKScript * (__cdecl*)(int, const char*, int))_addr(0xB389B0))(package, name, 1);
		return script;

	}
	return nullptr;
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

MKScript* FGGameInfo::GetFightScript()
{
	return ((MKScript*(__thiscall*)(FGGameInfo*))_addr(0xD66DF0))(this);
}

MKScript* FGGameInfo::GetGenericScript()
{
	return ((MKScript * (__thiscall*)(FGGameInfo*, int))_addr(0xD67310))(this, 1);
}

void FGGameInfo::ResetStageInteractables()
{
	int bgnd_info = *(int*)(this + 36);
	((void(__thiscall*)(int))_addr(0xD22560))(bgnd_info);
}


int MKScript::GetFunctionID(char* name)
{
	return ((int(__thiscall*)(MKScript*, char*, int))_addr(0xA7D4A0))(this, name, 0);
}
