// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ShooterCharacterBase.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "Shooter/Characters/ShooterCharacterBase.h"
#include "PlayerShooterCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API APlayerShooterCharacter : public AShooterCharacterBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	// Constructor
	APlayerShooterCharacter();
	
	// Checks if the player is in combat
	UPROPERTY(VisibleAnywhere)
	bool bIsInCombat = false;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Get the percentage of character's health
	UFUNCTION(BlueprintPure)
    float GetHealthPercent() const;

	// Noise Emitter
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Noise")
	UPawnNoiseEmitterComponent* NoiseEmitterComponent;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called if player wins (used in GetToLocationGameMode)
	UFUNCTION(BlueprintCallable)
	void WinGame() const;

private:
	// Regen health on timer
	FTimerHandle RegainHealthTimer;
	UPROPERTY(EditAnywhere)
	float RegainHealthInterval = 1.f;
	void RegainHealth();

	// MOVEMENTS
	void MoveForward(float AxisValue);
	void MoveSideways(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookSidewaysRate(float AxisValue);
	
};
