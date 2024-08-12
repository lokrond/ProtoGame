// Fill out your copyright notice in the Description page of Project Settings.


#include "SVAttributeComponent.h"

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
	float OldHealth = Health;

	Health = FMath::Clamp(Health + Delta, 0.f, MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("Health changed to this value : %f"), Health)

	float ActualDelta = Health - OldHealth;
	OnHealthChanged.Broadcast(InstigatorActor, this, Health, ActualDelta);
	UE_LOG(LogTemp, Warning, TEXT("ActualDelta is : %f"), ActualDelta)

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
