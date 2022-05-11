// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TrafficJamSimulation/EntityComponentSystem/Public/EntityManager.h"
#include "TrafficJamSimulation/System/Public/CarSystem.h"

#include "TrafficJamSimulationEntityManager.generated.h"

UCLASS(Blueprintable, BlueprintType, EditInlineNew)
class TRAFFICJAMSIMULATION_API UTrafficJamSimulationEntityManager : public UEntityManager
{
	GENERATED_BODY()

	
public:
	UTrafficJamSimulationEntityManager();
	
	UTrafficJamSimulationEntityManager(const FObjectInitializer& ObjectInitializer);

	virtual void InitializeSystems() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACarSystem> CarSystemClass;
};
