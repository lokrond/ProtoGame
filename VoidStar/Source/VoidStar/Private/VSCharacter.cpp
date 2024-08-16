// Fill out your copyright notice in the Description page of Project Settings.

#include "VSCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "SVActionComponent.h"
#include "SVAttributeComponent.h"
#include "SVInteractionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AVSCharacter::AVSCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractionComp = CreateDefaultSubobject<USVInteractionComponent>("InteractionComp");

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	AttributeComp = CreateDefaultSubobject<USVAttributeComponent>("AttributeComp");

	ActionComp = CreateDefaultSubobject<USVActionComponent>("ActionComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	EffectOnHitParamName = "HitFlashTime";
	EffectOnParryParamName = "ParryFlashTime";
}

void AVSCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this, &AVSCharacter::OnHealthChanged);
}

// Called when the game starts or when spawned
void AVSCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
}

FVector AVSCharacter::GetPawnViewLocation() const
{
	return CameraComp->GetComponentLocation();
}


// Called to bind functionality to input
void AVSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AVSCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AVSCharacter::LookMouse);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);

		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AVSCharacter::SprintStart);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AVSCharacter::SprintStop);

		EnhancedInputComponent->BindAction(PrimaryAttack, ETriggerEvent::Triggered, this, &AVSCharacter::ShootPrimaryAttack);
		EnhancedInputComponent->BindAction(TeleportAction, ETriggerEvent::Triggered, this, &AVSCharacter::ShootTeleportProjectile);
		EnhancedInputComponent->BindAction(UltimateAttack, ETriggerEvent::Triggered, this, &AVSCharacter::ShootUltimateAttack);

		EnhancedInputComponent->BindAction(ParryAction, ETriggerEvent::Triggered, this, &AVSCharacter::Parry);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AVSCharacter::PrimaryInteract);

	}
}

void AVSCharacter::HealSelf(float Amount)
{
	AttributeComp->ApplyHealthChange(this, Amount);
}

void AVSCharacter::Move(const FInputActionInstance& Instance)
{
	const FVector2D AxisValue = Instance.GetValue().Get<FVector2D>();
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0;
	ControlRot.Roll = 0;

	if (AxisValue.X != 0)
	{
		AddMovementInput(ControlRot.Vector(), AxisValue.X);
	}
	if (AxisValue.Y != 0)
	{
		// GetRightVector() is an existing function doing the same as this line.
		const FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
		AddMovementInput(RightVector, AxisValue.Y);
	}
}

void AVSCharacter::FaceOnAction()
{
	FRotator ControlRot = GetControlRotation();
	FRotator UpdatedRot(0, ControlRot.Yaw, 0);
	SetActorRotation(UpdatedRot);
}

void AVSCharacter::LookMouse(const FInputActionValue& InputValue)
{
	const FVector2D AxisValue = InputValue.Get<FVector2D>();

	if (AxisValue.Y != 0)
	{
		AddControllerPitchInput(AxisValue.Y);
	}
	if (AxisValue.X != 0)
	{
		AddControllerYawInput(AxisValue.X);
	}
}

void AVSCharacter::SprintStart()
{
	ActionComp->StartActionByName(this, "SprintAction");
}

void AVSCharacter::SprintStop()
{
	ActionComp->StopActionByName(this, "SprintAction");
}

void AVSCharacter::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
		UE_LOG(LogTemp, Warning, TEXT("Interact Called"))
	}
}


void AVSCharacter::ShootPrimaryAttack(const FInputActionInstance& Instance)
{
	FaceOnAction();
	ActionComp->StartActionByName(this, "PrimaryAttackAction");
}

void AVSCharacter::ShootUltimateAttack(const FInputActionInstance& Instance)
{
	FaceOnAction();
	ActionComp->StartActionByName(this, "UltimateAttackAction");
}

void AVSCharacter::ShootTeleportProjectile(const FInputActionInstance& Instance)
{
	FaceOnAction();
	ActionComp->StartActionByName(this, "TeleportAction");
}

void AVSCharacter::Parry(const FInputActionInstance& Instance)
{
	ActionComp->StartActionByName(this, "ParryAction");
	GetMesh()->SetScalarParameterValueOnMaterials(EffectOnParryParamName, GetWorld()->TimeSeconds);
}

void AVSCharacter::OnHealthChanged(AActor* InstigatorActor, USVAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.f)
	{
		GetMesh()->SetScalarParameterValueOnMaterials(EffectOnHitParamName, GetWorld()->TimeSeconds);
	}
	if (NewHealth <= 0.f && Delta < 0.f)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
}