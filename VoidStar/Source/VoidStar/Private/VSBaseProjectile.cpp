// Fill out your copyright notice in the Description page of Project Settings.


#include "VSBaseProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AVSBaseProjectile::AVSBaseProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentHit.AddDynamic(this, &AVSBaseProjectile::OnActorHit);
	RootComponent = SphereComp;

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComp");
	MovementComp->InitialSpeed = 2000.f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->ProjectileGravityScale = 0.f;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectsComp");
	EffectComp->SetupAttachment(RootComponent);

	ProjectileTravel_Audio = CreateDefaultSubobject<UAudioComponent>("ProjectileTravelAudioComp");
	ProjectileTravel_Audio->SetupAttachment(RootComponent);
}

void AVSBaseProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

void AVSBaseProjectile::Explode_Implementation()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
	UGameplayStatics::PlaySoundAtLocation(this, Impact_Audio, GetActorLocation(), GetActorRotation());
	UGameplayStatics::PlayWorldCameraShake(this, HitCameraShake, GetActorLocation(), 30.f, 1500.f, 1, true);

	Destroy();
}

void AVSBaseProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
}