#include "Weapon/DSLauncherWeapon.h"
#include "Weapon/DSProjectile.h"

//-------------------------------------------------------------------------------------------------------------
ADSLauncherWeapon::ADSLauncherWeapon()
{
}
//-------------------------------------------------------------------------------------------------------------
void ADSLauncherWeapon::Start_Fire()
{
	Make_Shot();
}
//-------------------------------------------------------------------------------------------------------------
void ADSLauncherWeapon::Stop_Fire()
{

}
//-------------------------------------------------------------------------------------------------------------
void ADSLauncherWeapon::Make_Shot()
{
	if (!GetWorld())
	{
		return;
	}

	FVector trace_start, trace_end, end_point, direction;
	FHitResult hit_result;

	if (!Get_Trace_Data(trace_start, trace_end))
	{
		return;
	}

	Make_Hit(hit_result, trace_start, trace_end);

	if (hit_result.bBlockingHit)
	{
		end_point = hit_result.ImpactPoint;
	}
	else
	{
		end_point = trace_end;
	}

	direction = (end_point - Get_Muzzle_World_Location()).GetSafeNormal();

	const FTransform spawn_transform(FRotator::ZeroRotator, Get_Muzzle_World_Location());
	
	if (ADSProjectile* projectile = GetWorld()->SpawnActorDeferred<ADSProjectile>(Class_Projectile, spawn_transform))
	{
		projectile->Set_Shot_Direction(direction);
		projectile->SetOwner(GetOwner());
		projectile->FinishSpawning(spawn_transform);
	}
}
//-------------------------------------------------------------------------------------------------------------
