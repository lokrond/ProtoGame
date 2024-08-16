// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VSBaseBuffs.h"
#include "VSGameplayInterface.h"
#include "VSCoinBuff.generated.h"

/**
 * 
 */
UCLASS()
class VOIDSTAR_API AVSCoinBuff : public AVSBaseBuffs, public IVSGameplayInterface
{
	GENERATED_BODY()

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

public:

	AVSCoinBuff();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BuffMeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Credit")
	int32 CreditAmount;

};
