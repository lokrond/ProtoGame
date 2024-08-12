// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "SVAICharacter.generated.h"

class USVAttributeComponent;
class UPawnSensingComponent;
class URadialForceComponent;
class UParticleSystemComponent;

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

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UPawnSensingComponent> PawnSensingComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<URadialForceComponent> RadialForceComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USVAttributeComponent> AttributeComp;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	TObjectPtr<UParticleSystemComponent> ParticleEffectComp;

	UPROPERTY(EditAnywhere, Category = "Effects")
	TObjectPtr<UParticleSystem> Explosion_VFX;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USVAttributeComponent* OwningComp, float NewHealth, float Delta);

	void SetTargetActor(AActor* NewTarget);

	bool bIsLowLife = false;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ExplosionRadius = 500.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ExplosionDamage = 25.f;
};
