// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "GameFramework/GameModeBase.h"
#include "SVGameModeBase.generated.h"

class AVSCharacter;
class UEnvQueryInstanceBlueprintWrapper;
class UEnvQuery;
class UCurveFloat;

/**
 * 
 */
UCLASS()
class VOIDSTAR_API ASVGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TSubclassOf<AActor> MinionClass;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UEnvQuery> SpawnBotQuery;

	UPROPERTY(EditDefaultsOnly, Category = "Buffs")
	TObjectPtr<UEnvQuery> SpawnBuffQuery;

	UPROPERTY(EditDefaultsOnly, Category = "Buffs")
	TArray<TSubclassOf<AActor>> BuffClasses;
	
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UCurveFloat> DifficultyCurve;



	FTimerHandle TimerHandle_SpawnMinions;

	FTimerHandle TimerHandle_SpawnBuffs;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float SpawnTimerInterval;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	float RespawnDelay;

	UPROPERTY(EditDefaultsOnly, Category = "Buffs")
	int32 CreditKillReward;

	UPROPERTY(EditDefaultsOnly, Category = "Buffs")
	int32 DesiredBuffCount;

	UPROPERTY(EditDefaultsOnly, Category = "Buff")
	FVector SpawnBuffsOffset = FVector::ZeroVector;

	UPROPERTY(EditDefaultsOnly, Category = "Buff")
	bool bUsingGridQuery = true;

	UPROPERTY(EditDefaultsOnly, Category = "Buffs")
	float RequiredBuffDistance;

	UFUNCTION()
	void SpawnBotTimerElapsed();

	UFUNCTION()
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UFUNCTION()
	void OnBuffQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UFUNCTION()
	void RespawnPlayerElapsed(AController* Controller);

public:

	virtual void OnActorKilled(AActor* VictimActor, AActor* Killer);

	UFUNCTION(Exec)
	void KillAll();

	ASVGameModeBase();

	virtual void StartPlay() override;
};
