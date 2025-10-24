// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KICharacter.generated.h"

//Instead of including header files we are just defining them here
class UCameraComponent;
class USpringArmComponent;
class UAnimMontage;
class UKIInteractionComponent;

UCLASS()
class ACTIONROGUELIKE_API AKICharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category="Attack")
	UAnimMontage* AttackAnim;

	FTimerHandle TimerHandle_PrimaryAttack;
	
	UPROPERTY(EditAnywhere, Category="Special Attack")
	TSubclassOf<AActor> SpecialAttackClass;

	UPROPERTY(EditAnywhere, Category="Special Attack")
	UAnimMontage* SpecialAttackAnim;

	FTimerHandle TimerHandle_SpecialAttack;

public:
	// Sets default values for this character's properties
	AKICharacter();

protected:
	//Create pointers for the camera component and the spring arm component
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UKIInteractionComponent* InteractionComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Movement forward/back
	void MoveForward(float Value);

	//  Movement left/right
	void MoveRight(float Value);

	// Actions
	void JumpAction();
	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();
	void PrimaryInteract();
	void SpecialAttack();
	void SpecialAttack_TimeElapsed();
	
	// Data
	FVector GetHandLocation();
	FActorSpawnParameters GetBaseSpawnParams();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
