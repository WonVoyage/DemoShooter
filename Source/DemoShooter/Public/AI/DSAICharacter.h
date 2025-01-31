#pragma once

#include "CoreMinimal.h"
#include "Player/DSCharacter.h"
#include "DSAICharacter.generated.h"

class UBehaviorTree;

//-------------------------------------------------------------------------------------------------------------
UCLASS()
class DEMOSHOOTER_API ADSAICharacter : public ADSCharacter
{
	GENERATED_BODY()
	
public:
	ADSAICharacter(const FObjectInitializer &obj_init);

	virtual void On_Death() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI") UBehaviorTree *Tree = 0;
};
//-------------------------------------------------------------------------------------------------------------
