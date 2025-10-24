// Fill out your copyright notice in the Description page of Project Settings.


#include "KITeleportProjectile.h"

// Sets default values
AKITeleportProjectile::AKITeleportProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->ProjectileGravityScale = 0.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
}

// Called when the game starts or when spawned
void AKITeleportProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AKITeleportProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
