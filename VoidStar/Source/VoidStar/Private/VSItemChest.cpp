// Fill out your copyright notice in the Description page of Project Settings.


#include "VSItemChest.h"

// Sets default values
AVSItemChest::AVSItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);

}

// Called when the game starts or when spawned
void AVSItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVSItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

