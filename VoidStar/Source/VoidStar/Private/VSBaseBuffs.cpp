// Fill out your copyright notice in the Description page of Project Settings.


#include "VSBaseBuffs.h"

// Sets default values
AVSBaseBuffs::AVSBaseBuffs()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PotionMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("PotionMeshComp");
	RootComponent = PotionMeshComp;
}

// Called when the game starts or when spawned
void AVSBaseBuffs::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVSBaseBuffs::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVSBaseBuffs::OnBuffInteraction()
{
	if (bIsBuffActive)
	{
		SetActorHiddenInGame(true);
		bIsBuffActive = false;
		GetWorldTimerManager().SetTimer(InactiveBuffDelay_Handle, this, &AVSBaseBuffs::ReactiveBuff, InactiveDelay);
	}
}

void AVSBaseBuffs::ReactiveBuff()
{
	SetActorHiddenInGame(false);
	bIsBuffActive = true;
}