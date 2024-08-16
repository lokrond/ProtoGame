// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "SVActionComponent.generated.h"

class USVAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VOIDSTAR_API USVActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	USVActionComponent();

	UPROPERTY(EditAnywhere, blueprintReadWrite, Category = "Tags")
	FGameplayTagContainer ActiveGameplayTags;

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void AddAction(TSubclassOf<USVAction> ActionClass);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool StartActionByName(AActor* Instigator, FName ActionName);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool StopActionByName(AActor* Instigator, FName ActionName);

protected:

	UPROPERTY()
	TArray<TObjectPtr<USVAction>> Actions;

	UPROPERTY(EditAnywhere, Category = "Actions")
	TArray<TSubclassOf<USVAction>> DefaultActions;

	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
