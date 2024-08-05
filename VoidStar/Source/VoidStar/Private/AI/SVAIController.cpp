// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SVAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void ASVAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviourTree);

	APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (MyPawn)
	{
		GetBlackboardComponent()->SetValueAsVector("MoveToLocation", MyPawn->GetActorLocation());

		GetBlackboardComponent()->SetValueAsObject("TargetActor", MyPawn);
	}
}