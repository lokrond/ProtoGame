// Fill out your copyright notice in the Description page of Project Settings.


#include "SVAction_Thornbuff.h"

#include "SVActionComponent.h"
#include "SVAttributeComponent.h"
#include "SVGameplayFunctionLibrary.h"

USVAction_Thornbuff::USVAction_Thornbuff()
{
	ReflectFraction = 0.3f;

	Duration = 0.f;
	Period = 0.f;
	
}

void USVAction_Thornbuff::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	UE_LOG(LogTemp, Log, TEXT("Action has been granted with no Duration."))

	USVAttributeComponent* AttributeComp = USVAttributeComponent::GetAttributes(GetOwningComponent()->GetOwner());
	if (AttributeComp)
	{
		UE_LOG(LogTemp, Log, TEXT("Action has accessed Attributes successfully"))
		AttributeComp->OnHealthChanged.AddDynamic(this, &USVAction_Thornbuff::OnHealthChanged);
	}
}

void USVAction_Thornbuff::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);

	USVAttributeComponent* AttributeComp = USVAttributeComponent::GetAttributes(GetOwningComponent()->GetOwner());

	if (AttributeComp)
	{
		AttributeComp->OnHealthChanged.RemoveDynamic(this, &USVAction_Thornbuff::OnHealthChanged);
	}

}

void USVAction_Thornbuff::OnHealthChanged(AActor* InstigatorActor, USVAttributeComponent* OwningComp, float NewValue, float Delta)
{
	AActor* OwningActor = GetOwningComponent()->GetOwner();

	if (Delta < 0.f && OwningActor != InstigatorActor)
	{
		int32 ReflectedAmount = FMath::RoundToInt(Delta * ReflectFraction);
		if (ReflectedAmount == 0)
		{
			return;
		}

		ReflectedAmount = FMath::Abs(ReflectedAmount);

		if (USVGameplayFunctionLibrary::ApplyDamage(OwningActor, InstigatorActor, ReflectedAmount))
		{
			UE_LOG(LogTemp, Log, TEXT("Damage successfully reflected, ReflectedAmount : '%i' to '%s'"), ReflectedAmount, *GetNameSafe(InstigatorActor))
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Damage reflection failed ; OwningActor : '%s', InstigatorActor : '%s', ReflectedAmount : '%i'"), *GetNameSafe(OwningActor), *GetNameSafe(InstigatorActor), ReflectedAmount)
		}
	}
}
