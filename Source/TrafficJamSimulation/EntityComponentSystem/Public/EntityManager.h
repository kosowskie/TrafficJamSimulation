// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EntityManager.generated.h"

class ACarSystem;
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

UCLASS(Blueprintable, BlueprintType, EditInlineNew)
class TRAFFICJAMSIMULATION_API UEntityManager : public UObject
{
	GENERATED_BODY()


public:
	UEntityManager();
	
	UEntityManager(const FObjectInitializer& ObjectInitializer);
	
	UFUNCTION()
	void InitializeManager(TArray<AActor*> Entities);

	virtual void InitializeSystems(){};

	TArray<AEntitySystem*> GetEntitiesContainer() const
	{
		return EntitiesContainer;
	};

	void SetEntitiesContainer(const TArray<AEntitySystem*>& _EntitiesContainer)
	{
		this->EntitiesContainer = _EntitiesContainer;
	};

	ATrafficJamSimulationGameModeBase* GetWorldContext() const
	{
		return WorldContext;
	};

	void SetWorldContext(ATrafficJamSimulationGameModeBase* _WorldContext)
	{
		this->WorldContext = _WorldContext;
	};

protected:
	void CreateSystem(TSubclassOf<AActor> SystemClass);

private:
	UPROPERTY()
	TArray<AEntitySystem*> EntitiesContainer;

	UPROPERTY()
	ATrafficJamSimulationGameModeBase* WorldContext;
};
