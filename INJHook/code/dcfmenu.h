#include "dcf.h"
enum eCustomCameras {
	CAMERA_3RDPERSON,
	TOTAL_CUSTOM_CAMERAS
};

enum eMenuSubMenus {
	SUBMENU_SETTINGS,
	TOTAL_SUBMENUS
};

// as usual, based on mh2 debug menu

class DCFMenu {
public:
	bool	 m_bIsActive = false;
	bool	 m_bSubmenuActive[TOTAL_SUBMENUS] = {};
	bool     m_bPressingKey = false;
	bool	 m_bSlowMotion = false;
	bool     m_bFreezeWorld = false;
	bool	 m_bIsFocused = false;
	bool	 m_bCustomCameraPos = false;
	bool	 m_bCustomCameraRot = false;
	bool	 m_bCustomCameraFOV = false;
	bool	 m_bFreeCam = false;
	bool	 m_bCustomCameras = false;
	bool	 m_bYObtained = false;
	bool	 m_bStageModifier = false;
	// cheats
	bool	m_bInfiniteHealthP1 = false;
	bool	m_bInfiniteHealthP2 = false;
	bool	m_bInfiniteMeterP1 = false;
	bool	m_bInfiniteMeterP2 = false;
	bool	m_bNoHealthP1 = false;
	bool	m_bNoHealthP2 = false;
	bool	m_bZeroMeterP1 = false;
	bool	m_bZeroMeterP2 = false;

	bool	m_bPlayer1Modifier = false;
	bool	m_bPlayer2Modifier = false;

	int		 m_nFreeCameraRotationSpeed = 20;
	float	 m_fFreeCameraSpeed = 1.0f;

	char szPlayer1ModifierCharacter[128] = {};
	char szPlayer2ModifierCharacter[128] = {};
	char szStageModifierStage[128] = {};

	FVector camPos;
	FRotator camRot;
	float camFov;

	void Initialize();
	void Process();
	void Draw();
	void UpdateControls();

	void DrawSettings();

	bool GetActiveState();
};



extern DCFMenu* TheMenu;

char* GetINJHookVersion();