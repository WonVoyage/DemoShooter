#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DSCharacterMovementComponent.generated.h"

//-------------------------------------------------------------------------------------------------------------
UCLASS()
class DEMOSHOOTER_API UDSCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

	virtual float GetMaxSpeed() const override;

	UPROPERTY(EditDefaultsOnly, Category = "Moving", meta = (ClampMin = "1.5", ClampMax = "10.0")) float Run_Modifire = 2.0f;
};
//-------------------------------------------------------------------------------------------------------------
