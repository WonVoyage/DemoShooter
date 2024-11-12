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
	virtual void Make_Shot();
	virtual bool Get_Trace_Data(FVector& trace_start, FVector& trace_end) const;

	
	void Make_Hit(FHitResult& hit_result, const FVector& trace_start, const FVector& trace_end);
	void Make_Damage(const FHitResult& hit_result);
	bool Get_PlayerViewPoint(FVector& view_location, FRotator& view_rotation) const;
	APlayerController *Get_PlayerController() const;
	FVector Get_Muzzle_World_Location() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) float Trace_Max_Distance = 1500.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) FName Name_MuzzleSocket = "Muzzle_Socket";
};
//-------------------------------------------------------------------------------------------------------------
