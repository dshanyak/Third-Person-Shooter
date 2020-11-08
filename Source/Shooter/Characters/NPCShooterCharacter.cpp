// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCShooterCharacter.h"

#include "Shooter/AI/BTServices/BTService_PlayerLocationIfSeen.h"

ANPCShooterCharacter::ANPCShooterCharacter()
{
    PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn Sensing Component"));
    PawnSensingComponent->OnSeePawn.AddDynamic(this, &ANPCShooterCharacter::CanSeePlayer);
    PawnSensingComponent->OnHearNoise.AddDynamic(this, &ANPCShooterCharacter::CanHearSomething);
}

void ANPCShooterCharacter::CanSeePlayer(APawn* Pawn)
{
    bCanSeePlayer = true;
}

void ANPCShooterCharacter::CanHearSomething(APawn* OtherActor, const FVector& Location, float Volume)
{
    bCanHearNoise = true;
}
