// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VSBaseProjectile.h"
#include "VSMagicProjectile.generated.h"

/**
 * 
 */
UCLASS()
class VOIDSTAR_API AVSMagicProjectile : public AVSBaseProjectile
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AVSMagicProjectile();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float BaseDamage = -25.f;

	UPROPERTY(EditAnywhere, Category = "Effects")
	TObjectPtr<UParticleSystem> CastMagicProjectile_VFX;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void Explode_Implementation() override;

};