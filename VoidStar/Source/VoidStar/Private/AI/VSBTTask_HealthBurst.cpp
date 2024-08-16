// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/VSBTTask_HealthBurst.h"
#include "SVAttributeComponent.h"
#include "AIController.h"
#include "AI/SVAICharacter.h"
#include "GameFramework/Character.h"


EBTNodeResult::Type UVSBTTask_HealthBurst::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AAIController* AIOwner = OwnerComp.GetAIOwner())
	{
		if (APawn* AIPawn = AIOwner->GetPawn())
		{
			if (AAICharacter* AICharacter = Cast<AAICharacter>(AIPawn))
			{
				if (USVAttributeComponent* AIAttribute = USVAttributeComponent::GetAttributes(AICharacter))
				{
					UE_LOG(LogTemp, Warning, TEXT("AIAttribute Cast Succeed"))
					AIAttribute->ApplyHealthChange(AIPawn->GetInstigator(), AIAttribute->GetMaxHealth());
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}
