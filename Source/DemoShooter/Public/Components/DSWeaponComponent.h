#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DSWeaponComponent.generated.h"

class ADSBaseWeapon;

//-------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon") TSubclassOf<ADSBaseWeapon> Weapon_Class;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation") UAnimMontage *AnimMontage_Reload;
};
//-------------------------------------------------------------------------------------------------------------
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEMOSHOOTER_API UDSWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDSWeaponComponent();

	void Start_Fire();
	void Stop_Fire();
	void Next_Weapon();
	void Reload();
	ADSBaseWeapon *Get_Current_Weapon();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon") FName Name_Weapon_Equip_Socket = "Weapon_Socket";
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon") FName Name_Weapon_Armory_Socket = "Armory_Socket";
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation") UAnimMontage *AnimMontage_Equip = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation") UAnimMontage *AnimMontage_Current_Reload = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon") TArray<FWeaponData> Weapon_Data;

protected:
	virtual void BeginPlay() override;

private:
	void Spawn_Weapons();
	void Attach_Weapon_To_Socket(ADSBaseWeapon *weapon, USceneComponent *scene_component, FName socket_name);
	void Equip_Weapon(int32 weapon_index);
	void Play_AnimMontage(UAnimMontage *animation);
	void Init_Animations();
	void On_Equip_Finished(USkeletalMeshComponent* mesh_component);
	bool Can_Fire() const;
	bool Can_Equip() const;

	UPROPERTY() ADSBaseWeapon *Current_Weapon = nullptr;
	UPROPERTY() TArray<ADSBaseWeapon*> Weapons;

	bool Equip_Anim_In_Progress = false;
	int32 Current_Weapon_Index = 0;
};
//-------------------------------------------------------------------------------------------------------------
