#include "AI/DSAICharacter.h"
#include "AI/DSAIController.h"
#include "Components/DSAIWeaponComponent.h"
#include "BrainComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

//-------------------------------------------------------------------------------------------------------------
ADSAICharacter::ADSAICharacter(const FObjectInitializer &obj_init)
	: Super(obj_init.SetDefaultSubobjectClass<UDSAIWeaponComponent>("WeaponComponent"))
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
void ADSAICharacter::On_Death()
{
	Super::On_Death();

	const auto ds_controller = Cast<AAIController>(Controller);

	if (ds_controller && ds_controller->BrainComponent)
	{
		ds_controller->BrainComponent->Cleanup();
	}
}