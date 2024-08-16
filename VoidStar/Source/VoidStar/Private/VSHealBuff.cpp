// Fill out your copyright notice in the Description page of Project Settings.


#include "VSHealBuff.h"
#include "SVAttributeComponent.h"
#include "SVPlayerState.h"

// Sets default values
AVSHealBuff::AVSHealBuff()
{
	BuffMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("BuffMeshComp");
	BuffMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BuffMeshComp->SetupAttachment(RootComponent);

	HealValue = 50;
	HealCreditCost = 50;
}

void AVSHealBuff::Interact_Implementation(APawn* InstigatorPawn)
{

	if (!ensure(InstigatorPawn))
	{
		return;
	}

	USVAttributeComponent* AttributeComp = USVAttributeComponent::GetAttributes(InstigatorPawn);

	UE_LOG(LogTemp, Display, TEXT("HealBuff interact called"))
	if (AttributeComp && !AttributeComp->IsFullHealth())
	{
		if (ASVPlayerState* LocalPlayerState = InstigatorPawn->GetPlayerState<ASVPlayerState>())
		{
			// if statements runs left to right, then CreditCost is check before the health change
			if (LocalPlayerState->SubtractCreditScore(HealCreditCost) && AttributeComp->ApplyHealthChange(this, HealValue))
			{
				UE_LOG(LogTemp, Warning, TEXT("HealBuff healing called"))
				OnBuffInteraction();
			}
		}
	}
}