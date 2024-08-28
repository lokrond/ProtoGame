// Fill out your copyright notice in the Description page of Project Settings.


#include "SVActionEffect.h"

#include "SVActionComponent.h"
#include "SVAttributeComponent.h"
#include "VSBaseProjectile.h"

USVActionEffect::USVActionEffect()
{
	bAutoStart = true;

}

void USVActionEffect::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	if (Duration > 0.f)
	{
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "StopAction", Instigator);

		GetWorld()->GetTimerManager().SetTimer(DurationHandle, Delegate, Duration, false);
	}

	if (Period > 0.f)
	{
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "ExecutePeriodicEffect", Instigator);

		GetWorld()->GetTimerManager().SetTimer(PeriodHandle, Delegate, Period, true);
	}
}

void USVActionEffect::StopAction_Implementation(AActor* Instigator)
{
	if (GetWorld()->GetTimerManager().GetTimerRemaining(PeriodHandle) < KINDA_SMALL_NUMBER)
	{
		ExecutePeriodicEffect(Instigator);
	}

	Super::StopAction_Implementation(Instigator);

	GetWorld()->GetTimerManager().ClearTimer(PeriodHandle);
	GetWorld()->GetTimerManager().ClearTimer(DurationHandle);

	if (USVActionComponent* ActionComp = GetOwningComponent())
	{
		ActionComp->RemoveAction(this);
	}
}

void USVActionEffect::ExecutePeriodicEffect_Implementation(AActor* Instigator)
{


}

