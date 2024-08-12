// Fill out your copyright notice in the Description page of Project Settings.


#include "VSHealBuff.h"
#include "SVAttributeComponent.h"


// Sets default values
AVSHealBuff::AVSHealBuff()
{
	BuffMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("BuffMeshComp");
	BuffMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BuffMeshComp->SetupAttachment(RootComponent);
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
		UE_LOG(LogTemp, Warning, TEXT("HealBuff healing called"))

		AttributeComp->ApplyHealthChange(this, HealValue);
		OnBuffInteraction();
	}
}