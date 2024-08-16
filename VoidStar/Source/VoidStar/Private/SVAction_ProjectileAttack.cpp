// Fill out your copyright notice in the Description page of Project Settings.


#include "SVAction_ProjectileAttack.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


USVAction_ProjectileAttack::USVAction_ProjectileAttack()
{
	HandSocketName = "Muzzle_01";
	AttackAnimDelay = 0.2f;

}


void USVAction_ProjectileAttack::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	ACharacter* Character = Cast<ACharacter>(Instigator);

	if (Character)
	{
		Character->PlayAnimMontage(AttackAnim);

		UGameplayStatics::SpawnEmitterAttached(CastingEffect, Character->GetMesh(), HandSocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget);

		FTimerHandle TimerHandle_AttackDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "AttackDelay_Elapsed", Character);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay, Delegate, AttackAnimDelay, false);
	}
}


void USVAction_ProjectileAttack::AttackDelay_Elapsed(ACharacter* InstigatorCharacter)
{
	if (ensureAlways(ProjectileClass))
	{
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(InstigatorCharacter);

		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);

		FCollisionShape Shape;
		Shape.SetSphere(20.f);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = InstigatorCharacter;

		FHitResult Hit;

		FRotator CameraRotation = InstigatorCharacter->GetControlRotation();
		FVector HandLocation = InstigatorCharacter->GetMesh()->GetSocketLocation("Muzzle_01");
		FVector StartSweep = InstigatorCharacter->GetPawnViewLocation();
		FVector EndSweep = StartSweep + CameraRotation.Vector() * 5000;

		if (GetWorld()->SweepSingleByObjectType(Hit, StartSweep, EndSweep, FQuat::Identity, ObjParams, Shape, QueryParams))
		{
			//Overwrite EndSweep in case the Sweep detect an object to calculate the optimal rotation based on this updated EndSweep
			EndSweep - Hit.ImpactPoint;
		}

		FRotator OptimalRotation = FRotationMatrix::MakeFromX(EndSweep - HandLocation).Rotator();
		FTransform SpawnTransform = FTransform(OptimalRotation, HandLocation);

		/*if (ProjectileClass == BlackholeProjectileClass)
		{
			SpawnTransform = FTransform(CameraRotation, HandLocation);
		}*/

		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransform, SpawnParams);
	}
	StopAction(InstigatorCharacter);
}
