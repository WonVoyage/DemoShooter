#pragma once

#include "CoreMinimal.h"
#include "Weapon/DSBaseWeapon.h"
#include "DSRifleWeapon.generated.h"

//-------------------------------------------------------------------------------------------------------------
UCLASS()
class DEMOSHOOTER_API ADSRifleWeapon : public ADSBaseWeapon
{
	GENERATED_BODY()
	
public:
	ADSRifleWeapon();

	virtual void Start_Fire() override;
	virtual void Stop_Fire() override;

protected:
	virtual void Make_Shot() override;
	virtual bool Get_Trace_Data(FVector& trace_start, FVector& trace_end) const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) float Bullet_Spread = 1.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) float Time_Between_Shots = 0.1f;

private:
	FTimerHandle Timer_Fire;
};
//-------------------------------------------------------------------------------------------------------------
