#include "Player/DSCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

//-------------------------------------------------------------------------------------------------------------
ADSCharacter::ADSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Spring_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	Spring_Arm->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Spring_Arm);
	Camera->bUsePawnControlRotation = true;
}
//-------------------------------------------------------------------------------------------------------------
void ADSCharacter::BeginPlay()
{
	Super::BeginPlay();
}
//-------------------------------------------------------------------------------------------------------------
void ADSCharacter::Tick(float delta_time)
{
	Super::Tick(delta_time);
}
//-------------------------------------------------------------------------------------------------------------
void ADSCharacter::SetupPlayerInputComponent(UInputComponent *player_input_component)
{
	Super::SetupPlayerInputComponent(player_input_component);

	player_input_component->BindAxis(TEXT("MoveForward"), this, &ADSCharacter::Move_Forward);
	player_input_component->BindAxis(TEXT("MoveRight"), this, &ADSCharacter::Move_Right);
	player_input_component->BindAxis(TEXT("LookUp"), this, &ADSCharacter::AddControllerPitchInput);
	player_input_component->BindAxis(TEXT("TurnAround"), this, &ADSCharacter::AddControllerYawInput);
}
//-------------------------------------------------------------------------------------------------------------
void ADSCharacter::Move_Forward(float amount)
{
	AddMovementInput(GetActorForwardVector(), amount);
}
//-------------------------------------------------------------------------------------------------------------
void ADSCharacter::Move_Right(float amount)
{
	AddMovementInput(GetActorRightVector(), amount);
}
//-------------------------------------------------------------------------------------------------------------
