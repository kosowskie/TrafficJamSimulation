// Copyright Epic Games, Inc. All Rights Reserved.


#include "TrafficJamSimulation/EntityComponentSystem/Public/EntityManager.h"

#include "TrafficJamSimulation/Core/Public/TrafficJamSimulationGameModeBase.h"
#include "TrafficJamSimulation/EntityComponentSystem/Public/EntityInterface.h"
#include "TrafficJamSimulation/EntityComponentSystem/Public/EntitySystem.h"
#include "TrafficJamSimulation/System/Public/CarSystem.h"

class ACarSystem;
class ATrafficJamSimulationGameModeBase;

UEntityManager::UEntityManager() : Super()
{
}

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

			EntitySystem->AddNewEntity_Implementation(EntityData);
			Entity->Destroy();
			break;
		}
	}
}

void UEntityManager::CreateSystem(TSubclassOf<AActor> SystemClass)
{
	ensure(GetWorldContext());
	
	ACarSystem* EntitySystem = GetWorldContext()->GetWorld()->SpawnActor<ACarSystem>(SystemClass);
	EntitiesContainer.Add(CastChecked<AEntitySystem>(EntitySystem));
}
