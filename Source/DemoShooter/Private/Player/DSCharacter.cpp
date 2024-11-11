#include "Player/DSCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/DSCharacterMovementComponent.h"
#include "Components/DSHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Weapon/DSBaseWeapon.h"
#include "Components/DSWeaponComponent.h"

//-------------------------------------------------------------------------------------------------------------
ADSCharacter::ADSCharacter(const FObjectInitializer &object_init)
	: Super(object_init.SetDefaultSubobjectClass<UDSCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	Component_SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	Component_SpringArm->SetupAttachment(GetRootComponent());

	Component_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Component_Camera"));
	Component_Camera->SetupAttachment(Component_SpringArm);
	Component_Camera->bUsePawnControlRotation = true;

	Component_Health = CreateDefaultSubobject<UDSHealthComponent>(TEXT("Health Component"));
	Component_Health->OnDeath.AddUObject(this, &ADSCharacter::On_Death);
	
	Component_Health_Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Health Text Component"));
	Component_Health_Text->SetupAttachment(GetRootComponent());

	Component_Weapon = CreateDefaultSubobject<UDSWeaponComponent>(TEXT("Weapon Component"));
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

	float health = Component_Health->Get_Health();

	Component_Health_Text->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), health)));
}
//-------------------------------------------------------------------------------------------------------------
void ADSCharacter::SetupPlayerInputComponent(UInputComponent *player_input_component)
{
	Super::SetupPlayerInputComponent(player_input_component);

	player_input_component->BindAxis(TEXT("MoveForward"), this, &ADSCharacter::Move_Forward);
	player_input_component->BindAxis(TEXT("MoveRight"), this, &ADSCharacter::Move_Right);
	player_input_component->BindAxis(TEXT("LookUp"), this, &ADSCharacter::AddControllerPitchInput);
	player_input_component->BindAxis(TEXT("TurnAround"), this, &ADSCharacter::AddControllerYawInput);
	player_input_component->BindAction(TEXT("Jump"), IE_Pressed, this, &ADSCharacter::Jump);
	player_input_component->BindAction(TEXT("Run"), IE_Pressed, this, &ADSCharacter::On_Run_Start);
	player_input_component->BindAction(TEXT("Run"), IE_Released, this, &ADSCharacter::On_Run_End);
	player_input_component->BindAction(TEXT("Fire"), IE_Pressed, Component_Weapon, &UDSWeaponComponent::Fire);
}
//-------------------------------------------------------------------------------------------------------------
bool ADSCharacter::Is_Running() const
{
	return Wants_To_Run && Is_Moving_Forward && !GetVelocity().IsZero();
}
//-------------------------------------------------------------------------------------------------------------
void ADSCharacter::On_Death()
{
	PlayAnimMontage(AnimMontage_Death);
	GetMovementComponent()->StopMovementImmediately();

	SetLifeSpan(5.0f);
}
//-------------------------------------------------------------------------------------------------------------
void ADSCharacter::Move_Forward(float amount)
{
	Is_Moving_Forward = amount > 0.0f;
	AddMovementInput(GetActorForwardVector(), amount);
}
//-------------------------------------------------------------------------------------------------------------
void ADSCharacter::Move_Right(float amount)
{
	AddMovementInput(GetActorRightVector(), amount);
}
//-------------------------------------------------------------------------------------------------------------
void ADSCharacter::On_Run_Start()
{
	Wants_To_Run = true;
}
//-------------------------------------------------------------------------------------------------------------
void ADSCharacter::On_Run_End()
{
	Wants_To_Run = false;
}
//-------------------------------------------------------------------------------------------------------------
