// Fill out your copyright notice in the Description page of Project Settings.


#include "VSHealBuff.h"
#include "SVAttributeComponent.h"

// Sets default values
AVSHealBuff::AVSHealBuff()
{

}

void AVSHealBuff::Interact_Implementation(APawn* InstigatorPawn, UActorComponent* OwnerAttribute)
{
	USVAttributeComponent* OwnerHp = Cast<USVAttributeComponent>(OwnerAttribute);
	float CurrentHitPoint = OwnerHp->GetHealth();
	float MaxHitPoint = OwnerHp->MaxHealth;
	if (OwnerHp && CurrentHitPoint < MaxHitPoint)
	{
		OwnerHp->ApplyHealthChange(HealValue);
		OnBuffInteraction();
	}
}
