#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DSPlayerHudWidget.generated.h"

//-------------------------------------------------------------------------------------------------------------
UCLASS()
class DEMOSHOOTER_API UDSPlayerHudWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "UI") float Get_Health_Percent() const;
};
//-------------------------------------------------------------------------------------------------------------
