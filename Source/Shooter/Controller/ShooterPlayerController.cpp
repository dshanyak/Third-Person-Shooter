// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay() 
{
    Super::BeginPlay();

    ShowStartDisplays();
    
}

void AShooterPlayerController::ShowStartDisplays()
{
    // Play intro display
    Intro = CreateWidget(this, IntroClass);
    if(Intro != nullptr)
    {
        Intro->AddToViewport();
        GetWorldTimerManager().SetTimer(IntroTimer, this, &AShooterPlayerController::RemoveIntro, IntroDelay);
    }
    
    // Add heads up display
    HUD = CreateWidget(this, HUDClass);
    if(HUD != nullptr)
    {
        HUD->AddToViewport();
    }
}

void AShooterPlayerController::RemoveIntro() const
{
    if(Intro != nullptr)
    {
        Intro->RemoveFromViewport();
    }
}

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner) 
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    // Remove HUD
    HUD->RemoveFromViewport();

    if(bIsWinner)
    {
        // Spawn Win Widget
        UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
        if(WinScreen != nullptr)
        {
            WinScreen->AddToViewport();
        }
    }
    else
    {
        //Spawn Lose Widget
        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
        if(LoseScreen != nullptr)
        {
            LoseScreen->AddToViewport();
        }
    }
    
    // Restart game in RestartDelay seconds
    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}


