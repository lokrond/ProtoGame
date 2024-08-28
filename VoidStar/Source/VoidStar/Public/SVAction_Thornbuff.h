// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SVActionEffect.h"
#include "SVAction_Thornbuff.generated.h"

/**
 * 
 */
UCLASS()
class VOIDSTAR_API USVAction_Thornbuff : public USVActionEffect
{
	GENERATED_BODY()

public:

	USVAction_Thornbuff();

	void StartAction_Implementation(AActor* Instigator) override;

	void StopAction_Implementation(AActor* Instigator) override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect")
	float ReflectFraction;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USVAttributeComponent* OwningComp, float NewValue, float Delta);

};
