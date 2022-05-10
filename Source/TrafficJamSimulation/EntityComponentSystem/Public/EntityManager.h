// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EntityManager.generated.h"

class AEntitySystem;
class ATrafficJamSimulationGameModeBase;

USTRUCT(BlueprintType)
struct FEntityData
{
	GENERATED_BODY()

	
	UPROPERTY()
	FString Id;

	UPROPERTY()
	UStaticMesh* ViewRepresentation;

	UPROPERTY()
	FTransform Transform;
	
	FEntityData(): ViewRepresentation(nullptr)
	{
	};

	FEntityData(FString _Id, UStaticMesh* _ViewRepresentation, FTransform _Transform) :
		Id(_Id), ViewRepresentation(_ViewRepresentation), Transform(_Transform)
	{
	};
};

UCLASS()
class TRAFFICJAMSIMULATION_API UEntityManager : public UObject
{
	GENERATED_BODY()

	UEntityManager(const FObjectInitializer& ObjectInitializer);

public:
	UFUNCTION()
	void InitializeManager(TArray<AActor*> Entities);

	UFUNCTION()
	virtual void InitializeSystems(){};

	UFUNCTION()
	void CreateSystem(TSubclassOf<AEntitySystem> SystemClass);

	TArray<AEntitySystem*> GetEntitiesContainer() const
	{
		return EntitiesContainer;
	};

	void SetEntitiesContainer(const TArray<AEntitySystem*>& _EntitiesContainer)
	{
		this->EntitiesContainer = _EntitiesContainer;
	};

private:
	UPROPERTY()
	TArray<AEntitySystem*> EntitiesContainer;
};
