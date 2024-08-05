// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VSBaseBuffs.h"
#include "VSHealBuff.generated.h"

/**
 * 
 */
UCLASS()
class VOIDSTAR_API AVSHealBuff : public AVSBaseBuffs
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AVSHealBuff();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buffs")
	float HealValue = 50;

	void Interact_Implementation(APawn* InstigatorPawn, UActorComponent* OwnerAttribute);
};
