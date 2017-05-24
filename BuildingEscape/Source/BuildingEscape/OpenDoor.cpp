// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	this->PressurePlateActor = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CheckDoorConditions();
}

void UOpenDoor::Open()
{
	UE_LOG(LogTemp, Warning, TEXT("Opening the door: %s"), *GetOwner()->GetName());
	//auto rot = GetOwner()->GetActorRotation();
	//rot.Yaw = -50.0f;
	//GetOwner()->SetActorRotation(rot);
	GetOwner()->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UOpenDoor::Close()
{
	UE_LOG(LogTemp, Warning, TEXT("Closing the door: %s"), *GetOwner()->GetName());
	GetOwner()->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}

void UOpenDoor::CheckDoorConditions()
{
	if (PressurePlate->IsOverlappingActor(PressurePlateActor)) 
	{
		Open();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	else if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay) 
	{
		Close();
	}
}
