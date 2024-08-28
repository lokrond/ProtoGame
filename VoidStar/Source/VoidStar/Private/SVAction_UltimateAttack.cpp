// Fill out your copyright notice in the Description page of Project Settings.


#include "SVAction_UltimateAttack.h"
#include <SVAttributeComponent.h>
#include "SVActionComponent.h"

USVAction_UltimateAttack::USVAction_UltimateAttack()
{
	UltimateCost = 60.f;
}

bool USVAction_UltimateAttack::CanStart_Implementation(AActor* Instigator)
{
	if (!Instigator && IsRunning())
	{
		return false;
	}

	USVActionComponent* Comp = GetOwningComponent();

	if (Comp->ActiveGameplayTags.HasAny(BlockedTags))
	{
		return false;
	}
	// Super has to be modified in order to avoid repetition

	USVAttributeComponent* AttributeComp = USVAttributeComponent::GetAttributes(Instigator);

	return AttributeComp && AttributeComp->GetEnergy() >= UltimateCost;
	
}

void USVAction_UltimateAttack::StartAction_Implementation(AActor* Instigator)
{
	USVAttributeComponent* AttributeComp = USVAttributeComponent::GetAttributes(Instigator);

	if (Instigator && AttributeComp)
	{
		AttributeComp->ApplyEnergyChanged(Instigator, -UltimateCost);
	}

	Super::StartAction_Implementation(Instigator);
}