#pragma once

#include "CoreMinimal.h"
#include "Weapon/DSBaseWeapon.h"
#include "DSRifleWeapon.generated.h"

class UDSWeaponFXComponents;
class UNiagaraSystem;
class UNiagaraComponent;

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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX") UDSWeaponFXComponents *Component_FX;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX") UNiagaraSystem *Trace_FX;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX") FString Name_Trace_Target = "Trace_Target";

private:
	void Init_Muzzle_FX();
	void Set_Muzzle_FX_Visibility(bool visible);
	void Spawn_Trace_FX(const FVector &trace_start, const FVector &trace_end);

	UPROPERTY() UNiagaraComponent *Component_FX_Muzzle;
	FTimerHandle Timer_Fire;
};
//-------------------------------------------------------------------------------------------------------------
