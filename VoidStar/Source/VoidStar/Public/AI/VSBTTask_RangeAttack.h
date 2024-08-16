// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "VSBTTask_RangeAttack.generated.h"

/**
 * 
 */
UCLASS()
class VOIDSTAR_API UVSBTTask_RangeAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<AActor> RangeProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float ProjectileSpread;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float ProjectileRecoil;

public:

	UVSBTTask_RangeAttack();
	
};
