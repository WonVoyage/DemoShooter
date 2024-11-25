#include "Weapon/DSProjectile.h"
#include "Weapon/Components/DSWeaponFXComponents.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

//-------------------------------------------------------------------------------------------------------------
ADSProjectile::ADSProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	Component_Collision = CreateDefaultSubobject<USphereComponent>("Component_Collision");
	Component_Collision->SetSphereRadius(3.0f);
	Component_Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Component_Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Component_Collision->bReturnMaterialOnMove = true;
	
	Component_Movement = CreateDefaultSubobject<UProjectileMovementComponent>("Component_Projectile_Movement");
	Component_Movement->InitialSpeed = 2000.0f;
	Component_Movement->ProjectileGravityScale = 0.0f;

	Component_FX = CreateDefaultSubobject<UDSWeaponFXComponents>("Component_FX");
	
	SetRootComponent(Component_Collision);
}
//-------------------------------------------------------------------------------------------------------------
void ADSProjectile::Set_Shot_Direction(const FVector &direction)
{
	Shot_Direction = direction;
}
//-------------------------------------------------------------------------------------------------------------
void ADSProjectile::BeginPlay()
{
	Super::BeginPlay();

	Component_Movement->Velocity = Shot_Direction * Component_Movement->InitialSpeed;
	Component_Collision->OnComponentHit.AddDynamic(this, &ADSProjectile::On_Projectile_Hit);
	SetLifeSpan(Life_Seconds);
}
//-------------------------------------------------------------------------------------------------------------
void ADSProjectile::On_Projectile_Hit(UPrimitiveComponent *hit_component, AActor *other_actor, UPrimitiveComponent *other_comp, FVector normal_impulse, const FHitResult &hit)
{
	if (!GetWorld())
	{
		return;
	}

	Component_Movement->StopMovementImmediately();
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage_Amount, GetActorLocation(), Damage_Radius, UDamageType::StaticClass(), {}, this, Get_Controller(), Full_Damage);
	//DrawDebugSphere(GetWorld(), GetActorLocation(), Damage_Radius, 24, FColor::Red, false, 5.0f);
	Component_FX->Play_Impact_FX(hit);
	Destroy();
}
//-------------------------------------------------------------------------------------------------------------
AController *ADSProjectile::Get_Controller() const
{
	const auto pawn = Cast<APawn>(GetOwner());

	return pawn ? pawn->GetController() : nullptr;
}
//-------------------------------------------------------------------------------------------------------------
