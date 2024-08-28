// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SVAction_Thornbuff.h"
#include "VSBaseBuffs.h"
#include "VSGameplayInterface.h"
#include "VSBuffThorn.generated.h"


/**
 * 
 */
UCLASS()
class VOIDSTAR_API AVSBuffThorn : public AVSBaseBuffs, public IVSGameplayInterface
{
	GENERATED_BODY()

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;


public:

	AVSBuffThorn();



protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BuffMeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<USVAction> ActionToGrant;

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void GrantingBuffAction(APawn* InstigatorPawn);
};
