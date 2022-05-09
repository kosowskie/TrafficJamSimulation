// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrafficJamSimulation/Components/FrontCarBoxCollision.h"
#include "TrafficCar.generated.h"

class UBackCarBoxCollision;
UCLASS()
class TRAFFICJAMSIMULATION_API ATrafficCar : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATrafficCar();
	
	UPROPERTY(Category = CarCollision, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* MyRootComponent;

	UPROPERTY(Category = CarCollision, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UFrontCarBoxCollision* FrontCarBoxCollision;

	UPROPERTY(Category = CarCollision, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBackCarBoxCollision* BackCarBoxCollision;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
