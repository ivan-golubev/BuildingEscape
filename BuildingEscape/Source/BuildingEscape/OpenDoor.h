// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	void Open();
	void Close();
	void CheckDoorConditions();
	// Called when the game starts
	virtual void BeginPlay() override;


private:
		UPROPERTY(VisibleAnywhere)
		float OpenAngle = -70.f;
		UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 1.f;
		float LastDoorOpenTime = 0.f;
		// mass in kilograms to open the door
		UPROPERTY(EditAnywhere)
		float MassThreshold = 30.f;

		UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate;	

		float GetMassOnPlate();		
};
