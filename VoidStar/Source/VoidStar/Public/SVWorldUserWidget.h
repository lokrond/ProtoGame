// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SVWorldUserWidget.generated.h"

class USizeBox;

/**
 * 
 */
UCLASS()
class VOIDSTAR_API USVWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(meta = (BindWidget))
	USizeBox* ParentSizeBox;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:

	UPROPERTY(EditAnywhere, Category = "UI")
	FVector WorldOffset;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	TObjectPtr<AActor> AttachedActor;

};
