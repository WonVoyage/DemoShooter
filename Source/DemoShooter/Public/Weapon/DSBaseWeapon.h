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

	virtual void Start_Fire();
	virtual void Stop_Fire();

protected:
	virtual void BeginPlay() override;

	void Make_Shot();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) float Trace_Max_Distance = 1500.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) float Bullet_Spread = 1.5f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) float Time_Between_Shots = 0.1f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) FName Name_MuzzleSocket = "Muzzle_Socket";

private:
	FTimerHandle Timer_Fire;
};
//-------------------------------------------------------------------------------------------------------------
