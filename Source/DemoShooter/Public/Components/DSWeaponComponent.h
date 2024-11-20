#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DSCoreTypes.h"
#include "DSWeaponComponent.generated.h"

class ADSBaseWeapon;

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
	void On_Empty_Clip();
	void Change_Clip();
	bool Get_Weapon_UI_Data(FWeaponUIData &data) const;
	bool Get_Weapon_Ammo_Data(FAmmoData &data) const;
	bool Try_To_Add_Ammo(TSubclassOf<ADSBaseWeapon> type_weapon, int32 amount_clips);
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
	void On_Equip_Finished(USkeletalMeshComponent *mesh_component);
	void On_Reload_Finished(USkeletalMeshComponent *mesh_component);
	bool Can_Fire() const;
	bool Can_Equip() const;
	bool Can_Reload() const;

	UPROPERTY() ADSBaseWeapon *Current_Weapon = nullptr;
	UPROPERTY() TArray<ADSBaseWeapon*> Weapons;

	bool Anim_In_Progress_Equip = false;
	bool Anim_In_Progress_Reload = false;
	int32 Index_Current_Weapon = 0;
};
//-------------------------------------------------------------------------------------------------------------
