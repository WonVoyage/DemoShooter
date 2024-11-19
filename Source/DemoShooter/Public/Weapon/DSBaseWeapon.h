#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DSBaseWeapon.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature);

//-------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()
	FAmmoData();
	FAmmoData(bool infinite, int32 bullets, int32 clips);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon") bool Infinite;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon") int32 Bullets;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!Infinite")) int32 Clips;
};
//-------------------------------------------------------------------------------------------------------------
UCLASS()
class DEMOSHOOTER_API ADSBaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	ADSBaseWeapon();
	virtual void Start_Fire();
	virtual void Stop_Fire();

	void Change_Clip();
	bool Can_Reload() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon") USkeletalMeshComponent* SkeletalMesh_Weapon;

	FOnClipEmptySignature On_Clip_Empty;

protected:
	virtual void BeginPlay() override;
	virtual void Make_Shot();
	virtual bool Get_Trace_Data(FVector& trace_start, FVector& trace_end) const;
	void Make_Hit(FHitResult& hit_result, const FVector& trace_start, const FVector& trace_end);
	void Make_Damage(const FHitResult& hit_result);
	void Decrease_Ammo();
	void Log_Ammo();
	bool Is_Ammo_Empty() const;
	bool Is_Clip_Empty() const;
	bool Get_PlayerViewPoint(FVector& view_location, FRotator& view_rotation) const;
	APlayerController* Get_PlayerController() const;
	FVector Get_Muzzle_World_Location() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) float Trace_Max_Distance = 1500.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) FName Name_MuzzleSocket = "Muzzle_Socket";
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) FAmmoData Default_Ammo { false, 15, 10 };

private:
	FAmmoData Current_Ammo;
};
//-------------------------------------------------------------------------------------------------------------
