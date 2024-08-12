// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/VSBTTask_RangeAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Math/UnrealMathUtility.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UVSBTTask_RangeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* RangeAIController = OwnerComp.GetAIOwner();
	if(ensure(RangeAIController))
	{
		ACharacter* RangeAIPawn = Cast<ACharacter>(RangeAIController->GetPawn());
		if (RangeAIPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		FVector MuzzleLocation = RangeAIPawn->GetMesh()->GetSocketLocation("Muzzle_01");

		AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));

		if (TargetActor == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		FVector Direction = TargetActor->GetActorLocation() - MuzzleLocation;
		FRotator MuzzleRotation = Direction.Rotation();
		MuzzleRotation.Yaw += FMath::FRandRange(-3.f, 3.f);
		MuzzleRotation.Pitch += FMath::FRandRange(-3.f, 3.f);
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		Params.Instigator = RangeAIPawn->GetInstigator();

		AActor* NewProj = GetWorld()->SpawnActor<AActor>(RangeProjectileClass, MuzzleLocation, MuzzleRotation, Params);

		return NewProj ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}