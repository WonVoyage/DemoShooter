#include "Animations/DSAnimNotify.h"

//-------------------------------------------------------------------------------------------------------------
void UDSAnimNotify::Notify(USkeletalMeshComponent* mesh_component, UAnimSequenceBase* animation)
{
	OnNotified.Broadcast(mesh_component);
	Super::Notify(mesh_component, animation);
}
//-------------------------------------------------------------------------------------------------------------
