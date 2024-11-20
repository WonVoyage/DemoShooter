#include "Pickups/DSBasePickup.h"
#include "Components/SphereComponent.h"

//-------------------------------------------------------------------------------------------------------------
ADSBasePickup::ADSBasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

	Component_Collision = CreateDefaultSubobject<USphereComponent>("Component_Collision");
	Component_Collision->SetSphereRadius(50.0f);
	Component_Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Component_Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	SetRootComponent(Component_Collision);
}
//-------------------------------------------------------------------------------------------------------------
void ADSBasePickup::BeginPlay()
{
	Super::BeginPlay();

	Generate_Rotation_Yaw();
}
//-------------------------------------------------------------------------------------------------------------
void ADSBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.0f, Rotation_Yaw, 0.0f));
}
//-------------------------------------------------------------------------------------------------------------
void ADSBasePickup::NotifyActorBeginOverlap(AActor *other_actor)
{
	Super::NotifyActorBeginOverlap(other_actor);

	const auto pawn = Cast<APawn>(other_actor);
	if (Give_Pickup_To(pawn))
	{
		Pickup_Was_Taken();
	}
}
//-------------------------------------------------------------------------------------------------------------
bool ADSBasePickup::Give_Pickup_To(APawn *pawn)
{
	return false;
}
//-------------------------------------------------------------------------------------------------------------
void ADSBasePickup::Pickup_Was_Taken()
{
	FTimerHandle timer_respawn;

	Component_Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetRootComponent()->SetVisibility(false, true);
	GetWorldTimerManager().SetTimer(timer_respawn, this, &ADSBasePickup::Respawn, Time_Respawn);
}
//-------------------------------------------------------------------------------------------------------------
void ADSBasePickup::Respawn()
{
	Generate_Rotation_Yaw();

	Component_Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	GetRootComponent()->SetVisibility(true, true);
}
//-------------------------------------------------------------------------------------------------------------
void ADSBasePickup::Generate_Rotation_Yaw()
{
	const auto direction = FMath::RandBool() ? 1.0f : -1.0f;

	Rotation_Yaw = FMath::RandRange(1.0f, 2.0f) * direction;
}
//-------------------------------------------------------------------------------------------------------------
