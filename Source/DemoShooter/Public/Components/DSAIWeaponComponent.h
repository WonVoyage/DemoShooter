#pragma once

#include "CoreMinimal.h"
#include "Components/DSWeaponComponent.h"
#include "DSAIWeaponComponent.generated.h"

//-------------------------------------------------------------------------------------------------------------
UCLASS()
class DEMOSHOOTER_API UDSAIWeaponComponent : public UDSWeaponComponent
{
	GENERATED_BODY()

public:
	virtual void Start_Fire() override;
	virtual void Next_Weapon() override;
};
//-------------------------------------------------------------------------------------------------------------
