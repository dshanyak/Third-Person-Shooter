// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacterBase.h"
#include "Shooter/Weapons/GunBase.h"
#include "Components/CapsuleComponent.h"
#include "Shooter/GameModes/ShooterGameModeBase.h"

// Sets default values
AShooterCharacterBase::AShooterCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	SetupWeapon();

	CurrentHealth = MaxHealth;
}

// Checks if the player is dead
bool AShooterCharacterBase::IsDead() const
{
	return CurrentHealth <= 0;
}

// Called every frame
void AShooterCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Handles the character taking damage
float AShooterCharacterBase::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) 
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	CurrentHealth = FMath::Clamp(CurrentHealth -= DamageApplied, 0.f, MaxHealth);

	// when dead, handle death
	if(IsDead())
	{
		HandleDeath();
	}

	return DamageApplied;
}

void AShooterCharacterBase::Shoot()
{
	Gun->PullTrigger();
}

// Add weapon to character
void AShooterCharacterBase::SetupWeapon() 
{
	// Spawn weapon
	Gun = GetWorld()->SpawnActor<AGunBase>(GunClass);

	// Hide default weapon
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	// Attach custom weapon
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
}

// Called when the character's health is <=0
void AShooterCharacterBase::HandleDeath() 
{
	// Call PawnKilled from game mode
	AShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AShooterGameModeBase>();
	if(GameMode != nullptr)
	{
		GameMode->PawnKilled(this);
	}

	// Remove capsule component and controller
	DetachFromControllerPendingDestroy();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}





