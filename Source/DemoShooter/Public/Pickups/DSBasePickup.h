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
	virtual bool Give_Pickup_To(APawn* pawn);

	UPROPERTY(VisibleAnywhere, Category = "Pickup") float Time_Respawn = 5.0f;
	UPROPERTY(VisibleAnywhere, Category = "Pickup") USphereComponent *Component_Collision;

private:
	void Pickup_Was_Taken();
	void Respawn();
	void Generate_Rotation_Yaw();

	float Rotation_Yaw = 0.0f;
};
//-------------------------------------------------------------------------------------------------------------
