// Fill out your copyright notice in the Description page of Project Settings.


#include "SVInteractionComponent.h"

#include "VSGameplayInterface.h"
#include "DrawDebugHelpers.h"

static TAutoConsoleVariable<bool> CVarDebugDrawInteraction(TEXT("sv.InteractionDebugDraw"), false, TEXT("Enable Debug Lines for Interact Component."), ECVF_Cheat);

// Sets default values for this component's properties
USVInteractionComponent::USVInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USVInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void USVInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USVInteractionComponent::PrimaryInteract()
{
	bool bDebugDraw = CVarDebugDrawInteraction.GetValueOnGameThread();

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();
	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * 380);

	TArray<FHitResult>  Hits;
	FCollisionShape Shape;
	float Radius = 30.f;
	Shape.SetSphere(Radius);

	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);

	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	for (FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<UVSGameplayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(MyOwner);
				IVSGameplayInterface::Execute_Interact(HitActor, MyPawn);

				if (bDebugDraw)
				{
					DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 16, LineColor, false, 2.f);
				}

				break;
			}
		}
	
	}
	if (bDebugDraw)
	{
		DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.f, 0, 2.f);
	}
}