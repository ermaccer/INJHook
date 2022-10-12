// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>
#include "code/dcf.h"
#include "MemoryMgr.h"
#include "code/dcfmenu.h"
#include "code/eNotifManager.h"
#include "code/mkcamera.h"
#include "code/eSettingsManager.h"
#include "code/mk10utils.h"
#include "code/GameInfo.h"
#include "eDirectX9Hook.h"
#include "code/helper/eGamepadManager.h"
#include "code/helper/eMouse.h"

using namespace Memory::VP;


void WINAPI HookUpdate()
{
	while (true)
	{
		INJHooks::HookProcessStuff();
		eMouse::UpdateMouse();
		Sleep(1);
	}
}

void OnInitializeHook()
{
	if (SettingsMgr->bEnableConsoleWindow)
	{
		AllocConsole();
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
	}

	printf("INJHook::OnInitializeHook() | Begin!\n");
	TheMenu->Initialize();
	Notifications->Init();

	InjectHook(_addr(0xDBC776), &FGGameInfo::SetStageAndCharactersHooked);
	InjectHook(_addr(0xDE824B), &FGGameInfo::SetStageAndCharactersHooked);
	InjectHook(_addr(0xE56625), &FGGameInfo::SetStageAndCharactersHooked);

	InjectHook(_addr(0xD8983E), &PlayerInfo::SetCharacterHooked);
	InjectHook(_addr(0xD89A31), &PlayerInfo::SetCharacterHooked);
	InjectHook(_addr(0xD89A86), &PlayerInfo::SetCharacterHooked);
	InjectHook(_addr(0xE6519D), &PlayerInfo::SetCharacterHooked);

	InjectHook(_addr(0xD899E8), &FGGameInfo::SetStageHooked);
	InjectHook(_addr(0xE5649D), &FGGameInfo::SetStageHooked);

	Nop(_addr(0x7BAC3C), 24);

	InjectHook(_addr(0x7BAC62), &MKCamera::HookedSetPosition);
	InjectHook(_addr(0x7BAC6D), &MKCamera::HookedSetRotation);

	if (SettingsMgr->bEnableGamepadSupport)
		InjectHook(_addr(0xF7548E), XInputGetState_Hook, PATCH_JUMP);
}

bool CheckGame()
{
	char* gameName = (char*)(_addr(0x17CCA24));

	if (strcmp(gameName, "Injustice") == 0)
	{
		return true;
	}
	else
	{
		MessageBoxA(0, "Invalid game version!\nINJHook only supports latest Steam executable.\n\n"
			"If you still cannot run the plugin and made sure that the game is updated, INJHook needs to be updated.", 0, MB_ICONINFORMATION);
		return false;
	}
}


BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		if (CheckGame())
		{
			SettingsMgr->Init();
			OnInitializeHook();
			DisableThreadLibraryCalls(hMod);
			CreateThread(nullptr, 0, DirectXHookThread, hMod, 0, nullptr);
			CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HookUpdate, hMod, 0, nullptr);
		}
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}




