// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/Character.h"
#include "VSCharacter.generated.h"

class USVActionComponent;
class USVAttributeComponent;
class UParticleSystemComponent;
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



protected:

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName EffectOnHitParamName;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName EffectOnParryParamName;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USVInteractionComponent> InteractionComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USVAttributeComponent> AttributeComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USVActionComponent> ActionComp;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* ParryAction;

	void ShootPrimaryAttack(const FInputActionInstance& Instance);
	void ShootUltimateAttack(const FInputActionInstance& Instance);
	void ShootTeleportProjectile(const FInputActionInstance& Instance);

	void Parry(const FInputActionInstance& Instance);;

	void LookMouse(const FInputActionValue& InputValue);
	void Move(const FInputActionInstance& Instance);

	void SprintStart();
	void SprintStop();

	void FaceOnAction();

	void PrimaryInteract();

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USVAttributeComponent* OwningComp, float NewHealth, float Delta);

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual FVector GetPawnViewLocation() const override;

public:

	AVSCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Exec)
	void HealSelf(float Amount = 100);
};