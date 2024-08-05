// Fill out your copyright notice in the Description page of Project Settings.


#include "VSTargetDummy.h"
#include "SVAttributeComponent.h"

// Sets default values
AVSTargetDummy::AVSTargetDummy()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	AttributeComp = CreateDefaultSubobject<USVAttributeComponent>("AttributeComp");
}

// Called when the game starts or when spawned
void AVSTargetDummy::BeginPlay()
{
	Super::BeginPlay();
	
}

/*void AMjTargetDummy::OnHealthChanged(AActor* InstigatorActor, UMjAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.f)
	{
		SkeletalComp->
	}
}
*/