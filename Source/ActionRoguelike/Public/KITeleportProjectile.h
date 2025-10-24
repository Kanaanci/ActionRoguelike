// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KIProjectileBaseClass.h"
#include "GameFramework/Actor.h"
#include "KITeleportProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AKITeleportProjectile : public AKIProjectileBaseClass
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AKITeleportProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
