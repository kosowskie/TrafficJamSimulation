// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrafficJamSimulation/EntityComponentSystem/Public/EntityInterface.h"
#include "TrafficCar.generated.h"

class UBackCarBoxCollision;
UCLASS()
class TRAFFICJAMSIMULATION_API ATrafficCar : public AActor, public IEntityInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATrafficCar();
	
	UPROPERTY(Category = CarCollision, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* MyRootComponent;
	
	UPROPERTY(Category = CarCollision, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Id;

	UFUNCTION(BlueprintNativeEvent)
	FEntityData GetData();
	virtual FEntityData GetData_Implementation() override;
};
