#pragma once

#include "CoreMinimal.h"
#include "Pickups/DSBasePickup.h"
#include "DSHealthPickup.generated.h"

//-------------------------------------------------------------------------------------------------------------
UCLASS()
class DEMOSHOOTER_API ADSHealthPickup : public ADSBasePickup
{
	GENERATED_BODY()

protected:
	virtual bool Give_Pickup_To(APawn* pawn) override;
};
//-------------------------------------------------------------------------------------------------------------
