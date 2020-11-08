// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Shooter/Characters/NPCShooterCharacter.h"

class AIController;


UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen() 
{
    NodeName = TEXT("UpdatePlayerLocationIfSeen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    // Get player's pawn
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if(PlayerPawn == nullptr)
    {
        return;
    }

    // Get AI Controller
    AAIController* AIController = OwnerComp.GetAIOwner();
    if(AIController == nullptr)
    {
        return;
    }

    // Get NPC Pawn
    ANPCShooterCharacter* NPC = Cast<ANPCShooterCharacter>(AIController->GetPawn());
    if(NPC == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("BTService_PlayerLocationIfSeen: NPC is null"));
        return;
    }

    // Update player location if AI character has line of sight to player 
    if((NPC->bCanSeePlayer) && AIController->LineOfSightTo(PlayerPawn))
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
    }
    else
    {
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
        NPC->bCanSeePlayer = false;
    }
}
