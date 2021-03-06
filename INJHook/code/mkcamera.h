#pragma once
#include "dcf.h"
#include "unreal/FMatrix.h"
// generic layer for other plugins too
class MKCamera {
private:
	char pad[0x320];
	FVector  camPos;
	FRotator camRot;
	float	 camFov;
public:
	void SetPosition(FVector* pos);
	void SetRotation(FRotator* rot);
	void SetFOV(float FOV);
	float GetFOV();

	void HookedSetPosition(FVector* pos);
	void HookedSetRotation(FRotator* rot);

	FMatrix GetMatrix();
};

extern MKCamera* TheCamera;