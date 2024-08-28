// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SVAction_ProjectileAttack.h"
#include "SVAction_UltimateAttack.generated.h"

/**
 * 
 */
UCLASS()
class VOIDSTAR_API USVAction_UltimateAttack : public USVAction_ProjectileAttack
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float UltimateCost;

public:

	USVAction_UltimateAttack();

	virtual bool CanStart_Implementation(AActor* Instigator) override;

	virtual void StartAction_Implementation(AActor* Instigator) override;
};
