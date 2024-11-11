#include "Weapon/DSBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include <Kismet/GameplayStatics.h>
#include "Engine/DamageEvents.h"

//-------------------------------------------------------------------------------------------------------------
ADSBaseWeapon::ADSBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMesh_Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));

	SetRootComponent(SkeletalMesh_Weapon);
}
//-------------------------------------------------------------------------------------------------------------
void ADSBaseWeapon::Fire()
{
	UE_LOG(LogTemp, Error, TEXT("FIRE!!!!"));
	Make_Shot();
}
//-------------------------------------------------------------------------------------------------------------
void ADSBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}
//-------------------------------------------------------------------------------------------------------------
void ADSBaseWeapon::Make_Shot()
{
	const auto player = Cast<ACharacter>(GetOwner());
	const auto controller = player->GetController();
	const FTransform socket_transform = SkeletalMesh_Weapon->GetSocketTransform(Name_MuzzleSocket);
	FVector view_location;
	FRotator view_rotation;
	controller->GetPlayerViewPoint(view_location, view_rotation);
	const FVector trace_start = view_location;
	const FVector shoot_direction = view_rotation.Vector();
	const FVector trace_end = trace_start + shoot_direction * Trace_Max_Distance;
	FCollisionQueryParams collision_params;
	collision_params.AddIgnoredActor(GetOwner());
	FHitResult hit_result;

	GetWorld()->LineTraceSingleByChannel(hit_result, trace_start, trace_end, ECollisionChannel::ECC_Visibility, collision_params);

	if (hit_result.bBlockingHit)
	{
		DrawDebugLine(GetWorld(), socket_transform.GetLocation(), hit_result.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
		DrawDebugSphere(GetWorld(), hit_result.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);

		ACharacter *hit_player = Cast<ACharacter>(hit_result.GetActor());

		if (!hit_player)
		{
			return;
		}

		hit_player->TakeDamage(10.0f, FDamageEvent(), UGameplayStatics::GetPlayerController(this, 0), this);
	}
	else
	{
		DrawDebugLine(GetWorld(), socket_transform.GetLocation(), trace_end, FColor::Red, false, 3.0f, 0, 3.0f);
	}
}
//-------------------------------------------------------------------------------------------------------------
