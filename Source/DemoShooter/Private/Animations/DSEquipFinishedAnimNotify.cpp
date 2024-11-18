#include "Animations/DSEquipFinishedAnimNotify.h"

//-------------------------------------------------------------------------------------------------------------
void UDSEquipFinishedAnimNotify::Notify(USkeletalMeshComponent *mesh_component, UAnimSequenceBase *animation)
{
	OnNotified.Broadcast(mesh_component);
	Super::Notify(mesh_component, animation);
}
//-------------------------------------------------------------------------------------------------------------
