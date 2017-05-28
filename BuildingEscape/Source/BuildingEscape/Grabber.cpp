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
	/// Look for the attached Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabber:PhysicsHandle found. owner: %s"), *GetOwner()->GetName());
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber:PhysicsHandle is missing ! owner: %s"), *GetOwner()->GetName());
	}
	/// Look for attached Input Controller
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabber:InputComponent found. owner: %s"), *GetOwner()->GetName());
		/// bind the input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber:InputComponent is missing ! owner: %s"), *GetOwner()->GetName());
	}
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

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));
}

