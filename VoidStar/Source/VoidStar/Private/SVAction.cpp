// Fill out your copyright notice in the Description page of Project Settings.


#include "SVAction.h"

#include "SVActionComponent.h"



bool USVAction::CanStart_Implementation(AActor* Instigator)
{
	if (IsRunning())
	{
		return false;
	}

	USVActionComponent* Comp = GetOwningComponent();

	if (Comp->ActiveGameplayTags.HasAny(BlockedTags))
	{
		return false;
	}

	return true;
}


void USVAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Running: %s"), *GetNameSafe(this))

	USVActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.AppendTags(GrantsTags);

	bIsRunning = true;
}

void USVAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Stopped: %s"), *GetNameSafe(this))

	ensureAlways(bIsRunning);

	USVActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.RemoveTags(GrantsTags);

	bIsRunning = false;
}



UWorld* USVAction::GetWorld() const
{

	// Outer is set when creating action via NewObject<T>

	UActorComponent* Comp = Cast <UActorComponent>(GetOuter());

	if (Comp)
	{
		return Comp->GetWorld();
	}

	return nullptr;
}

USVActionComponent* USVAction::GetOwningComponent() const
{
	return Cast<USVActionComponent>(GetOuter());
}

bool USVAction::IsRunning() const
{
	return bIsRunning;
}
