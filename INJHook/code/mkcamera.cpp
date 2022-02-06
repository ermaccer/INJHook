#include "mkcamera.h"
#include "mk10utils.h"
#include "dcfmenu.h"
#include <iostream>

void MKCamera::SetPosition(FVector * pos)
{
	camPos = *pos;
	((void(__thiscall*)(MKCamera*, FVector*))_addr(0x8C1770))(this, pos);
}

void MKCamera::SetRotation(FRotator * rot)
{
	camRot = *rot;
	((void(__thiscall*)(MKCamera*, FRotator*))_addr(0x8C17A0))(this, rot);
}

void MKCamera::SetFOV(float FOV)
{
	camFov = FOV;
}

float MKCamera::GetFOV()
{
	return camFov;
}

void MKCamera::HookedSetPosition(FVector * pos)
{
	if (TheMenu->m_bCustomCameraFOV)
		SetFOV(TheMenu->camFov);
	else
		TheMenu->camFov = GetFOV();
	
	if (!TheMenu->m_bCustomCameraPos)
	{
		TheMenu->camPos = *pos;
		SetPosition(pos);
	}
	else
		SetPosition(&TheMenu->camPos);
	
}

void MKCamera::HookedSetRotation(FRotator * rot)
{
	if (!TheMenu->m_bCustomCameraRot)
	{
		TheMenu->camRot = *rot;
		SetRotation(rot);
	}
	else
		SetRotation(&TheMenu->camRot);
}

