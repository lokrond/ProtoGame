// Fill out your copyright notice in the Description page of Project Settings.

#include "VSCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "SVAttributeComponent.h"
#include "SVInteractionComponent.h"
#include "VSBlackholeProjectile.h"
#include "VSMagicProjectile.h"
#include "VSTeleportProjectile.h"
#include "GameFramework/CharacterMovementComponent.h"


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

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
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

// Called every frame
void AVSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AVSCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AVSCharacter::LookMouse);
		EnhancedInputComponent->BindAction(PrimaryAttack, ETriggerEvent::Triggered, this, &AVSCharacter::ShootPrimaryAttack);
		EnhancedInputComponent->BindAction(TeleportAction, ETriggerEvent::Triggered, this, &AVSCharacter::ShootTeleportProjectile);
		EnhancedInputComponent->BindAction(UltimateAttack, ETriggerEvent::Triggered, this, &AVSCharacter::ShootUltimateAttack);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AVSCharacter::PrimaryInteract);
	}
}



void AVSCharacter::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
{
	if (ensureAlways(ClassToSpawn))
	{
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);

		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);

		FCollisionShape Shape;
		Shape.SetSphere(20.f);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		FHitResult Hit;

		FRotator CameraRotation = CameraComp->GetComponentRotation();
		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
		FVector StartSweep = CameraComp->GetComponentLocation();
		FVector EndSweep = CameraComp->GetComponentLocation() + CameraRotation.Vector() * 5000;

		if (GetWorld()->SweepSingleByObjectType(Hit, StartSweep, EndSweep, FQuat::Identity, ObjParams, Shape, QueryParams))
		{
			//Overwrite EndSweep in case the Sweep detect an object to calculate the optimal rotation based on this updated EndSweep
			EndSweep - Hit.ImpactPoint;
		}

		FRotator OptimalRotation = FRotationMatrix::MakeFromX(EndSweep - HandLocation).Rotator();
		FTransform SpawnTransform = FTransform(OptimalRotation, HandLocation);

		if (ClassToSpawn == BlackholeProjectileClass)
		{
			SpawnTransform = FTransform(CameraRotation, HandLocation);
		}
		GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTransform, SpawnParams);
	}
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
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(TimerHandle_AttackAnim, this, &AVSCharacter::PrimaryAttack_TimeElapsed, DelayTimer);

}

void AVSCharacter::PrimaryAttack_TimeElapsed()
{
	UE_LOG(LogTemp, Display, TEXT("PrimaryAttack called"))
	SpawnProjectile(MagicProjectileClass);
}


void AVSCharacter::ShootUltimateAttack(const FInputActionInstance& Instance)
{
	FaceOnAction();
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_AttackAnim, this, &AVSCharacter::UltimateAttack_TimeElapsed, DelayTimer);
}

void AVSCharacter::UltimateAttack_TimeElapsed()
{
	SpawnProjectile(BlackholeProjectileClass);
}


void AVSCharacter::ShootTeleportProjectile(const FInputActionInstance& Instance)
{
	FaceOnAction();
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_AttackAnim, this, &AVSCharacter::TeleportProjectile_TimeElapsed, DelayTimer);
}

void AVSCharacter::TeleportProjectile_TimeElapsed()
{
	SpawnProjectile(TeleportProjectileClass);
}


void AVSCharacter::OnHealthChanged(AActor* InstigatorActor, USVAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.f)
	{
		GetMesh()->SetScalarParameterValueOnMaterials("HitFlashTime", GetWorld()->TimeSeconds);
	}
	if (NewHealth <= 0.f && Delta < 0.f)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
	if (NewHealth == 0)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_AttackAnim);
	}
}