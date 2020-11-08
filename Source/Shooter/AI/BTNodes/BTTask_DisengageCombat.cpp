// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_DisengageCombat.h"

#include "Kismet/GameplayStatics.h"
#include "Shooter/Characters/PlayerShooterCharacter.h"

class APlayerShooterCharacter;

UBTTask_DisengageCombat::UBTTask_DisengageCombat()
{
    NodeName = TEXT("DisengageCombat");
}

EBTNodeResult::Type UBTTask_DisengageCombat::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    // Ensure we have an AI owner
    if(OwnerComp.GetAIOwner() == nullptr)
        return EBTNodeResult::Failed;

    // Get player's pawn
    APlayerShooterCharacter* PlayerShooterCharacter = Cast<APlayerShooterCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if(PlayerShooterCharacter == nullptr)
        return EBTNodeResult::Failed;

    // Toggle IsInCombat boolean
    PlayerShooterCharacter->bIsInCombat = false;

    return EBTNodeResult::Succeeded;
}
