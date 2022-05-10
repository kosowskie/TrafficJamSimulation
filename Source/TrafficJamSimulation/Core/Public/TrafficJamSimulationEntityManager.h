// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrafficJamSimulation/EntityComponentSystem/Public/EntityManager.h"
#include "UObject/Object.h"
#include "TrafficJamSimulationEntityManager.generated.h"

UCLASS()
class TRAFFICJAMSIMULATION_API UTrafficJamSimulationEntityManager : public UEntityManager
{
	GENERATED_BODY()

	
public:
	UTrafficJamSimulationEntityManager(const FObjectInitializer& ObjectInitializer);
	
	virtual void InitializeSystems() override;
};
