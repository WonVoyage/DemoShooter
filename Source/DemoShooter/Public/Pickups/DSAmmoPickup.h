#pragma once

#include "CoreMinimal.h"
#include "Pickups/DSBasePickup.h"
#include "DSAmmoPickup.generated.h"

class ADSBaseWeapon;

//-------------------------------------------------------------------------------------------------------------
UCLASS()
class DEMOSHOOTER_API ADSAmmoPickup : public ADSBasePickup
{
	GENERATED_BODY()

protected:
	virtual bool Give_Pickup_To(APawn* pawn) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0")) int32 Amount_Clips = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup") TSubclassOf<ADSBaseWeapon> Type_Weapon;
};
//-------------------------------------------------------------------------------------------------------------
