// Fill out your copyright notice in the Description page of Project Settings.


#include "SVGameModeBase.h"

#include "EngineUtils.h"
#include "SVAttributeComponent.h"
#include "AI/SVAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "DrawDebugHelpers.h"

ASVGameModeBase::ASVGameModeBase()
{
	SpawnTimerInterval = 2.f;
}

void ASVGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnMinions, this, &ASVGameModeBase::SpawnBotTimerElapsed, SpawnTimerInterval, true);
}

void ASVGameModeBase::SpawnBotTimerElapsed()
{
	int32 NbOfActiveBots = 0;
	for (TActorIterator<AAICharacter> It(GetWorld()); It; ++It)
	{
		AAICharacter* Bot = *It;

		USVAttributeComponent* AttributeComp = USVAttributeComponent::GetAttributes(Bot);
		if (AttributeComp && AttributeComp->IsAlive())
		{
			NbOfActiveBots++;
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Found %i bots alive."), NbOfActiveBots)

		float MaxBotCount = 10.f;

	if (DifficultyCurve)
	{
		MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}

	if (NbOfActiveBots >= MaxBotCount)
	{
		UE_LOG(LogTemp, Log, TEXT("Spawn capacity full. Skipping spawn."))
			return;
	}

	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);
	if (ensure(QueryInstance))
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ASVGameModeBase::OnQueryCompleted);

	}
}

void ASVGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn bot EQS Query failed!"))
			return;
	}


	TArray<FVector> Locations;
	QueryInstance->GetQueryResultsAsLocations(Locations);

	if (Locations.IsValidIndex(0))
	{
		GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0], FRotator::ZeroRotator);

		DrawDebugSphere(GetWorld(), Locations[0], 50.f, 20, FColor::Purple, false, 20.f);
	}
}
