// Fill out your copyright notice in the Description page of Project Settings.


#include "VSBuffThorn.h"

#include "SVActionComponent.h"
#include "SVAction_Thornbuff.h"

AVSBuffThorn::AVSBuffThorn()
{
	BuffMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	BuffMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BuffMeshComp->SetupAttachment(RootComponent);
}

void AVSBuffThorn::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}

	GrantingBuffAction(InstigatorPawn);

	OnBuffInteraction();

}


void AVSBuffThorn::GrantingBuffAction(APawn* InstigatorPawn)
{
	USVActionComponent* ActionComp = Cast<USVActionComponent>(InstigatorPawn->FindComponentByClass(USVActionComponent::StaticClass()));

	check(ActionComp);

	if (ActionComp->GetAction(ActionToGrant))
	{
		FString DebugMsg = FString::Printf(TEXT("Action '%s' already known."), *GetNameSafe(ActionToGrant));
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, DebugMsg);
		return;
	}

	FString DebugMsg = FString::Printf(TEXT("Action '%s' granted to '%s'."), *GetNameSafe(ActionToGrant), *GetNameSafe(InstigatorPawn));
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, DebugMsg);

	ActionComp->AddAction(InstigatorPawn, ActionToGrant);

}