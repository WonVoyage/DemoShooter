#include "Dev/DSDevDamageActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

//-------------------------------------------------------------------------------------------------------------
ADSDevDamageActor::ADSDevDamageActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Scene_Component = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	SetRootComponent(Scene_Component);
}
//-------------------------------------------------------------------------------------------------------------
void ADSDevDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, Sphere_Color);
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, nullptr, {}, this, nullptr, Full_Damage);
}
//-------------------------------------------------------------------------------------------------------------
void ADSDevDamageActor::BeginPlay()
{
	Super::BeginPlay();
}
//-------------------------------------------------------------------------------------------------------------
