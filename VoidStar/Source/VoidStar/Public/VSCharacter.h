// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/Character.h"
#include "VSCharacter.generated.h"

class USVAttributeComponent;
class AVSTeleportProjectile;
class AVSBlackholeProjectile;
class AVSMagicProjectile;
class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
class USVInteractionComponent;
class UAnimMontage;

UCLASS()
class VOIDSTAR_API AVSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVSCharacter();

protected:

	FTimerHandle TimerHandle_AttackAnim;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USVInteractionComponent> InteractionComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USVAttributeComponent* AttributeComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> PlayerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* PrimaryAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* TeleportAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* UltimateAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, Category = "Animation")
	TObjectPtr<UAnimMontage> AttackAnim;

	UPROPERTY(EditAnywhere, Category = "Class")
	TSubclassOf<AVSMagicProjectile> MagicProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Class")
	TSubclassOf<AVSTeleportProjectile> TeleportProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Class")
	TSubclassOf<AVSBlackholeProjectile> BlackholeProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float DelayTimer;

	void Move(const FInputActionInstance& Instance);

	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);
	void ShootPrimaryAttack(const FInputActionInstance& Instance);
	void PrimaryAttack_TimeElapsed();

	void ShootUltimateAttack(const FInputActionInstance& Instance);
	void UltimateAttack_TimeElapsed();

	void ShootTeleportProjectile(const FInputActionInstance& Instance);
	void TeleportProjectile_TimeElapsed();

	void LookMouse(const FInputActionValue& InputValue);
	void FaceOnAction();

	void PrimaryInteract();

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USVAttributeComponent* OwningComp, float NewHealth, float Delta);

	virtual void PostInitializeComponents() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};