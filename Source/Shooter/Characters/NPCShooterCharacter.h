// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ShooterCharacterBase.h"
#include "Engine/TargetPoint.h"
#include "Perception/PawnSensingComponent.h"

#include "NPCShooterCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API ANPCShooterCharacter : public AShooterCharacterBase
{
	GENERATED_BODY()


public:
	// Constructor
	ANPCShooterCharacter();

	// Point where NPC will pace to
	UPROPERTY(EditAnywhere)
	ATargetPoint* PatrolPoint;

	// Adds sight and hearing to NPC
	UPROPERTY(EditAnywhere)
	UPawnSensingComponent* PawnSensingComponent;
	
	UPROPERTY(EditDefaultsOnly)
	bool bCanSeePlayer = false;
	UPROPERTY(EditDefaultsOnly)
	bool bCanHearNoise = false;

private:
	// Adds dynamic to the PawnSensingComponent
	UFUNCTION()
    void CanSeePlayer(APawn* Pawn);
	UFUNCTION()
	void CanHearSomething(APawn* OtherActor, const FVector &Location, float Volume);
};

