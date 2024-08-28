// Fill out your copyright notice in the Description page of Project Settings.


#include "VSBlackholeProjectile.h"

#include "Components/SphereComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

AVSBlackholeProjectile::AVSBlackholeProjectile()
{
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->SetupAttachment(RootComponent);
}

void AVSBlackholeProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AVSBlackholeProjectile::DestroyOnOverlap);
}

void AVSBlackholeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVSBlackholeProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_Blackhole, this, &AVSBlackholeProjectile::HandleDestruction, LifeTime);
}


void AVSBlackholeProjectile::HandleDestruction()
{
	if (this)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_Blackhole);
		Destroy();
	}
}



void AVSBlackholeProjectile::DestroyOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != GetInstigator())
	{
		UE_LOG(LogTemp, Warning, TEXT("OtherActor : %s, has been destroyed"), *GetNameSafe(OtherActor));

		OtherActor->Destroy();
	}
}
