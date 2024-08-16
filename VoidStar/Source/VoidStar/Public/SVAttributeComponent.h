// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SVAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, USVAttributeComponent*, OwningComp, float, NewHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VOIDSTAR_API USVAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USVAttributeComponent();
	// Could use (meta = "") specifier for more properties editor related
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static USVAttributeComponent* GetAttributes(AActor* FromActor);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static bool IsActorAlive(AActor* Actor);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float MaxHealth = 100.f;

public:

	UFUNCTION(BlueprintCallable)
	bool Kill(AActor* InstigatorActor);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(AActor* InstigatorActor, float Delta);

	float GetHealth() { return Health; }
	float GetMaxHealth() { return MaxHealth; }
	float AddToHealth(float NewHealth) { return Health += NewHealth; }
	bool IsFullHealth() const;

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

};