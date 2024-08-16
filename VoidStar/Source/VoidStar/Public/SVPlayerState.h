// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SVPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreditsChanged, ASVPlayerState*, PlayerState, int32, NewCredits, int32, Delta);

/**
 * 
 */
UCLASS()
class VOIDSTAR_API ASVPlayerState : public APlayerState
{
	GENERATED_BODY()


protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Credit")
	int32 CreditScore = 0;

public:

	UFUNCTION(BlueprintCallable, Category = "Credit")
	int32 GetCreditScore() const { return CreditScore; }

	UFUNCTION(BlueprintCallable, Category = "Credit")
	void AddCreditScore(int32 Delta);
	UFUNCTION(BlueprintCallable, Category = "Credit")
	bool SubtractCreditScore(int32 Delta);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCreditsChanged OnCreditsChanged;
};
