#include "mkcamera.h"
#include "mk10utils.h"
#include "dcfmenu.h"
#include <iostream>
#include "helper/eMath.h"

MKCamera* TheCamera;

void MKCamera::SetPosition(FVector * pos)
{
	TheCamera = this;
	camPos = *pos;
	((void(__thiscall*)(MKCamera*, FVector*))_addr(0x8C1770))(this, pos);
}

void MKCamera::SetRotation(FRotator * rot)
{
	TheCamera = this;
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
	
	float oneTime = 0.0f;
	float oneTimeX = 0.0f;
	if (!TheMenu->m_bYObtained)
	{
		oneTime = pos->Y;
		oneTimeX = pos->X;
		TheMenu->m_bYObtained = true;
	}
	if (TheMenu->m_bCustomCameras)
	{
		if (GetObj(PLAYER1) && GetObj(PLAYER2))
		{
			FVector eyePos[2];
			FVector middle;
			switch (TheMenu->m_nCurrentCustomCamera)
			{
			case CAMERA_HEAD_TRACKING:
				USkeletalMeshComponent* skeleton;
				if (TheMenu->m_bUsePlayerTwoAsTracker)
					skeleton = GetObj(PLAYER2)->GetSkeleton();
				else
					skeleton = GetObj(PLAYER1)->GetSkeleton();

				skeleton->GetBoneLocation(&eyePos[0], "LeftEye");
				skeleton->GetBoneLocation(&eyePos[1], "RightEye");
				middle = (eyePos[0] + eyePos[1]) / 2.0;


				pos->X = middle.X + TheMenu->m_fAdjustCustomHeadCameraX;
				pos->Y = middle.Y + TheMenu->m_fAdjustCustomHeadCameraY2;
				pos->Z = middle.Z + TheMenu->m_fAdjustCustomHeadCameraZ;


				TheMenu->camPos = *pos;

				break;
			}
		}
		SetPosition(pos);
	}
	else
	{
		if (!TheMenu->m_bCustomCameraPos)
		{
			TheMenu->camPos = *pos;
			SetPosition(pos);
		}
		else
			SetPosition(&TheMenu->camPos);
	}	
}

void MKCamera::HookedSetRotation(FRotator * rot)
{
	if (TheMenu->m_bCustomCameras)
	{
		if (GetObj(PLAYER1) && GetObj(PLAYER2))
		{
			FVector p1, p2;
			FRotator headRot;
			switch (TheMenu->m_nCurrentCustomCamera)
			{
			case CAMERA_HEAD_TRACKING:
				USkeletalMeshComponent* skeleton;
				if (TheMenu->m_bUsePlayerTwoAsTracker)
					skeleton = GetObj(PLAYER2)->GetSkeleton();
				else
					skeleton = GetObj(PLAYER1)->GetSkeleton();
				skeleton->GetBoneRotation(&headRot, "Head");

				rot->Pitch = headRot.Yaw / 10 + TheMenu->m_fAdjustCustomHeadCameraY;
				if (TheMenu->m_bStaticHead)
					rot->Yaw = 16000 + headRot.Pitch / 1000;
				else rot->Yaw = headRot.Pitch + 1000;
				rot->Roll = abs(headRot.Roll / 100);
				TheMenu->camRot = *rot;

				if (GetObj(PLAYER1))
					GetCharacterPosition(PLAYER1, &p1);
				if (GetObj(PLAYER2))
					GetCharacterPosition(PLAYER2, &p2);

				if (p2.Y < p1.Y && !TheMenu->m_bDontFlipCamera)
				{
					rot->Yaw *= -1;
				}
				else if (eMath::areVecsEqual(p1, p2) && !TheMenu->m_bDontAdjust) // sometimes happens in mk9
				{
					rot->Yaw *= -1;
				}
				else if (fabs(p1.Y - p2.Y) < 0.1f && !TheMenu->m_bDontAdjust)
				{
					rot->Yaw *= -1;
				}

				TheMenu->camRot = *rot;
				break;
			}
		}

		SetRotation(rot);
	}
	else
	{
		if (!TheMenu->m_bCustomCameraRot)
		{
			TheMenu->camRot = *rot;
			SetRotation(rot);
		}
		else
			SetRotation(&TheMenu->camRot);
	}
}

FMatrix MKCamera::GetMatrix()
{
	FRotator rot = camRot;
	FMatrix mat(&rot);
	return mat;
}

