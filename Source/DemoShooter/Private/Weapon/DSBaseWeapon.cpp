#include "Weapon/DSBaseWeapon.h"

//-------------------------------------------------------------------------------------------------------------
ADSBaseWeapon::ADSBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMesh_Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));

	SetRootComponent(SkeletalMesh_Weapon);
}
//-------------------------------------------------------------------------------------------------------------
void ADSBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}
//-------------------------------------------------------------------------------------------------------------
void ADSBaseWeapon::Fire()
{
	UE_LOG(LogTemp, Error, TEXT("FIRE!!!!"));
}
//-------------------------------------------------------------------------------------------------------------
