#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DSDevDamageActor.generated.h"

//-------------------------------------------------------------------------------------------------------------
UCLASS()
class DEMOSHOOTER_API ADSDevDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADSDevDamageActor();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool Full_Damage = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Radius = 300.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Damage = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FColor Sphere_Color = FColor::Red;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) USceneComponent *Scene_Component;

protected:
	virtual void BeginPlay() override;
};
//-------------------------------------------------------------------------------------------------------------
