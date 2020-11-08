// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "GameFramework/PlayerController.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"
#include "Shooter/AI/Controllers/ShooterAIController.h"
#include "Shooter/Characters/PlayerShooterCharacter.h"


void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled) 
{
    Super::PawnKilled(PawnKilled);

    // If no enemies remaining, player wins
    if(EnemiesRemaining <= 0)
    {
        EndGame(true);
    }
    
}

