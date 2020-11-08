// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ShooterGameModeBase.h"
#include "Engine/TriggerVolume.h"
#include "Shooter/GameModes/ShooterGameModeBase.h"
#include "GetToLocationGameMode.generated.h"


UCLASS()
class SHOOTER_API AGetToLocationGameMode : public AShooterGameModeBase
{
	GENERATED_BODY()

public:
	void WinGame() const;
	
};
