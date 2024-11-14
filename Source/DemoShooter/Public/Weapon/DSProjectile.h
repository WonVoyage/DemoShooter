#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DSProjectile.generated.h"

class USphereComponent;

//-------------------------------------------------------------------------------------------------------------
UCLASS()
class DEMOSHOOTER_API ADSProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ADSProjectile();

protected:
	virtual void BeginPlay() override;

private:

	USphereComponent *Component_Collision;
};
//-------------------------------------------------------------------------------------------------------------
