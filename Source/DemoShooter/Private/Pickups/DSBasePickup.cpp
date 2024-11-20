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
}
//-------------------------------------------------------------------------------------------------------------
void ADSBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
//-------------------------------------------------------------------------------------------------------------
void ADSBasePickup::NotifyActorBeginOverlap(AActor *other_actor)
{
	Super::NotifyActorBeginOverlap(other_actor);

	const auto pawn = Cast<APawn>(other_actor);

	UE_LOG(LogTemp, Display, TEXT("Pickup was taken"));
	Pickup_Was_Taken();
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
	Component_Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	GetRootComponent()->SetVisibility(true, true);
}
//-------------------------------------------------------------------------------------------------------------
