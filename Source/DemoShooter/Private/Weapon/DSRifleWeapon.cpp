#include "Weapon/DSRifleWeapon.h"
#include "Weapon/Components/DSWeaponFXComponents.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

//-------------------------------------------------------------------------------------------------------------
ADSRifleWeapon::ADSRifleWeapon()
{
	Component_FX = CreateDefaultSubobject<UDSWeaponFXComponents>("FX_Component");
}
//-------------------------------------------------------------------------------------------------------------
void ADSRifleWeapon::Start_Fire()
{
	Init_Muzzle_FX();
	GetWorldTimerManager().SetTimer(Timer_Fire, this, &ADSRifleWeapon::Make_Shot, Time_Between_Shots, true);
	Make_Shot();
}
//-------------------------------------------------------------------------------------------------------------
void ADSRifleWeapon::Stop_Fire()
{
	GetWorldTimerManager().ClearTimer(Timer_Fire);
	Set_Muzzle_FX_Visibility(false);
}
//-------------------------------------------------------------------------------------------------------------
void ADSRifleWeapon::Make_Shot()
{
	if (!GetWorld() || Is_Ammo_Empty())
	{
		return;
	}

	FVector trace_start, trace_end;
	FHitResult hit_result;
	
	if (!Get_Trace_Data(trace_start, trace_end))
	{
		return;
	}

	Make_Hit(hit_result, trace_start, trace_end);

	FVector trace_fx_end = trace_end;

	if (hit_result.bBlockingHit)
	{
		trace_fx_end = hit_result.ImpactPoint;
		Make_Damage(hit_result);
		Component_FX->Play_Impact_FX(hit_result);
	}
	Spawn_Trace_FX(Get_Muzzle_World_Location(), trace_fx_end);
	Decrease_Ammo();
}
//-------------------------------------------------------------------------------------------------------------
bool ADSRifleWeapon::Get_Trace_Data(FVector &trace_start, FVector &trace_end) const
{
	const auto half_rad = FMath::DegreesToRadians(Bullet_Spread);
	FVector view_location;
	FRotator view_rotaion;

	if (!Get_PlayerViewPoint(view_location, view_rotaion))
	{
		return false;
	}

	const FVector shoot_direction = FMath::VRandCone(view_rotaion.Vector(), half_rad);
	trace_start = view_location;
	trace_end = trace_start + shoot_direction * Trace_Max_Distance;


	return true;
}
//-------------------------------------------------------------------------------------------------------------
void ADSRifleWeapon::Init_Muzzle_FX()
{
	if (!Component_FX_Muzzle)
	{
		Component_FX_Muzzle = Spawn_Muzzle_FX();
	}

	Set_Muzzle_FX_Visibility(true);
}
//-------------------------------------------------------------------------------------------------------------
void ADSRifleWeapon::Set_Muzzle_FX_Visibility(bool visible)
{
	if (Component_FX_Muzzle)
	{
		Component_FX_Muzzle->SetPaused(!visible);
		Component_FX_Muzzle->SetVisibility(visible, false);
	}
}
//-------------------------------------------------------------------------------------------------------------
void ADSRifleWeapon::Spawn_Trace_FX(const FVector& trace_start, const FVector& trace_end)
{
	const auto trace_fx_component = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Trace_FX, trace_start);
	if (trace_fx_component)
	{
		trace_fx_component->SetNiagaraVariableVec3(Name_Trace_Target, trace_end);
	}
}
//-------------------------------------------------------------------------------------------------------------
