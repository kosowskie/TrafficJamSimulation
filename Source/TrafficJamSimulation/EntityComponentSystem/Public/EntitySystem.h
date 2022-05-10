// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EntityManager.h"
#include "GameFramework/GameModeBase.h"
#include "EntitySystem.generated.h"

UCLASS()
class TRAFFICJAMSIMULATION_API AEntitySystem : public AActor
{
	GENERATED_BODY()

public:
	AEntitySystem();
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	USceneComponent* MyRootComponent;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UInstancedStaticMeshComponent* ViewEntities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DataType;
	
	UFUNCTION()
	void UpdateInstanceLocation(int InstanceIndex, FVector Location, bool bShouldUpdateRender = false);
	
	virtual void AddDataToContainer(int32* Index, FEntityData Data);
	
	void AddNewEntity(FEntityData EntityData);
	void RemoveEntity(int InstanceIndex) const;
	
	TMap<int*, FEntityData> GetDataContainer() const
	{
		return DataContainer;
	};

	void SetDataContainer(const TMap<int*, FEntityData>& _DataContainer)
	{
		this->DataContainer = _DataContainer;
	};
	
	
private:
	TMap<int*, FEntityData> DataContainer;
};
