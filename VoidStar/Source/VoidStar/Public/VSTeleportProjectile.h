// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VSBaseProjectile.h"
#include "VSTeleportProjectile.generated.h"

class UParticleSystemComponent;

/**
 * 
 */
UCLASS()
class VOIDSTAR_API AVSTeleportProjectile : public AVSBaseProjectile
{
	GENERATED_BODY()

public:
	AVSTeleportProjectile();

protected:

	FTimerHandle TimerHandle_TravelTime;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float DelayTimerTP = 0.2f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float DelayTravelTime = 0.4f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float TeleportReach = 600.f;

	FVector TeleportLocation;

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	virtual void Explode_Implementation() override;

	void TeleportInstigator();

};
