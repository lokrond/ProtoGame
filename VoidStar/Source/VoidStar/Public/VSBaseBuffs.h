// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SVAttributeComponent.h"
#include "VSGameplayInterface.h"
#include "VSBaseBuffs.generated.h"

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
	TObjectPtr<UStaticMeshComponent> PotionMeshComp;

	UPROPERTY(EditAnywhere, Category = "Buffs")
	float InactiveDelay = 10.f;

	bool bIsBuffActive = true;

	void ReactiveBuff();

	void OnBuffInteraction();

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

};