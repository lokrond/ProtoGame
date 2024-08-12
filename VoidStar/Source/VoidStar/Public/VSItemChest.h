// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VSItemChest.generated.h"

UCLASS()
class VOIDSTAR_API AVSItemChest : public AActor
{
	GENERATED_BODY()

public:

	AVSItemChest();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UStaticMeshComponent> LidMesh;

};
