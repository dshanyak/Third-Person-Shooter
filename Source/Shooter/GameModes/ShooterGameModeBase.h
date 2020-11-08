// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterGameModeBase.generated.h"

class APlayerShooterCharacter;

UCLASS()
class SHOOTER_API AShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void PawnKilled(APawn* PawnKilled);

	UFUNCTION(BlueprintPure)
    int GetNumEnemies() const;

protected:
	// handle ending the game
	void EndGame(bool bIsPlayerWinner) const;

	// disengage player from combat after an NPC death
	FTimerHandle DisengageFromCombatTimerHandle;
	UPROPERTY(EditAnywhere)
	float DisengageCombatDelay = 5.f;
	void DisengageCombat() const;

	// Number of enemies remaining
	UPROPERTY(EditDefaultsOnly)
	int EnemiesRemaining = 10;

};
