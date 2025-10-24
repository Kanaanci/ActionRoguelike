// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KIProjectileBaseClass.h"
#include "GameFramework/Actor.h"
#include "KIMagicProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AKIMagicProjectile : public AKIProjectileBaseClass
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AKIMagicProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
