// Fill out your copyright notice in the Description page of Project Settings.


#include "SVAttributeComponent.h"

#include "EngineUtils.h"
#include "SVGameModeBase.h"
#include "AI/SVAICharacter.h"

static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("sv.DamageMultiplier"), 1.f, TEXT("Global damage Modifier for Attribute Component."), ECVF_Cheat);

// Sets default values for this component's properties
USVAttributeComponent::USVAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Health = MaxHealth;

}

bool USVAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

bool USVAttributeComponent::IsFullHealth() const
{
	return Health == MaxHealth;
}

bool USVAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{

	if (!GetOwner()->CanBeDamaged())
	{
		return false;
	}

	if (Delta < 0.f)
	{
		float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();

		Delta *= DamageMultiplier;
	}

	float OldHealth = Health;

	Health = FMath::Clamp(Health + Delta, 0.f, MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("Health changed to this value : %f"), Health)

	float ActualDelta = Health - OldHealth;
	OnHealthChanged.Broadcast(InstigatorActor, this, Health, ActualDelta);
	UE_LOG(LogTemp, Warning, TEXT("ActualDelta is : %f"), ActualDelta)

	//Died implementation
	if (ActualDelta < 0.f && Health == 0.f)
	{
		ASVGameModeBase* GM = GetWorld()->GetAuthGameMode<ASVGameModeBase>();
		if (GM)
		{
			GM->OnActorKilled(GetOwner(), InstigatorActor);
		}
	}

	// ActualDelta is 0 if player has no remaining health point
	return ActualDelta != 0;
}

USVAttributeComponent* USVAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<USVAttributeComponent>(FromActor->GetComponentByClass(StaticClass()));
	}
	return nullptr;
}

bool USVAttributeComponent::IsActorAlive(AActor* Actor)
{
	USVAttributeComponent* AttributeComp = GetAttributes(Actor);
	if (AttributeComp)
	{
		return AttributeComp->IsAlive();
	}
	return false;
}

bool USVAttributeComponent::Kill(AActor* InstigatorActor)
{
	return ApplyHealthChange(InstigatorActor, -GetMaxHealth());
}
