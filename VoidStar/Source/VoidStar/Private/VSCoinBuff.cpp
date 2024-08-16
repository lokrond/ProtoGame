// Fill out your copyright notice in the Description page of Project Settings.


#include "VSCoinBuff.h"
#include "SVPlayerState.h"

AVSCoinBuff::AVSCoinBuff()
{
	BuffMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("BuffMeshComp");
	BuffMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BuffMeshComp->SetupAttachment(RootComponent);

	CreditAmount = 50;
}

void AVSCoinBuff::Interact_Implementation(APawn* InstigatorPawn)
{

	if (!ensure(InstigatorPawn))
	{
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("CoinBuff interact called"))

	if (ASVPlayerState* LocalPlayerState = InstigatorPawn->GetPlayerState<ASVPlayerState>())
	{
		UE_LOG(LogTemp, Warning, TEXT("CoinBuff credit score called"))
		LocalPlayerState->AddCreditScore(CreditAmount);
		OnBuffInteraction();
	}
}