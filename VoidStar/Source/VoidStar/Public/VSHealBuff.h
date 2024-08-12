// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VSBaseBuffs.h"
#include "VSGameplayInterface.h"
#include "VSHealBuff.generated.h"

/**
 * 
 */
UCLASS()
class VOIDSTAR_API AVSHealBuff : public AVSBaseBuffs, public IVSGameplayInterface
{
	GENERATED_BODY()

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

public:
	// Sets default values for this actor's properties
	AVSHealBuff();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BuffMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buffs")
	float HealValue = 50;

};
