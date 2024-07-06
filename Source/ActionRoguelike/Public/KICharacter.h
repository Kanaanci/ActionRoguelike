// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KICharacter.generated.h"

//Instead of including header files we are just defining them here
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ACTIONROGUELIKE_API AKICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKICharacter();

protected:


	//Create pointers for the camera component and the spring arm component
	UPROPERTY(VisibleAnywhere);
	UCameraComponent* CameraComp;
	
	UPROPERTY(VisibleAnywhere);
	USpringArmComponent* SpringArmComp;
	
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
