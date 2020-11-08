// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_EngageCombat.h"


#include "Kismet/GameplayStatics.h"
#include "Shooter/Characters/PlayerShooterCharacter.h"

UBTTask_EngageCombat::UBTTask_EngageCombat()
{
    NodeName = TEXT("EngageCombat");
}

EBTNodeResult::Type UBTTask_EngageCombat::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
    PlayerShooterCharacter->bIsInCombat = true;

    return EBTNodeResult::Succeeded;
}
