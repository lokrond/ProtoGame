// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SVAICharacter.generated.h"

class USVAttributeComponent;
class UPawnSensingComponent;
class URadialForceComponent;
class UParticleSystemComponent;
class UUserWidget;
class USVWorldUserWidget;
class USVActionComponent;

UCLASS()
class VOIDSTAR_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AAICharacter();

	bool GetIsLowLife() { return bIsLowLife; }
	void SetIsLowLife(bool bHasLowLife) { bIsLowLife = bHasLowLife; }

protected:

	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName HitFlashParamName;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	FName TargetActorKey;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<USVWorldUserWidget> SpottedWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	TObjectPtr<USVWorldUserWidget> ActiveHealthBar;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> HealthBarWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UPawnSensingComponent> PawnSensingComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<URadialForceComponent> RadialForceComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USVAttributeComponent> AttributeComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UParticleSystemComponent> ParticleEffectComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USVActionComponent> ActionComp;

	UPROPERTY(EditAnywhere, Category = "Effects")
	TObjectPtr<UParticleSystem> Explosion_VFX;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USVAttributeComponent* OwningComp, float NewValue, float Delta);


	void SetTargetActor(AActor* NewTarget);

	AActor* GetTargetActor() const;

	bool bIsLowLife = false;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ExplosionRadius = 500.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ExplosionDamage = 25.f;
};
