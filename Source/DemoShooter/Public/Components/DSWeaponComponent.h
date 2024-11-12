#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DSWeaponComponent.generated.h"

class ADSBaseWeapon;

//-------------------------------------------------------------------------------------------------------------
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEMOSHOOTER_API UDSWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDSWeaponComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") TSubclassOf<ADSBaseWeapon> Weapon_Class;
	
	ADSBaseWeapon *Current_Weapon = nullptr;

	void Start_Fire();
	void Stop_Fire();

protected:
	virtual void BeginPlay() override;

private:
	void Spawn_Weapon();
};
//-------------------------------------------------------------------------------------------------------------
