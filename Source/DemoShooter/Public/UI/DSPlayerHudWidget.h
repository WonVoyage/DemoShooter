#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DSCoreTypes.h"
#include "DSPlayerHudWidget.generated.h"

//-------------------------------------------------------------------------------------------------------------
UCLASS()
class DEMOSHOOTER_API UDSPlayerHudWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "UI") float Get_Health_Percent() const;
	UFUNCTION(BlueprintCallable, Category = "UI") bool Get_Weapon_UI_Data(FWeaponUIData &data) const;
	UFUNCTION(BlueprintCallable, Category = "UI") bool Get_Weapon_Ammo_Data(FAmmoData &data) const;
};
//-------------------------------------------------------------------------------------------------------------
