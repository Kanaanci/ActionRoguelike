// Fill out your copyright notice in the Description page of Project Settings.


#include "KIInteractionComponent.h"

#include "KIGameplayInterface.h"

// Sets default values for this component's properties
UKIInteractionComponent::UKIInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UKIInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UKIInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UKIInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;
	
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	
	FVector End = EyeLocation + (EyeRotation.Vector() * 1000);

	// FHitResult Hit;
	// GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);

	FCollisionShape Shape;
	Shape.SetSphere(30.0f);
	TArray<FHitResult> Hits;
	GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);

	for (FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();

		if (HitActor)
		{
			if (HitActor->Implements<UKIGameplayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(MyOwner);
				IKIGameplayInterface::Execute_Interact(HitActor, MyPawn);
				DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 30.0f, 32, FColor::Green, false, 2.0f);
				break;
			}
		}
	}

	DrawDebugLine(GetWorld(), EyeLocation, End, FColor::Red, false, 2.0f, 0, 2.0f);

}
