// Fill out your copyright notice in the Description page of Project Settings.


#include "VSMagicProjectile.h"

#include "SVActionComponent.h"
#include "Components/SphereComponent.h"
#include "SVGameplayFunctionLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AVSMagicProjectile::AVSMagicProjectile()
{
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AVSMagicProjectile::OnActorOverlap);

}


void AVSMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{

		USVActionComponent* ActionComp = Cast<USVActionComponent>(OtherActor->GetComponentByClass(USVActionComponent::StaticClass()));
		if (ActionComp && ActionComp->ActiveGameplayTags.HasTag(ParryTag))
		{
			MovementComp->Velocity = -MovementComp->Velocity;

			SetInstigator(Cast<APawn>(OtherActor));
			return;
		}

		if (USVGameplayFunctionLibrary::ApplyDirectionnalDamage(GetInstigator(), OtherActor, BaseDamage, SweepResult))
		{
			UE_LOG(LogTemp, Display, TEXT("%s hit ! Damage inflicted : %f"), *GetNameSafe(OtherActor), BaseDamage)
			Explode();
		}

	}
}
