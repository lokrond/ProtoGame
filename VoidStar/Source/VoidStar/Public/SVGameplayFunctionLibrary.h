// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SVGameplayFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class VOIDSTAR_API USVGameplayFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	static bool ApplyDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	static bool ApplyDirectionnalDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount, const FHitResult& HitResult);
	
};
