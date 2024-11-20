#pragma once

#include "CoreMinimal.h"
#include "Pickups/DSBasePickup.h"
#include "DSAmmoPickup.generated.h"

//-------------------------------------------------------------------------------------------------------------
UCLASS()
class DEMOSHOOTER_API ADSAmmoPickup : public ADSBasePickup
{
	GENERATED_BODY()

private:
	virtual bool Give_Pickup_To(APawn* pawn) override;
};
//-------------------------------------------------------------------------------------------------------------
