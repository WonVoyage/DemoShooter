#include "AI/DSAICharacter.h"
#include "AI/DSAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

//-------------------------------------------------------------------------------------------------------------
ADSAICharacter::ADSAICharacter(const FObjectInitializer &obj_init)
	: Super(obj_init)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ADSAIController::StaticClass();
	bUseControllerRotationYaw = false;

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
}
//-------------------------------------------------------------------------------------------------------------
