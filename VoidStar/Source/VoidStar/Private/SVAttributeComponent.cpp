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


bool USVAttributeComponent::ApplyHealthChange(float Delta /*AActor* &InstigatorActor*/)
{
	Health += Delta;
	Health = FMath::Clamp(Health, 0.f, 100.f);
	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);
	return true;
}