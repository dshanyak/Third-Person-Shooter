// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Shooter/Characters/NPCShooterCharacter.h"
#include "Shooter/Characters/ShooterCharacterBase.h"


void AShooterAIController::BeginPlay() 
{
    Super::BeginPlay();

    // Run behavior tree and set start location
    if(AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);

        // Set default blackboard keys
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
        ANPCShooterCharacter* NPC = Cast<ANPCShooterCharacter>(GetPawn());
        GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolPoint"), NPC->PatrolPoint->GetActorLocation());
    }
    
}

bool AShooterAIController::IsDead() const
{
    AShooterCharacterBase* ControlledCharacter = Cast<AShooterCharacterBase>(GetPawn());
    if(ControlledCharacter != nullptr)
    {
        return ControlledCharacter->IsDead();
    }

    return true;
}
