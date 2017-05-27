// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Grabber:BeginPlay()"));
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector playerLocation;
	FRotator playerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(playerLocation, playerRotation);
	//UE_LOG(LogTemp, Warning, TEXT("Grabber:PlayerLocation(%s), PlayerRotation(%s)"), *playerLocation.ToString(), *playerRotation.ToString());
	FVector lineTraceEnd = playerLocation + playerRotation.Vector() * Reach;
	DrawDebugLine(
		GetWorld(),
		playerLocation,
		lineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		5.f
	);

	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(
		hit,
		playerLocation,
		lineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(false)
	);
	if (hit.GetActor() != NULL) {
		UE_LOG(LogTemp, Warning, TEXT("Object hit: %s"), *hit.GetActor()->GetName());
	}
}

