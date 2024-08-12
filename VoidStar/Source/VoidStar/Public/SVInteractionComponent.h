// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SVInteractionComponent.generated.h"

class USVAttributeComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VOIDSTAR_API USVInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	void PrimaryInteract();

	// Sets default values for this component's properties
	USVInteractionComponent();

protected:

	UPROPERTY(EditAnywhere, Category = "Class")
	TSubclassOf<USVAttributeComponent> AttributeCompClass;

	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};