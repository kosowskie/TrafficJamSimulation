// Copyright Epic Games, Inc. All Rights Reserved.


#include "TrafficJamSimulation/EntityComponentSystem/Public/EntityManager.h"

#include "TrafficJamSimulation/EntityComponentSystem/Public/EntityInterface.h"
#include "TrafficJamSimulation/EntityComponentSystem/Public/EntitySystem.h"

class ATrafficJamSimulationGameModeBase;

UEntityManager::UEntityManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UEntityManager::InitializeManager(TArray<AActor*> Entities)
{
	InitializeSystems();

	for(AActor* Entity : Entities)
	{
		if(!Entity->GetClass()->ImplementsInterface(UEntityInterface::StaticClass()))
			continue;
		
		FEntityData EntityData = IEntityInterface::Execute_GetData(Entity);
		for(AEntitySystem* EntitySystem : GetEntitiesContainer())
		{
			if(EntitySystem->DataType != EntityData.Id)
				continue;

			EntitySystem->AddNewEntity(EntityData);
			Entity->Destroy();
			break;
		}
	}
}

void UEntityManager::CreateSystem(TSubclassOf<AEntitySystem> SystemClass)
{
	check(GEngine);
	
	AEntitySystem* EntitySystem = GEngine->GetWorld()->SpawnActor<AEntitySystem>(SystemClass);
	EntitiesContainer.Add(EntitySystem);
}
