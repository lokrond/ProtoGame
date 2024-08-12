// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SVAICharacter.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SVAttributeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AAICharacter::AAICharacter()
{
 
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	AttributeComp = CreateDefaultSubobject<USVAttributeComponent>("AttributeComp");

	ParticleEffectComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleEffectComp");
	ParticleEffectComp->SetupAttachment(GetMesh(), "neck_01");

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->SetupAttachment(RootComponent);
	RadialForceComp->Radius = ExplosionRadius;
	RadialForceComp->bImpulseVelChange = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AAICharacter::OnPawnSeen);
	AttributeComp->OnHealthChanged.AddDynamic(this, &AAICharacter::OnHealthChanged);
}

void AAICharacter::OnHealthChanged(AActor* InstigatorActor, USVAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	
	if (NewHealth <= 25.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Particle effect activate"))
		ParticleEffectComp->Activate();
		SetIsLowLife(true);
	}

	if (Delta < 0.f)
	{
		if (InstigatorActor != this)
		{
			SetTargetActor(InstigatorActor);
		}

		if (NewHealth <= 0.f)
		{
			AAIController* AIC = Cast<AAIController>(GetController());
			if (AIC)
			{
				AIC->GetBrainComponent()->StopLogic("Killed");
			}

			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");
			SetLifeSpan(10.f);
		}
	}

	if (NewHealth > 25.f && ParticleEffectComp->IsActive())
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion_VFX, GetActorLocation(), GetActorRotation());
		RadialForceComp->FireImpulse();
		ParticleEffectComp->Deactivate();
		SetIsLowLife(false);
	}
}

void AAICharacter::SetTargetActor(AActor* NewTarget)
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		AIC->GetBlackboardComponent()->SetValueAsObject("TargetActor", NewTarget);
	}
}
void AAICharacter::OnPawnSeen(APawn* Pawn)
{
	SetTargetActor(Pawn);

	DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER SPOTTED", nullptr, FColor::White, 4.f, true);
}