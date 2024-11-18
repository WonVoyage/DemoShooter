#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "DSEquipFinishedAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifiedSignature, USkeletalMeshComponent*);

//-------------------------------------------------------------------------------------------------------------
UCLASS()
class DEMOSHOOTER_API UDSEquipFinishedAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent *mesh_component, UAnimSequenceBase *animation) override;

	FOnNotifiedSignature OnNotified;
};
//-------------------------------------------------------------------------------------------------------------
