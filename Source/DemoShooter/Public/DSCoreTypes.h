#pragma once

#include "DSCoreTypes.generated.h"

// Weapon
DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature);

class ADSBaseWeapon;

//-------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()
	FAmmoData();
	FAmmoData(bool infinite, int32 bullets, int32 clips);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon") bool Infinite;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon") int32 Bullets;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!Infinite")) int32 Clips;
};
//-------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon") TSubclassOf<ADSBaseWeapon> Weapon_Class;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation") UAnimMontage* AnimMontage_Reload;
};
//-------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FWeaponUIData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon") UTexture2D *Main_Icon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon") UTexture2D* CrossHair_Icon;
};
//-------------------------------------------------------------------------------------------------------------




// Health
DECLARE_MULTICAST_DELEGATE(FOnDeath);




// VFX

class UNiagaraSystem;
//-------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FDecalData
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX") float Time_Life = 5.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX") float Time_Fade_Out = 0.7f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX") FVector Size = FVector(10.0f);
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX") UMaterialInterface *Material;
};
//-------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FImpactData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX") UNiagaraSystem *Effect_Niagara;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX") FDecalData Data_Decal;
};
//-------------------------------------------------------------------------------------------------------------
