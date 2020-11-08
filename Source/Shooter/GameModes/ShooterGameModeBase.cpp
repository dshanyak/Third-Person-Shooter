// Copyright Epic Games, Inc. All Rights Reserved.


#include "ShooterGameModeBase.h"

#include "EngineUtils.h"
#include "KillEmAllGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Shooter/AI/Controllers/ShooterAIController.h"
#include "Shooter/Characters/PlayerShooterCharacter.h"


void AShooterGameModeBase::PawnKilled(APawn* PawnKilled) 
{
    // If the killed pawn is the player, end the game with a loss
    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if(PlayerController != nullptr)
    {
        EndGame(false);
        return;
    }

    // If the killed pawn is an NPC, disengage player from combat after delay
    GetWorldTimerManager().SetTimer(DisengageFromCombatTimerHandle, this, &AKillEmAllGameMode::DisengageCombat, DisengageCombatDelay);
    
    //Update the count of number of enemies still alive
    EnemiesRemaining = 0;
    for(AShooterAIController* AIController : TActorRange<AShooterAIController>(GetWorld()))
    {
        if(!AIController->IsDead())
        {
            EnemiesRemaining++;
        }
    }
}

int AShooterGameModeBase::GetNumEnemies() const
{
    return EnemiesRemaining;
}

void AShooterGameModeBase::EndGame(bool bIsPlayerWinner) const
{
    for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}

void AShooterGameModeBase::DisengageCombat() const
{
    APlayerShooterCharacter* PlayerShooterCharacter = Cast<APlayerShooterCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if (PlayerShooterCharacter == nullptr)
        return;
    PlayerShooterCharacter->bIsInCombat = false;
}
