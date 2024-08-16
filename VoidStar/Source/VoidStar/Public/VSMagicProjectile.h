// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "VSBaseProjectile.h"
#include "VSMagicProjectile.generated.h"

/**
 * 
 */
UCLASS()
class VOIDSTAR_API AVSMagicProjectile : public AVSBaseProjectile
{
	GENERATED_BODY()



protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float BaseDamage = 25.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FGameplayTag ParryTag;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:
	// Sets default values for this actor's properties
	AVSMagicProjectile();

};