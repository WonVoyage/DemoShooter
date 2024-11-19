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