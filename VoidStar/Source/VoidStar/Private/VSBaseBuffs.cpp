// Fill out your copyright notice in the Description page of Project Settings.


#include "VSBaseBuffs.h"
#include "Components/SphereComponent.h"

// Sets default values
AVSBaseBuffs::AVSBaseBuffs()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Buffs");
	RootComponent = SphereComp;


	
}


void AVSBaseBuffs::OnBuffInteraction()
{
		SetBuffState(false);
		GetWorldTimerManager().SetTimer(InactiveBuffDelay_Handle, this, &AVSBaseBuffs::ReactiveBuff, InactiveDelay);
}

void AVSBaseBuffs::ReactiveBuff()
{
	SetBuffState(true);
}

void AVSBaseBuffs::SetBuffState(bool bBuffState)
{

	SetActorEnableCollision(bBuffState);
	RootComponent->SetVisibility(bBuffState, true);
}