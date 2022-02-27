#pragma once
#include "GameInfo.h"


class MKCharacter {
public:
	void SetLife(float life);
	void SetMeter(float value);

	void ExecuteScript(MKScript* script, int function);

};