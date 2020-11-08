// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunBase.generated.h"

UCLASS()
class SHOOTER_API AGunBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunBase();

	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* MeshComponent;

	// Effects
	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere)
	UParticleSystem* HitEffect;
	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;
	UPROPERTY(EditAnywhere)
	USoundBase* HitSound;

	// Weapon Stats
	UPROPERTY(EditAnywhere)
	float MaxRange = 1000;
	UPROPERTY(EditAnywhere)
	float Damage = 10.f;

	// Line tracing
	bool GunTrace(FHitResult& HitResult, FVector& ShotDirection);
	AController* GetOwnerController() const;

	bool bIsOwnerPlayer = false;

};
