#include "Components/DSCharacterMovementComponent.h"
#include "Player/DSCharacter.h"

//-------------------------------------------------------------------------------------------------------------
float UDSCharacterMovementComponent::GetMaxSpeed() const
{
	const float max_speed = Super::GetMaxSpeed();
	const ADSCharacter *character = Cast<ADSCharacter>(GetPawnOwner());

	return character && character->Is_Running() ? max_speed * Run_Modifire : max_speed;
}
//-------------------------------------------------------------------------------------------------------------
