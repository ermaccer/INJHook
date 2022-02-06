#include "dcfmenu.h"
#include <iostream>
#include "..\imgui\imgui.h"
#include "eNotifManager.h"
#include "eSettingsManager.h"
#include <Windows.h>
#include "..\eDirectX9Hook.h"

const char* szCharacters[] = {
	"NPC_AA_Inmates",
	"NPC_AA_KillerCroc",
	"NPC_AA_Penguin",
	"NPC_AA_Riddler",
	"NPC_AA_Scarecrow",
	"NPC_AA_TwoFace",
	"NPC_Amazonian",
	"NPC_Cat",
	"NPC_Dummy",
	"NPC_HOJ_Giganta",
	"NPC_LX_LexExoSuit",
	"NPC_MaleMedium",
	"NPC_MET_Atrocitus",
	"NPC_MET_Kilowog",
	"NPC_MilitaryPolice",
	"NPC_Pedestrians_Male",
	"NPC_RV_Trigon",
	"NPC_SC_Atom",
	"NPC_SC_JokerClan",
	"NPC_SIP_Inmates",
	"NPC_SIP_MechGuard",
	"CHAR_BossSuperman",
	"CHAR_Aquaman",
	"CHAR_Aquaman_A",
	"CHAR_Aquaman_V",
	"CHAR_Ares",
	"CHAR_Ares_V",
	"CHAR_Bane",
	"CHAR_Bane_A",
	"CHAR_Bane_V",
	"CHAR_Batman",
	"CHAR_Batman_A",
	"CHAR_Batman_C",
	"CHAR_Batman_D",
	"CHAR_Batman_E",
	"CHAR_Batman_V",
	"CHAR_BlackAdam",
	"CHAR_BlackAdam_V",
	"CHAR_Catwoman",
	"CHAR_Catwoman_A",
	"CHAR_Catwoman_V",
	"CHAR_Cyborg",
	"CHAR_Cyborg_V",
	"CHAR_Deathstroke",
	"CHAR_Deathstroke_A",
	"CHAR_Deathstroke_V",
	"CHAR_Doomsday",
	"CHAR_Doomsday_V",
	"CHAR_Flash",
	"CHAR_Flash_A",
	"CHAR_Flash_B",
	"CHAR_Flash_V",
	"CHAR_GreenArrow",
	"CHAR_GreenArrow_A",
	"CHAR_GreenArrow_V",
	"CHAR_GreenLantern",
	"CHAR_GreenLantern_A",
	"CHAR_GreenLantern_C",
	"CHAR_GreenLantern_V",
	"CHAR_HarleyQuinn",
	"CHAR_HarleyQuinn_A",
	"CHAR_HarleyQuinn_V",
	"CHAR_Hawkgirl",
	"CHAR_Hawkgirl_V",
	"CHAR_Joker",
	"CHAR_Joker_A",
	"CHAR_Joker_V",
	"CHAR_KillerFrost",
	"CHAR_KillerFrost_V",
	"CHAR_LexLuthor",
	"CHAR_LexLuthor_A",
	"CHAR_LexLuthor_V",
	"CHAR_Nightwing",
	"CHAR_Nightwing_A",
	"CHAR_Nightwing_V",
	"CHAR_Raven",
	"CHAR_Raven_V",
	"CHAR_Shazam",
	"CHAR_Shazam_A",
	"CHAR_Shazam_V",
	"CHAR_Sinestro",
	"CHAR_Sinestro_V",
	"CHAR_SolomonGrundy",
	"CHAR_SolomonGrundy_A",
	"CHAR_SolomonGrundy_B",
	"CHAR_SolomonGrundy_V",
	"CHAR_Superman",
	"CHAR_Superman_A",
	"CHAR_Superman_B",
	"CHAR_Superman_C",
	"CHAR_Superman_D",
	"CHAR_Superman_V",
	"CHAR_WonderWoman",
	"CHAR_WonderWoman_A",
	"CHAR_WonderWoman_B",
	"CHAR_WonderWoman_C",
	"CHAR_WonderWoman_V",
};

const char* szStageNames[]{
	"BGND_Arkham",
	"BGND_ArkhamV",
	"BGND_Atlantis",
	"BGND_Batcave",
	"BGND_CharacterBio",
	"BGND_CharacterTest",
	"BGND_DCF_Base",
	"BGND_DesignTest",
	"BGND_Ferris",
	"BGND_Fortress",
	"BGND_Gotham",
	"BGND_GPD_Int_Room",
	"BGND_Insurgency",
	"BGND_Justice",
	"BGND_Metropolis",
	"BGND_ScenarioBase",
	"BGND_SIPrison",
	"BGND_Themyscira",
	"BGND_WatchTower",
	"BGND_WayneManor",
	"BGND_WayneManorN",
};

DCFMenu* TheMenu = new DCFMenu();

static void ShowHelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}

}

void DCFMenu::Initialize()
{
	sprintf(szPlayer1ModifierCharacter, szCharacters[0]);
	sprintf(szPlayer2ModifierCharacter, szCharacters[0]);
	sprintf(szStageModifierStage, szStageNames[0]);
}

void DCFMenu::Process()
{
	UpdateControls();
}

void DCFMenu::Draw()
{
	ImGui::GetIO().MouseDrawCursor = true;
	ImGui::Begin(GetINJHookVersion(), &m_bIsActive, ImGuiWindowFlags_MenuBar);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Settings"))
		{
			m_bSubmenuActive[SUBMENU_SETTINGS] = true;
			ImGui::EndMenu();
		}
	}
	ImGui::EndMenuBar();

	if (ImGui::BeginTabBar("##tabs"))
	{
		if (ImGui::BeginTabItem("Character Modifier"))
		{
			ImGui::Checkbox("Enable Player 1 Modifier", &m_bPlayer1Modifier);

			if (ImGui::BeginCombo("Player 1 Character", szPlayer1ModifierCharacter))
			{
				for (int n = 0; n < IM_ARRAYSIZE(szCharacters); n++)
				{
					bool is_selected = (szPlayer1ModifierCharacter == szCharacters[n]);
					if (ImGui::Selectable(szCharacters[n], is_selected))
						sprintf(szPlayer1ModifierCharacter, szCharacters[n]);
					if (is_selected)
						ImGui::SetItemDefaultFocus();

				}
				ImGui::EndCombo();
			}
			ImGui::Separator();
			ImGui::Checkbox("Enable Player 2 Modifier", &m_bPlayer2Modifier);

			if (ImGui::BeginCombo("Player 2 Character", szPlayer2ModifierCharacter))
			{
				for (int n = 0; n < IM_ARRAYSIZE(szCharacters); n++)
				{
					bool is_selected = (szPlayer2ModifierCharacter == szCharacters[n]);
					if (ImGui::Selectable(szCharacters[n], is_selected))
						sprintf(szPlayer2ModifierCharacter, szCharacters[n]);
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Stage Modifier"))
		{
			ImGui::Checkbox("Enable Stage Modifier", &m_bStageModifier);

			if (ImGui::BeginCombo("Stage", szStageModifierStage))
			{
				for (int n = 0; n < IM_ARRAYSIZE(szStageNames); n++)
				{
					bool is_selected = (szStageModifierStage == szStageNames[n]);
					if (ImGui::Selectable(szStageNames[n], is_selected))
						sprintf(szStageModifierStage, szStageNames[n]);
					if (is_selected)
						ImGui::SetItemDefaultFocus();

				}
				ImGui::EndCombo();
			}

			if (ImGui::Button("Reset Stage Objects"))
				ResetStageInteractables();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Camera Control"))
		{
			ImGui::Checkbox("Set Camera Position", &m_bCustomCameraPos);
			ImGui::InputFloat3("X | Y | Z", &camPos.X);
			ImGui::Checkbox("Set Camera Rotation", &m_bCustomCameraRot);
			ImGui::InputInt3("Pitch | Yaw | Roll", &camRot.Pitch);
			ImGui::Checkbox("Set FOV", &m_bCustomCameraFOV);
			ImGui::InputFloat("FOV", &camFov);
			ImGui::Separator();
			ImGui::Checkbox("Enable Freecam", &m_bFreeCam);
			ImGui::SameLine(); ShowHelpMarker("Allows to move camera with certain keys.\nRequires all toggles enabled!\nYou can configure keys in .ini file.");

			if (m_bFreeCam)
			{
				if (!m_bCustomCameraPos || !m_bCustomCameraRot || !m_bCustomCameraFOV)
					ImGui::TextColored(ImVec4(1.f, 0.3f, 0.3f, 1.f), "Check rest of the Set Camera options!");

				ImGui::InputFloat("Freecam Speed", &m_fFreeCameraSpeed);
				ImGui::InputInt("Freecam Rotation Speed", &m_nFreeCameraRotationSpeed);
			}

			ImGui::EndTabItem();

		}
		if (ImGui::BeginTabItem("Cheats"))
		{
			ImGui::Separator();
			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, 11.5f * ImGui::GetFontSize());

			ImGui::Text("Infinite Health");
			ImGui::NextColumn();
			ImGui::Checkbox("P1##infhealth", &m_bInfiniteHealthP1);
			ImGui::SameLine();
			ImGui::Checkbox("P2##infhealth", &m_bInfiniteHealthP2);
			ImGui::NextColumn();


			ImGui::Text("Zero Health\n");
			ImGui::NextColumn();
			ImGui::Checkbox("P1##0health", &m_bNoHealthP1);
			ImGui::SameLine();
			ImGui::Checkbox("P2##0health", &m_bNoHealthP2);
			ImGui::NextColumn();

			ImGui::Text("Infinite Meter\n");
			ImGui::NextColumn();
			ImGui::Checkbox("P1##super", &m_bInfiniteMeterP1);
			ImGui::SameLine();
			ImGui::Checkbox("P2##super", &m_bInfiniteMeterP2);
			ImGui::NextColumn();

			ImGui::Text("Zero Meter\n");
			ImGui::NextColumn();
			ImGui::Checkbox("P1##0super", &m_bZeroMeterP1);
			ImGui::SameLine();
			ImGui::Checkbox("P2##0super", &m_bZeroMeterP2);
			ImGui::NextColumn();


			ImGui::Columns(1);
			

			ImGui::EndTabItem();
		}
	}
	ImGui::End();


	if (m_bSubmenuActive[SUBMENU_SETTINGS])
		DrawSettings();
}

void DCFMenu::UpdateControls()
{
	if (TheMenu->m_bFreeCam)
	{
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyXPlus))
			TheMenu->camPos.X += TheMenu->m_fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyXMinus))
			TheMenu->camPos.X -= TheMenu->m_fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYPlus))
			TheMenu->camPos.Y += TheMenu->m_fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYMinus))
			TheMenu->camPos.Y -= TheMenu->m_fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyZPlus))
			TheMenu->camPos.Z += TheMenu->m_fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyZMinus))
			TheMenu->camPos.Z -= TheMenu->m_fFreeCameraSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYawMinus))
			TheMenu->camRot.Yaw -= TheMenu->m_nFreeCameraRotationSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYawPlus))
			TheMenu->camRot.Yaw += TheMenu->m_nFreeCameraRotationSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRollMinus))
			TheMenu->camRot.Roll -= TheMenu->m_nFreeCameraRotationSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRollPlus))
			TheMenu->camRot.Roll += TheMenu->m_nFreeCameraRotationSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyPitchMinus))
			TheMenu->camRot.Pitch -= TheMenu->m_nFreeCameraRotationSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyPitchPlus))
			TheMenu->camRot.Pitch += TheMenu->m_nFreeCameraRotationSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyFOVMinus))
		{
			Sleep(20);
			TheMenu->camFov -= 1.0f;
		}

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyFOVPlus))
		{
			Sleep(20);
			TheMenu->camFov += 1.0f;
		}

	}
}

void DCFMenu::DrawSettings()
{
	ImGui::SetNextWindowPos({ ImGui::GetIO().DisplaySize.x / 2.0f, ImGui::GetIO().DisplaySize.y / 2.0f }, ImGuiCond_Once, { 0.5f, 0.5f });
	ImGui::SetNextWindowSize({ 700,700 }, ImGuiCond_Once);
	ImGui::Begin("Settings", &m_bSubmenuActive[SUBMENU_SETTINGS]);

	static int settingID = 0;
	static const char* settingNames[] = {
		"Menu",
		"INI"
	};

	enum eSettings {
		MENU,
		INI,
	};

	ImGui::BeginChild("##settings", { 12 * ImGui::GetFontSize(), 0 }, true);

	for (int n = 0; n < IM_ARRAYSIZE(settingNames); n++)
	{
		bool is_selected = (settingID == n);
		if (ImGui::Selectable(settingNames[n], is_selected))
			settingID = n;
		if (is_selected)
			ImGui::SetItemDefaultFocus();
	}

	ImGui::EndChild();

	ImGui::SameLine();
	ImGui::BeginChild("##content", { 0, -ImGui::GetFrameHeightWithSpacing() });

	switch (settingID)
	{
	case MENU:
		ImGui::TextWrapped("All user settings are saved to INJHook_user.ini.");
		ImGui::Text("Menu Scale");
		ImGui::InputFloat("", &SettingsMgr->fMenuScale);
		break;
	case INI:
		ImGui::TextWrapped("These settings control INJHook.ini options. Any changes require game restart to take effect.");
		ImGui::LabelText("", "Core");
		ImGui::Separator();
		ImGui::Checkbox("Debug Console", &SettingsMgr->bEnableConsoleWindow);

		break;
	default:
		break;
	}

	if (ImGui::Button("Save", { -FLT_MIN, 0 }))
	{
		Notifications->SetNotificationTime(2500);
		Notifications->PushNotification("Settings saved to INJHook.ini and INJHook_user.ini!");
		eDirectX9Hook::ms_bShouldReloadFonts = true;
		SettingsMgr->SaveSettings();
	}

	ImGui::EndChild();

	ImGui::End();
}

bool DCFMenu::GetActiveState()
{
	return m_bIsActive;
}

char * GetINJHookVersion()
{
	static char buffer[512] = {};
	sprintf(buffer, "INJHook by ermaccer (%s)", INJHOOK_VERSION);
	return buffer;
}
