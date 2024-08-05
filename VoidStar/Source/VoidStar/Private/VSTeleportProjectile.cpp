// Fill out your copyright notice in the Description page of Project Settings.


#include "VSTeleportProjectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AVSTeleportProjectile::AVSTeleportProjectile()
{
	MovementComp->InitialSpeed = 3000.f;
}

void AVSTeleportProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AMjTeleportProjectile::Explode_Implementation);
}

void AVSTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_TravelTime, this, &AVSTeleportProjectile::Explode, DelayTravelTime);
}

void AVSTeleportProjectile::Explode_Implementation()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_TravelTime);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactVFX, GetActorLocation(), GetActorRotation());

	EffectComp->DeactivateSystem();
	MovementComp->StopMovementImmediately();
	SetActorEnableCollision(false);

	FTimerHandle TimerHandle_Teleport;
	GetWorldTimerManager().SetTimer(TimerHandle_Teleport, this, &AVSTeleportProjectile::TeleportInstigator, DelayTimerTP);

	// Skip base implementation to prevent Destroy() being called on this implementation (don't call Super)
	// Super::Explode_Implementation 
}

void AVSTeleportProjectile::TeleportInstigator()
{
	AActor* ActorToTeleport = GetInstigator();
	if (ensure(ActorToTeleport))
	{
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);
	}



}
