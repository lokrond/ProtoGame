// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VSBaseBuffs.generated.h"

class USphereComponent;

UCLASS()
class VOIDSTAR_API AVSBaseBuffs : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVSBaseBuffs();

protected:

	FTimerHandle InactiveBuffDelay_Handle;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USphereComponent> SphereComp;

	UPROPERTY(EditAnywhere, Category = "Buffs")
	float InactiveDelay = 10.f;

	void ReactiveBuff();
	void SetBuffState(bool bBuffState);

	void OnBuffInteraction();

};