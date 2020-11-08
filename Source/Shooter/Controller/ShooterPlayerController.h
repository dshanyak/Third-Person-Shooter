// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class SHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

protected:
	virtual void BeginPlay() override;

private:
	// Win/Lose Screens
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseScreenClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinScreenClass;

	// HUD Display
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDClass;
	UPROPERTY()
	UUserWidget* HUD;

	// Restart game elements
	FTimerHandle RestartTimer;
	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.f;
	
	// Display Intro
	FTimerHandle IntroTimer;
	UPROPERTY(EditAnywhere)
	float IntroDelay = 5.f;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> IntroClass;
	UUserWidget* Intro;
	void ShowStartDisplays();
	void RemoveIntro() const;
	
};
