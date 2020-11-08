// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBase.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Serialization/JsonTypes.h"
#include "Shooter/Characters/PlayerShooterCharacter.h"

// Sets default values
AGunBase::AGunBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(Root);

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetupAttachment(Root);

	

}

void AGunBase::PullTrigger()
{
	// Check if the owner of the gun is the player
	bIsOwnerPlayer = Cast<APlayerShooterCharacter>(GetOwner()) == nullptr ? false : true;
	
	// Spawn muzzle effects
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, MeshComponent, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, MeshComponent, TEXT("MuzzleFlashSocket"));
	if(bIsOwnerPlayer)
		MakeNoise(1, Cast<APawn>(GetOwner()));

	FHitResult HitResult;
	FVector ShotDirection;
	bool bSuccess = GunTrace(HitResult, ShotDirection);
	if(bSuccess)
	{
		// Create particle and sound effects at impact point
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, HitResult.Location, ShotDirection.Rotation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), HitSound, HitResult.Location, ShotDirection.Rotation());
		MakeNoise(1, Cast<APawn>(GetOwner()), HitResult.Location);
		
		// Apply Damage
		FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
		HitResult.GetActor()->TakeDamage(Damage, DamageEvent, GetOwnerController(), this);

		// Draw debug point
			//DrawDebugPoint(GetWorld(), HitResult.Location, 20.f, FColor::Green, true);
	}

}

// Called when the game starts or when spawned
void AGunBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Calculates direction of bullet and whether it hits
bool AGunBase::GunTrace(FHitResult& HitResult, FVector& ShotDirection) 
{
	// Get owner controller
	AController* OwnerController = GetOwnerController();
	if(!OwnerController) return false; // avoid nullptr errors

	// Get ViewPoint location and rotation
	FVector ViewPointLocation;
	FRotator ViewPointRotation;
	OwnerController->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);
	ShotDirection = -ViewPointRotation.Vector();

	// Calculate end point of linetrace
	FVector End = ViewPointLocation + (ViewPointRotation.Vector() * MaxRange);

	// Draw line trace
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(HitResult, ViewPointLocation, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

AController* AGunBase::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(!OwnerPawn) return nullptr; // avoid nullptr errors
	return OwnerPawn->GetController();
	
}

