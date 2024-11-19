#include "Components/DSWeaponComponent.h"
#include "Weapon/DSBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/DSEquipFinishedAnimNotify.h"
#include "Animations/DSReloadFinishedAnimNotify.h"

//-------------------------------------------------------------------------------------------------------------
UDSWeaponComponent::UDSWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponComponent::Start_Fire()
{
	if (Can_Fire())
	{
		Current_Weapon->Start_Fire();
	}
}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponComponent::Stop_Fire()
{
	Current_Weapon->Stop_Fire();
}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponComponent::Next_Weapon()
{
	if (!Can_Equip())
	{
		return;
	}

	Current_Weapon->Stop_Fire();
	Index_Current_Weapon = (Index_Current_Weapon + 1) % Weapons.Num();

	Equip_Weapon(Index_Current_Weapon);
}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponComponent::Reload()
{
	Change_Clip();
}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponComponent::On_Empty_Clip()
{
	Change_Clip();
}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponComponent::Change_Clip()
{
	if (!Can_Reload())
	{
		return;
	}

	Current_Weapon->Stop_Fire();
	Current_Weapon->Change_Clip();
	Anim_In_Progress_Reload = true;
	Play_AnimMontage(AnimMontage_Current_Reload);
}
//-------------------------------------------------------------------------------------------------------------
ADSBaseWeapon* UDSWeaponComponent::Get_Current_Weapon()
{
	return Current_Weapon;
}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	Init_Animations();
	Spawn_Weapons();
	Equip_Weapon(Index_Current_Weapon);
}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponComponent::Spawn_Weapons()
{
	ACharacter *character = Cast<ACharacter>(GetOwner());
	
	if (!character)
	{
		throw 23;
	}

	for (auto &weapon_data : Weapon_Data)
	{
		ADSBaseWeapon *weapon = GetWorld()->SpawnActor<ADSBaseWeapon>(weapon_data.Weapon_Class);

		weapon->SetOwner(GetOwner());
		Weapons.Add(weapon);
		weapon->On_Clip_Empty.AddUObject(this, &UDSWeaponComponent::On_Empty_Clip);
		Attach_Weapon_To_Socket(weapon, character->GetMesh(), Name_Weapon_Armory_Socket);
	}
}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponComponent::Attach_Weapon_To_Socket(ADSBaseWeapon *weapon, USceneComponent *scene_component, FName socket_name)
{
	FAttachmentTransformRules attachment_rules(EAttachmentRule::SnapToTarget, false);
	weapon->AttachToComponent(scene_component, attachment_rules, socket_name);
}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponComponent::Equip_Weapon(int32 weapon_index)
{
	ACharacter *character = Cast<ACharacter>(GetOwner());
	
	if (!character)
	{
		return;
	}

	if (Current_Weapon)
	{
		Attach_Weapon_To_Socket(Current_Weapon, character->GetMesh(), Name_Weapon_Armory_Socket);
	}

	//AnimMontage_Current_Reload = Weapon_Data[weapon_index].AnimMontage_Reload;
	Current_Weapon = Weapons[weapon_index];
	Anim_In_Progress_Equip = true;

	Attach_Weapon_To_Socket(Current_Weapon, character->GetMesh(), Name_Weapon_Equip_Socket);
	Play_AnimMontage(AnimMontage_Equip);

	const auto current_data = Weapon_Data.FindByPredicate([&](const FWeaponData& data) {return data.Weapon_Class == Current_Weapon->GetClass(); });
	AnimMontage_Current_Reload = current_data->AnimMontage_Reload;

}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponComponent::Play_AnimMontage(UAnimMontage *animation)
{
	ACharacter* character = Cast<ACharacter>(GetOwner());

	character->PlayAnimMontage(animation);
}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponComponent::Init_Animations()
{
	if (!AnimMontage_Equip)
	{
		return;
	}

	auto notify_equip_finished = Find_Notify_By_Class<UDSEquipFinishedAnimNotify>(AnimMontage_Equip);

	if (notify_equip_finished)
	{
		notify_equip_finished->OnNotified.AddUObject(this, &UDSWeaponComponent::On_Equip_Finished);
	}

	for (auto &weapon_data : Weapon_Data)
	{
		auto notify_reload_finished = Find_Notify_By_Class<UDSReloadFinishedAnimNotify>(weapon_data.AnimMontage_Reload);

		if (!notify_equip_finished)
		{
			continue;
		}

		notify_reload_finished->OnNotified.AddUObject(this, &UDSWeaponComponent::On_Reload_Finished);
	}

}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponComponent::On_Equip_Finished(USkeletalMeshComponent* mesh_component)
{
	ACharacter* character = Cast<ACharacter>(GetOwner());

 	if (character->GetMesh() == mesh_component)
	{
		Anim_In_Progress_Equip = false;
		UE_LOG(LogTemp, Error, TEXT("Equip Finished"));
	}
}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponComponent::On_Reload_Finished(USkeletalMeshComponent* mesh_component)
{
	ACharacter* character = Cast<ACharacter>(GetOwner());

	if (character->GetMesh() == mesh_component)
	{
		Anim_In_Progress_Reload = false;
		UE_LOG(LogTemp, Error, TEXT("Reload Finished"));
	}
}
//-------------------------------------------------------------------------------------------------------------
bool UDSWeaponComponent::Can_Fire() const
{
	return !Anim_In_Progress_Equip && !Anim_In_Progress_Reload;
}
//-------------------------------------------------------------------------------------------------------------
bool UDSWeaponComponent::Can_Equip() const
{
	return !Anim_In_Progress_Equip;
}
//-------------------------------------------------------------------------------------------------------------
bool UDSWeaponComponent::Can_Reload() const
{
	return !Anim_In_Progress_Reload && !Anim_In_Progress_Equip && Current_Weapon->Can_Reload();
}
//-------------------------------------------------------------------------------------------------------------
template <typename T>
T *UDSWeaponComponent::Find_Notify_By_Class(UAnimSequenceBase *animation)
{
	const auto notify_events = animation->Notifies;

	for (auto notify_event : notify_events)
	{
		auto anim_notify = Cast<T>(notify_event.Notify);

		if (anim_notify)
		{
			return anim_notify;
		}
	}

	return nullptr;
}
//-------------------------------------------------------------------------------------------------------------
