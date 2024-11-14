#include "Weapon/DSProjectile.h"
#include "Components/SphereComponent.h"

//-------------------------------------------------------------------------------------------------------------
ADSProjectile::ADSProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	Component_Collision = CreateDefaultSubobject<USphereComponent>("Component_Collision");
	Component_Collision->SetSphereRadius(3.0f);
	SetRootComponent(Component_Collision);
}
//-------------------------------------------------------------------------------------------------------------
void ADSProjectile::BeginPlay()
{
	Super::BeginPlay();
}
//-------------------------------------------------------------------------------------------------------------
