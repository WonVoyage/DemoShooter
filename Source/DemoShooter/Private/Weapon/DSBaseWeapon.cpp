#include "Weapon/DSBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include <Kismet/GameplayStatics.h>
#include "Engine/DamageEvents.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

//-------------------------------------------------------------------------------------------------------------
FAmmoData::FAmmoData(){}
//-------------------------------------------------------------------------------------------------------------
FAmmoData::FAmmoData(bool infinite, int32 bullets, int32 clips)
{
	Infinite = infinite;
	Bullets = bullets;
	Clips = clips;
}
//-------------------------------------------------------------------------------------------------------------
ADSBaseWeapon::ADSBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMesh_Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));

	SetRootComponent(SkeletalMesh_Weapon);
}
//-------------------------------------------------------------------------------------------------------------
void ADSBaseWeapon::Start_Fire()
{

}
//-------------------------------------------------------------------------------------------------------------
void ADSBaseWeapon::Stop_Fire()
{

}
//-------------------------------------------------------------------------------------------------------------
void ADSBaseWeapon::Change_Clip()
{
	Current_Ammo.Bullets = Default_Ammo.Bullets;

	if (!Current_Ammo.Infinite)
	{
		Current_Ammo.Clips--;
	}
	UE_LOG(LogTemp, Warning, TEXT("---------------- CHANGE CLIP ----------------"));
}
//-------------------------------------------------------------------------------------------------------------
bool ADSBaseWeapon::Can_Reload() const
{
	return Current_Ammo.Bullets < Default_Ammo.Bullets && Current_Ammo.Clips > 0;
}
//-------------------------------------------------------------------------------------------------------------
bool ADSBaseWeapon::Try_To_Add_Ammo(int32 amount_clips)
{
	if (Current_Ammo.Infinite || Is_Ammo_Full() || amount_clips <= 0)
	{
		return false;
	}

	if (Is_Ammo_Empty())
	{
		Current_Ammo.Clips = FMath::Clamp(Current_Ammo.Clips + amount_clips, 0, Default_Ammo.Clips + 1);
		On_Clip_Empty.Broadcast();
	}
	else if (Current_Ammo.Clips < Default_Ammo.Clips)
	{
		const auto amount_next_clips = Current_Ammo.Clips + amount_clips;
		if (Default_Ammo.Clips - amount_next_clips >= 0)
		{
			Current_Ammo.Clips = amount_next_clips;
		}
		else
		{
			Current_Ammo.Clips = Default_Ammo.Clips;
			Current_Ammo.Bullets = Default_Ammo.Bullets;
		}
	}
	else
	{
		Current_Ammo.Bullets = Default_Ammo.Bullets;
	}

	return true;
}
//-------------------------------------------------------------------------------------------------------------
FWeaponUIData ADSBaseWeapon::Get_UI_Data() const
{
	return UI_Data;
}
//-------------------------------------------------------------------------------------------------------------
FAmmoData ADSBaseWeapon::Get_Ammo_Data() const
{
	return Current_Ammo;
}
//-------------------------------------------------------------------------------------------------------------
void ADSBaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	Current_Ammo = Default_Ammo;
}
//-------------------------------------------------------------------------------------------------------------
void ADSBaseWeapon::Make_Shot()
{

}
//-------------------------------------------------------------------------------------------------------------
bool ADSBaseWeapon::Get_Trace_Data(FVector &trace_start, FVector &trace_end) const
{
	FVector view_location;
	FRotator view_rotaion;
	FVector shoot_direction;

	if (!Get_PlayerViewPoint(view_location, view_rotaion))
	{
		return false;
	}

	shoot_direction = view_rotaion.Vector();
	trace_start = view_location;
	trace_end = trace_start + shoot_direction * Trace_Max_Distance;

	return true;
}
//-------------------------------------------------------------------------------------------------------------
void ADSBaseWeapon::Make_Hit(FHitResult &hit_result, const FVector &trace_start, const FVector &trace_end)
{
	if (!GetWorld())
	{
		return;
	}

	FCollisionQueryParams collision_params;
	collision_params.AddIgnoredActor(GetOwner());
	collision_params.bReturnPhysicalMaterial = true;

	GetWorld()->LineTraceSingleByChannel(hit_result, trace_start, trace_end, ECollisionChannel::ECC_Visibility, collision_params);
}
//-------------------------------------------------------------------------------------------------------------
void ADSBaseWeapon::Make_Damage(const FHitResult &hit_result)
{
	const auto damage_actor = hit_result.GetActor();

	if (!damage_actor)
	{
		return;
	}

	damage_actor->TakeDamage(10.0f, FDamageEvent(), UGameplayStatics::GetPlayerController(this, 0), this);
}
//-------------------------------------------------------------------------------------------------------------
void ADSBaseWeapon::Decrease_Ammo()
{
	Current_Ammo.Bullets--;

	if (Is_Clip_Empty() && !Is_Ammo_Empty())
	{
		Stop_Fire();
		On_Clip_Empty.Broadcast();
	}
}
//-------------------------------------------------------------------------------------------------------------
bool ADSBaseWeapon::Is_Ammo_Empty() const
{
	return !Current_Ammo.Infinite && Current_Ammo.Clips == 0 && Is_Clip_Empty();
}
//-------------------------------------------------------------------------------------------------------------
bool ADSBaseWeapon::Is_Clip_Empty() const
{
	return Current_Ammo.Bullets == 0;
}
//-------------------------------------------------------------------------------------------------------------
bool ADSBaseWeapon::Is_Ammo_Full() const
{
	return Current_Ammo.Clips == Default_Ammo.Clips && Current_Ammo.Bullets == Default_Ammo.Bullets;
}
//-------------------------------------------------------------------------------------------------------------
bool ADSBaseWeapon::Get_PlayerViewPoint(FVector &view_location, FRotator &view_rotation) const
{
	const auto character = Cast<ACharacter>(GetOwner());

	if (!character)
	{
		return false;
	}

	if (character->IsPlayerControlled())
	{
		const auto controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		if (!controller)
		{
			return false;
		}

		controller->GetPlayerViewPoint(view_location, view_rotation);

		return true;
	}
	else
	{
		view_location = Get_Muzzle_World_Location();
		view_rotation = SkeletalMesh_Weapon->GetSocketRotation(Name_MuzzleSocket);
		return true;
	}

}
//-------------------------------------------------------------------------------------------------------------
APlayerController *ADSBaseWeapon::Get_PlayerController() const
{
	const auto player = Cast<ACharacter>(GetOwner());

	if (!player)
	{
		return nullptr;
	}
	
	return player->GetController<APlayerController>();
}
//-------------------------------------------------------------------------------------------------------------
FVector ADSBaseWeapon::Get_Muzzle_World_Location() const
{
	return SkeletalMesh_Weapon->GetSocketLocation(Name_MuzzleSocket);
}
//-------------------------------------------------------------------------------------------------------------
UNiagaraComponent *ADSBaseWeapon::Spawn_Muzzle_FX()
{
	return UNiagaraFunctionLibrary::SpawnSystemAttached(FX_Muzzle, SkeletalMesh_Weapon, Name_MuzzleSocket, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);
}
//-------------------------------------------------------------------------------------------------------------
