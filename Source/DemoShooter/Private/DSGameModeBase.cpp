#include "DSGameModeBase.h"
#include "Player/DSPlayerController.h"
#include "Player/DSCharacter.h"


ADSGameModeBase::ADSGameModeBase()
{
	DefaultPawnClass = ADSCharacter::StaticClass();
	PlayerControllerClass = ADSPlayerController::StaticClass();
}