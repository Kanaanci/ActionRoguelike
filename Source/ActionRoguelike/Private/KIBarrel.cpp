// Fill out your copyright notice in the Description page of Project Settings.

#include "KIBarrel.h"

// Sets default values
AKIBarrel::AKIBarrel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	RootComponent = StaticMeshComp;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->Radius = 100000;
	RadialForceComp->ImpulseStrength = 1000000;
	RadialForceComp->SetupAttachment(StaticMeshComp);
}

// Called when the game starts or when spawned
void AKIBarrel::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AKIBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AKIBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	StaticMeshComp->OnComponentHit.AddDynamic(this, &AKIBarrel::OnActorHit);
}


void AKIBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                        FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComp->FireImpulse();

	UE_LOG(LogTemp, Log, TEXT("OnActorHit %s at game time: %f"),*GetNameSafe(OtherActor), GetWorld()->TimeSeconds);
	DrawDebugString(GetWorld(), Hit.ImpactPoint, "This is the String", nullptr, FColor::Green, 2.0f, true);
}
