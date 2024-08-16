// Fill out your copyright notice in the Description page of Project Settings.


#include "SVActionComponent.h"

#include "SVAction.h"

USVActionComponent::USVActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void USVActionComponent::BeginPlay()
{
	Super::BeginPlay();

	for (TSubclassOf<USVAction> ActionClass : DefaultActions)
	{
		AddAction(ActionClass);
	}
}

void USVActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FString DebugMsg = GetNameSafe(GetOwner()) + " : " + ActiveGameplayTags.ToStringSimple();
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, DebugMsg);
}

void USVActionComponent::AddAction(TSubclassOf<USVAction> ActionClass)
{
	if (!ensure(ActionClass))
	{
		return;
	}

	USVAction* NewAction = NewObject<USVAction>(this, ActionClass);
	if (ensure(NewAction))
	{
		Actions.Add(NewAction);
	}
}

bool USVActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
	for (USVAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (!Action->CanStart(Instigator))
			{
				FString FailedMsg = FString::Printf(TEXT("Failed to run: %s"), *ActionName.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FailedMsg);
				continue;
			}

			Action->StartAction(Instigator);
			return true;
		}
	}

	return false;
}

bool USVActionComponent::StopActionByName(AActor* Instigator, FName ActionName)
{
	for (USVAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (Action->IsRunning())
			{
				Action->StopAction(Instigator);
				return true;
			}
		}
	}

	return false;
}


