// Fill out your copyright notice in the Description page of Project Settings.


#include "VSItemChest.h"

// Sets default values
AVSItemChest::AVSItemChest()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);
}

