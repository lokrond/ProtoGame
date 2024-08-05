// Fill out your copyright notice in the Description page of Project Settings.


#include "VSMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "SVAttributeComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AVSMagicProjectile::AVSMagicProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AVSMagicProjectile::OnActorOverlap);

}

// Called when the game starts or when spawned
void AVSMagicProjectile::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::SpawnEmitterAttached(CastMagicProjectile_VFX, SphereComp, "Muzzle_01");
}

// Called every frame
void AVSMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVSMagicProjectile::Explode_Implementation()
{
	Super::Explode_Implementation();
}


void AVSMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		USVAttributeComponent* AttributeComp = Cast<USVAttributeComponent>(OtherActor->GetComponentByClass(USVAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(BaseDamage);
			Explode_Implementation();
		}
	}
}
