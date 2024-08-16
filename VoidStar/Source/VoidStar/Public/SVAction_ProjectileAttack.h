// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SVAction.h"
#include "SVAction_ProjectileAttack.generated.h"

/**
 * 
 */
UCLASS()
class VOIDSTAR_API USVAction_ProjectileAttack : public USVAction
{
	GENERATED_BODY()


protected:

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float AttackAnimDelay;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TObjectPtr<UAnimMontage> AttackAnim;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TObjectPtr<UParticleSystem> CastingEffect;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName HandSocketName;

	UFUNCTION()
	void AttackDelay_Elapsed(ACharacter* InstigatorCharacter);

public:

	virtual void StartAction_Implementation(AActor* Instigator) override;

	USVAction_ProjectileAttack();
};
