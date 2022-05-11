// Fill out your copyright notice in the Description page of Project Settings.


#include "TrafficJamSimulation/Core/Public/TrafficJamSimulationEntityManager.h"

#include "TrafficJamSimulation/System/Public/CarSystem.h"

UTrafficJamSimulationEntityManager::UTrafficJamSimulationEntityManager() : Super()
{
}

UTrafficJamSimulationEntityManager::UTrafficJamSimulationEntityManager(
	const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UTrafficJamSimulationEntityManager::InitializeSystems()
{
	Super::InitializeSystems();

	CreateSystem(CarSystemClass);
}