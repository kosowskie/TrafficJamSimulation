// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TrafficJamSimulationGameModeBase.generated.h"

class UTrafficJamSimulationEntityManager;

DECLARE_DELEGATE(FOnEntityManagerInitialize)

UCLASS()
class TRAFFICJAMSIMULATION_API ATrafficJamSimulationGameModeBase : public AGameModeBase
{
	GENERATED_BODY()


public:
	ATrafficJamSimulationGameModeBase();

	UFUNCTION()
	void StartEntityManager();

	UTrafficJamSimulationEntityManager* GetEntityManager() const
	{
		return EntityManager;
	};

	void SetEntityManager(UTrafficJamSimulationEntityManager* _EntityManager)
	{
		this->EntityManager = _EntityManager;
	};
	
	FOnEntityManagerInitialize OnEntityManagerInitialize;

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY()
	UTrafficJamSimulationEntityManager* EntityManager;
};
