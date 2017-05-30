// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();	
	BindController();
}

void UGrabber::BindController()
{
	/// Look for the attached Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	/// Look for attached Input Controller
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	UE_LOG(LogTemp, Warning, TEXT("Grabber:InputComponent found. owner: %s"), *GetOwner()->GetName());
	/// bind the input axis
	InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PhysicsHandle->GrabbedComponent) {
		FVector playerLocation;
		FRotator playerRotation;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(playerLocation, playerRotation);
		FVector lineTraceEnd = playerLocation + playerRotation.Vector() * Reach;
		PhysicsHandle->SetTargetLocation(lineTraceEnd);
	}
}

FHitResult UGrabber::GetPhysicsBodyInReach()
{
	FVector playerLocation;
	FRotator playerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(playerLocation, playerRotation);
	//UE_LOG(LogTemp, Warning, TEXT("Grabber:PlayerLocation(%s), PlayerRotation(%s)"), *playerLocation.ToString(), *playerRotation.ToString());
	FVector lineTraceEnd = playerLocation + playerRotation.Vector() * Reach;
	//DrawDebugLine(
	//	GetWorld(),
	//	playerLocation,
	//	lineTraceEnd,
	//	FColor(255, 0, 0),
	//	false,
	//	0.f,
	//	0.f,
	//	5.f
	//);

	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(
		hit,
		playerLocation,
		lineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(false)
	);
	return hit;
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));
	// ray cast to get actors with physics body collision channel set
	FHitResult hit = GetPhysicsBodyInReach();
	if (hit.GetActor() != nullptr) {
		auto componentToGrab = hit.GetComponent();
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			componentToGrab,
			NAME_None,
			componentToGrab->GetOwner()->GetActorLocation(),
			componentToGrab->GetOwner()->GetActorRotation()
		);
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab released"));
	PhysicsHandle->ReleaseComponent();
}