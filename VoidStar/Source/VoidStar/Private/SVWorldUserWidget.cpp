// Fill out your copyright notice in the Description page of Project Settings.


#include "SVWorldUserWidget.h"
#include <Kismet/GameplayStatics.h>
#include <Components/SizeBox.h>
#include <Blueprint/WidgetLayoutLibrary.h>

void USVWorldUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!IsValid(AttachedActor)) 
	{
		RemoveFromParent();

		UE_LOG(LogTemp, Warning, TEXT("AttachedActor no longer valid, HealthWidget should have been removed earlier."))
		return;
	}

	FVector2D ScreenPosition;

	if (UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), AttachedActor->GetActorLocation() + WorldOffset, ScreenPosition))
	{
		float Scale = UWidgetLayoutLibrary::GetViewportScale(this);
		ScreenPosition /= Scale;

		if (ParentSizeBox)
		{
			ParentSizeBox->SetRenderTranslation(ScreenPosition);
		}
	}
}
