#pragma once

#include "CoreMinimal.h"
#include "Weapon/DSBaseWeapon.h"
#include "DSLauncherWeapon.generated.h"

class ADSProjectile;

//-------------------------------------------------------------------------------------------------------------
UCLASS()
class DEMOSHOOTER_API ADSLauncherWeapon : public ADSBaseWeapon
{
	GENERATED_BODY()
	
public:
	ADSLauncherWeapon();

	virtual void Start_Fire() override;
	virtual void Stop_Fire() override;

protected:
	virtual void Make_Shot() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon") TSubclassOf<ADSProjectile> Class_Projectile;
};
//-------------------------------------------------------------------------------------------------------------
