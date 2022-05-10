// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TrafficJamSimulation/EntityComponentSystem/Public/EntityManager.h"
#include "TrafficJamSimulationGameModeBase.generated.h"

DECLARE_DELEGATE(FOnEntityManagerInitialize)

UCLASS()
class TRAFFICJAMSIMULATION_API ATrafficJamSimulationGameModeBase : public AGameModeBase
{
	GENERATED_BODY()


public:
	ATrafficJamSimulationGameModeBase();

	UFUNCTION()
	void StartEntityManager();

	UEntityManager* GetEntityManager() const
	{
		return EntityManager;
	};

	void SetEntityManager(UEntityManager* _EntityManager)
	{
		this->EntityManager = _EntityManager;
	};
	
	FOnEntityManagerInitialize OnEntityManagerInitialize;

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY()
	UEntityManager* EntityManager;
};
