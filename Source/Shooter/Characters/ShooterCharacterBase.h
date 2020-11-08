// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacterBase.generated.h"

// forward declaration
class AGunBase;

UCLASS()
class SHOOTER_API AShooterCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Properties
	UPROPERTY(EditAnywhere)
	float RotationRate = 100.f;
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.f;
	UPROPERTY(VisibleAnywhere)
	float CurrentHealth = 100.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// When shooter takes damage
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// Actions
	void Shoot();

	// Check if character is dead
	UFUNCTION(BlueprintPure)
	bool IsDead() const;
	
private:
	// Actions
	void SetupWeapon();
	void HandleDeath();

	// Weapon
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AGunBase> GunClass;
	UPROPERTY()
	AGunBase* Gun;

};
