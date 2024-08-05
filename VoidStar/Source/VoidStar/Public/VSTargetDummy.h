// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VSTargetDummy.generated.h"

class USVAttributeComponent;

UCLASS()
class VOIDSTAR_API AVSTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVSTargetDummy();

protected:


	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USVAttributeComponent> AttributeComp;

	//UFUNCTION()
	//void OnHealthChanged(AActor* InstigatorActor, UMjAttributeComponent* OwningComp, float NewHealth, float Delta);

	virtual void BeginPlay() override;

};
