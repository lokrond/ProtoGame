// Fill out your copyright notice in the Description page of Project Settings.


#include "SVGameModeBase.h"

#include "EngineUtils.h"
#include "SVAttributeComponent.h"
#include "AI/SVAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "DrawDebugHelpers.h"
#include "VSCharacter.h"
#include "SVPlayerState.h"
#include "TimerManager.h"


static TAutoConsoleVariable<bool> CVarSpawnBots(TEXT("sv.SpawnBots"), true, TEXT("Enable spawning of bots via timer."), ECVF_Cheat);


ASVGameModeBase::ASVGameModeBase()
{
	SpawnTimerInterval = 2.f;
	RespawnDelay = 2.f;

	CreditKillReward = 10;

	RequiredBuffDistance = 2000.f;
	DesiredBuffCount = 10;
	SpawnBuffsOffset.Z = 50.f;

}

void ASVGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnMinions, this, &ASVGameModeBase::SpawnBotTimerElapsed, SpawnTimerInterval, true);

	UEnvQueryInstanceBlueprintWrapper* QueryBuffInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBuffQuery, this, EEnvQueryRunMode::AllMatching, nullptr);
	if (ensure(QueryBuffInstance))
	{
		QueryBuffInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ASVGameModeBase::OnBuffQueryCompleted);

	}
}

void ASVGameModeBase::KillAll()
{
	for (TActorIterator<AAICharacter> It(GetWorld()); It; ++It)
	{
		AAICharacter* Bot = *It;

		USVAttributeComponent* AttributeComp = USVAttributeComponent::GetAttributes(Bot);

		if (AttributeComp && AttributeComp->IsAlive())
		{

			AttributeComp->Kill(this);

			for (TActorIterator<AVSCharacter> PlayerIt(GetWorld()); PlayerIt; ++PlayerIt)
			{
				AVSCharacter* Player = *PlayerIt;
				Player->GetPlayerState<ASVPlayerState>()->AddCreditScore(10);
			}
		}
	}
}

void ASVGameModeBase::SpawnBotTimerElapsed()
{
	if (!CVarSpawnBots.GetValueOnGameThread())
	{
		UE_LOG(LogTemp, Warning, TEXT("Bot spawning disabled via cvar 'CVarSpawnBots'."))
		return;
	}

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

void ASVGameModeBase::OnBuffQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		return;
	}

	TArray<FVector> Locations;
	QueryInstance->GetQueryResultsAsLocations(Locations);

	

	if (bUsingGridQuery)
	{
		TArray<FVector> UsedLocations;
		int32 SpawnCounter = 0;

		while (SpawnCounter < DesiredBuffCount && Locations.Num() > 0)
		{
			int32 RandomLocationIndex = FMath::RandRange(0, Locations.Num() - 1);

			FVector PickedLocation = Locations[RandomLocationIndex];
			Locations.RemoveAt(RandomLocationIndex);

			bool bValidLocation = true;
			for (FVector OtherLocation : UsedLocations)
			{
				float DistanceTo = (PickedLocation - OtherLocation).Size();

				if (DistanceTo < RequiredBuffDistance)
				{
					bValidLocation = false;
					break;
				}
			}

			if (!bValidLocation)
			{
				continue;
			}

			int32 RandomClassIndex = FMath::RandRange(0, BuffClasses.Num() - 1);
			TSubclassOf<AActor> RandomBuffClass = BuffClasses[RandomClassIndex];

			GetWorld()->SpawnActor<AActor>(RandomBuffClass, PickedLocation + SpawnBuffsOffset, FRotator::ZeroRotator);
			DrawDebugSphere(GetWorld(), PickedLocation + SpawnBuffsOffset, 50.f, 20, FColor::Purple, false, 20.f);

			UsedLocations.Add(PickedLocation);
			SpawnCounter++;
		}
	}
	else
	{
		// This part is would be use to spawn buff on specific locations when using proper query
		for (FVector Location : Locations)
		{
		int32 RandomClassIndex = FMath::RandRange(0, BuffClasses.Num() - 1);
		TSubclassOf<AActor> RandomBuffClass = BuffClasses[RandomClassIndex];

		GetWorld()->SpawnActor<AActor>(RandomBuffClass, Location, FRotator::ZeroRotator);
		DrawDebugSphere(GetWorld(), Location, 50.f, 20, FColor::Purple, false, 20.f);
		}	
	}
}

void ASVGameModeBase::RespawnPlayerElapsed(AController* Controller)
{
	if (ensure(Controller))
	{
		Controller->UnPossess();

		RestartPlayer(Controller);
	}
}

void ASVGameModeBase::OnActorKilled(AActor* VictimActor, AActor* Killer)
{
	if (AVSCharacter* Player = Cast<AVSCharacter>(VictimActor))
	{
		FTimerHandle TimerHandle_RespawnDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "RespawnPlayerElapsed", Player->GetController());
		GetWorldTimerManager().SetTimer(TimerHandle_RespawnDelay, Delegate, RespawnDelay, false);

		return;
	}
	AAICharacter* EnemyBot = Cast<AAICharacter>(VictimActor);
	if (EnemyBot)
	{
		ASVPlayerState* LocalPlayerState = Killer->GetInstigatorController()->GetPlayerState<ASVPlayerState>();
		LocalPlayerState->AddCreditScore(CreditKillReward);
	}
}


