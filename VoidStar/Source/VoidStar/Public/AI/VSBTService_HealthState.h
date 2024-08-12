// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "VSBTService_HealthState.generated.h"

class USVAttributeComponent;
/**
 * 
 */
UCLASS()
class VOIDSTAR_API UVSBTService_HealthState : public UBTService
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector DetectLowHealthKey;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	bool bActorLowHealth = false;

	TSubclassOf<USVAttributeComponent> AttributeClass;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
