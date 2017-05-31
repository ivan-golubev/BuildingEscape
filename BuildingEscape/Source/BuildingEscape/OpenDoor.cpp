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
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CheckDoorConditions();
}

void UOpenDoor::Open()
{
	GetOwner()->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UOpenDoor::Close()
{	
	GetOwner()->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}

float UOpenDoor::GetMassOnPlate() const { 
	float totalMass = 0.f;
	TArray<AActor*> actors;
	PressurePlate->GetOverlappingActors(actors);
	for (AActor* actor: actors) {
		totalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}	
	//UE_LOG(LogTemp, Warning, TEXT("Total mass is: %s"), *FString::SanitizeFloat(totalMass));
	return totalMass; 
}

void UOpenDoor::CheckDoorConditions()
{
	if (GetMassOnPlate() >= MassThreshold) {
		Open();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}	
	else if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		Close();
	}
}
