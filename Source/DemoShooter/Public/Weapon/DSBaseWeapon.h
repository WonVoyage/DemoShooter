#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DSBaseWeapon.generated.h"

//-------------------------------------------------------------------------------------------------------------
UCLASS()
class DEMOSHOOTER_API ADSBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ADSBaseWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") USkeletalMeshComponent *SkeletalMesh_Weapon;

	virtual void Fire();

protected:
	virtual void BeginPlay() override;
};
//-------------------------------------------------------------------------------------------------------------
