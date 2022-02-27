#pragma once

class MKScript {
public:
	int GetFunctionID(char* name);
};

class FGGameInfo {
public:
	void SetStageAndCharacters(char* stage, char* p1, char* p2);
	void SetStageAndCharactersHooked(char* stage, char* p1, char* p2);

	MKScript* GetFightScript();
	MKScript* GetGenericScript();
	void ResetStageInteractables();
};

FGGameInfo* GetGameInfo();

MKScript* GetScript(const char* name);