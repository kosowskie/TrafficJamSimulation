// Copyright Epic Games, Inc. All Rights Reserved.


#include "TrafficJamSimulation/Core/Public/TrafficJamSimulationGameModeBase.h"

#include "Kismet/GameplayStatics.h"
#include "TrafficJamSimulation/EntityComponentSystem/Public/EntityInterface.h"

class IEntityInterface;

ATrafficJamSimulationGameModeBase::ATrafficJamSimulationGameModeBase()
{
}

void ATrafficJamSimulationGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	StartEntityManager();
}

void ATrafficJamSimulationGameModeBase::StartEntityManager()
{
	SetEntityManager(NewObject<UEntityManager>(UEntityManager::StaticClass()));

	if (!GetEntityManager())
		return;

	TArray<AActor*> EntityActors;
	UGameplayStatics::GetAllActorsWithInterface(this, UEntityInterface::StaticClass(), EntityActors);

	GetEntityManager()->InitializeManager(EntityActors);

	OnEntityManagerInitialize.Execute();
}
