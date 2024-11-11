#include "DSGameModeBase.h"
#include "Player/DSPlayerController.h"
#include "Player/DSCharacter.h"
#include "UI/DSGameHUD.h"

//-------------------------------------------------------------------------------------------------------------
ADSGameModeBase::ADSGameModeBase()
{
	DefaultPawnClass = ADSCharacter::StaticClass();
	PlayerControllerClass = ADSPlayerController::StaticClass();
	HUDClass = ADSGameHUD::StaticClass();
}
//-------------------------------------------------------------------------------------------------------------
