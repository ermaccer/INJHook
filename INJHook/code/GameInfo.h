#pragma once

class FGGameInfo {
public:
	void SetStageAndCharacters(char* stage, char* p1, char* p2);
	void SetStageAndCharactersHooked(char* stage, char* p1, char* p2);

	void ResetStageInteractables();
};

FGGameInfo* GetGameInfo();