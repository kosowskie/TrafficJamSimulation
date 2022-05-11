// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrafficJamSimulation/System/Public/CarSystem.h"
#include "CarSpawner.generated.h"

UCLASS()
class TRAFFICJAMSIMULATION_API ACarSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACarSpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CarId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* CarMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "60.0", UIMin = "0.0", UIMax = "60.0"))
	float MinRandSpawnTimer = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "60.0", UIMin = "0.0", UIMax = "60.0"))
	float MaxRandSpawnTimer = 6.f;

	UFUNCTION()
	void SpawningEntities();

	UFUNCTION()
	void SpawnCarEntity() const;
	
	ACarSystem* GetCarSystem() const
	{
		return CarSystem;
	};

	void SetCarSystem(ACarSystem* _CarSystem)
	{
		this->CarSystem = _CarSystem;
	};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void FindCarEntitySystem(ATrafficJamSimulationGameModeBase* ProjectGameMode);

private:
	void BindCarEntitySystem();

	UPROPERTY()
	ACarSystem* CarSystem;
};
