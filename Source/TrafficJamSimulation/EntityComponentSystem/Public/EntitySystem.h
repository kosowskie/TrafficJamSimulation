// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EntityManagement.h"
#include "GameFramework/GameModeBase.h"

#include "EntitySystem.generated.h"

UCLASS()
class TRAFFICJAMSIMULATION_API AEntitySystem : public AActor, public IEntityManagement
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
	
	virtual void UpdateInstanceLocation(int InstanceIndex, FVector Location, bool bShouldUpdateRender = false);

	UFUNCTION(BlueprintNativeEvent)
	void AddNewEntity(FEntityData EntityData);
	virtual void AddNewEntity_Implementation(FEntityData EntityData) override;
	
	UFUNCTION(BlueprintNativeEvent)
	void RemoveEntity(int InstanceIndex);
	virtual void RemoveEntity_Implementation(int InstanceIndex) override;
	
protected:
	virtual void UpdateSystem(int EntityIndex, bool bShouldRender){};
};
