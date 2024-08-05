// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VSBaseProjectile.h"
#include "VSBlackholeProjectile.generated.h"

class URadialForceComponent;

/**
 * 
 */
UCLASS()
class VOIDSTAR_API AVSBlackholeProjectile : public AVSBaseProjectile
{
	GENERATED_BODY()

public:

	AVSBlackholeProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	FTimerHandle TimerHandle_Blackhole;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	URadialForceComponent* RadialForceComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float LifeTime = 5.f;

	UFUNCTION()
	void DestroyOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void PostInitializeComponents() override;

	void HandleDestruction();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};