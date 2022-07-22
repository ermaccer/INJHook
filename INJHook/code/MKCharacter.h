#pragma once
#include "GameInfo.h"
#include "unreal/SkeletalMeshComponent.h"


class MKCharacter {
public:
	void SetLife(float life);
	void SetMeter(float value);

	void ExecuteScript(MKScript* script, int function);
	USkeletalMeshComponent* GetSkeleton();

};