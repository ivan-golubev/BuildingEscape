// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorOpenEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorCloseEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FDoorOpenEvent OnOpen;

	UPROPERTY(BlueprintAssignable)
	FDoorCloseEvent OnClose;

protected:
	void CheckDoorConditions();
	// Called when the game starts
	virtual void BeginPlay() override;


private:
		// mass in kilograms to open the door
		UPROPERTY(EditAnywhere)
		float MassThreshold = 30.f;

		UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;	

		float GetMassOnPlate() const;		
};
