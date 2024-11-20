#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DSBasePickup.generated.h"

class USphereComponent;

//-------------------------------------------------------------------------------------------------------------
UCLASS()
class DEMOSHOOTER_API ADSBasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	ADSBasePickup();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor *other_actor) override;

	UPROPERTY(VisibleAnywhere, Category = "Pickup")USphereComponent *Component_Collision;
};
//-------------------------------------------------------------------------------------------------------------
