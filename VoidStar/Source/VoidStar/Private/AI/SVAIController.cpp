// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SVAIController.h"


void ASVAIController::BeginPlay()
{
	Super::BeginPlay();

	if(ensureMsgf(BehaviorTree, TEXT("BehaviorTree is nullptr! Assign BehaviorTree in AI Controller")))
	{
		RunBehaviorTree(BehaviorTree);
	}
}