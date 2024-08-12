// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/VSBTService_HealthState.h"
#include "SVAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "AI/SVAICharacter.h"

void UVSBTService_HealthState::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackboardComp))
	{
		if (AAIController* AIOwner = OwnerComp.GetAIOwner())
		{
			if (APawn* AIPawn = AIOwner->GetPawn())
			{
				if (AAICharacter* AICharacter = Cast<AAICharacter>(AIPawn))
				{
						BlackboardComp->SetValueAsBool(DetectLowHealthKey.SelectedKeyName, AICharacter->GetIsLowLife());
				}
			}
		}
	}
}
		
	

