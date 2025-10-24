// Fill out your copyright notice in the Description page of Project Settings.


#include "KICharacter.h"

#include "AKIBlackHoleProjectile.h"
#include "KIInteractionComponent.h"
#include "KIMagicProjectile.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AKICharacter::AKICharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Instantiate Spring arm for 3rd person and then attach it to the character root
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	//Instantiate the camera component and then attach it to the Spring arm component
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComponent = CreateDefaultSubobject<UKIInteractionComponent>("InteractionComponent");

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void AKICharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AKICharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(), Value);
}

void AKICharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, Value);
}

void AKICharacter::JumpAction()
{
	Jump();
}

FVector AKICharacter::GetHandLocation()
{
	return GetMesh()->GetSocketLocation("Muzzle_01");
}

FActorSpawnParameters AKICharacter::GetBaseSpawnParams()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	return SpawnParams;
}

void AKICharacter::PrimaryAttack_TimeElapsed()
{
	FTransform SpawnTM = FTransform(GetControlRotation(), GetHandLocation());
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, GetBaseSpawnParams());
}

void AKICharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AKICharacter::PrimaryAttack_TimeElapsed, .2f);
}


void AKICharacter::PrimaryInteract()
{
	if (InteractionComponent)
	{
		InteractionComponent->PrimaryInteract();
	}
}

void AKICharacter::SpecialAttack_TimeElapsed()
{
	FTransform SpawnTM = FTransform(GetControlRotation(), GetHandLocation());
	AActor* SpecialAttack = GetWorld()->SpawnActor<AActor>(SpecialAttackClass, SpawnTM, GetBaseSpawnParams());

	if (SpecialAttack)
	{
		FTimerHandle TimerHandle_DestroyActor;
		GetWorldTimerManager().SetTimer(TimerHandle_DestroyActor, [SpecialAttack]()
		{
			if (SpecialAttack)
			{
				SpecialAttack->Destroy();
			}
		}, 5.0f, false);
	}
}

void AKICharacter::SpecialAttack()
{
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(TimerHandle_SpecialAttack, this, &AKICharacter::SpecialAttack_TimeElapsed, .1f);
}

// Called every frame
void AKICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AKICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Player walking movement
	PlayerInputComponent->BindAxis("MoveForward", this, &AKICharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AKICharacter::MoveRight);

	// Mouse camera looking
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	// Actions
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AKICharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("JumpAction", IE_Pressed, this, &AKICharacter::JumpAction);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AKICharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("SpecialAttack", IE_Pressed, this, &AKICharacter::SpecialAttack);
}
