// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SoundSourceIfHeard.h"



#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Shooter/Characters/NPCShooterCharacter.h"

UBTService_SoundSourceIfHeard::UBTService_SoundSourceIfHeard()
{
    NodeName = TEXT("SoundSourceIfHeard");
}

void UBTService_SoundSourceIfHeard::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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
        UE_LOG(LogTemp, Error, TEXT("BTService_SoundSourceIfHeard: NPC is null"));
        return;
    }

    // Update last player's last known location when the NPC hears them
    if(NPC->bCanHearNoise)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
    }

    // Set bCanHearNoise to back to false when the NPC can't see them
    NPC->bCanHearNoise = NPC->bCanSeePlayer;
    
}
