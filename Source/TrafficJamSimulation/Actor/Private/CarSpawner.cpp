// Fill out your copyright notice in the Description page of Project Settings.


#include "TrafficJamSimulation/Actor/Public/CarSpawner.h"

#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "TrafficJamSimulation/Core/Public/TrafficJamSimulationEntityManager.h"
#include "TrafficJamSimulation/Core/Public/TrafficJamSimulationGameModeBase.h"
#include "TrafficJamSimulation/Data/CarData.h"
#include "TrafficJamSimulation/EntityComponentSystem/Public/EntitySystem.h"
#include "TrafficJamSimulation/System/Public/CarSystem.h"

// Sets default values
ACarSpawner::ACarSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ACarSpawner::SpawningEntities()
{
	SpawnCarEntity();

	FTimerHandle TimerHandle;
	const float SpawnTime = FMath::RandRange(MinRandSpawnTimer, MaxRandSpawnTimer);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ACarSpawner::SpawningEntities, SpawnTime);
}

void ACarSpawner::SpawnCarEntity() const
{
	GetCarSystem()->AddNewEntity_Implementation(FCarData(CarId, CarMesh, GetActorTransform()));
}

// Called when the game starts or when spawned
void ACarSpawner::BeginPlay()
{
	Super::BeginPlay();

	BindCarEntitySystem();
}

void ACarSpawner::FindCarEntitySystem(ATrafficJamSimulationGameModeBase* ProjectGameMode)
{
	for (AEntitySystem* EntitySystem : ProjectGameMode->GetEntityManager()->GetEntitiesContainer())
	{
		if (!EntitySystem->GetClass()->IsChildOf(ACarSystem::StaticClass()))
			continue;

		SetCarSystem(Cast<ACarSystem>(EntitySystem));
		break;
	}
}

void ACarSpawner::BindCarEntitySystem()
{
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
	check(GameMode);

	ATrafficJamSimulationGameModeBase* ProjectGameMode = Cast<ATrafficJamSimulationGameModeBase>(GameMode);
	if (!ProjectGameMode->GetEntityManager())
	{
		ProjectGameMode->OnEntityManagerInitialize.AddLambda([this]()
		{
			ATrafficJamSimulationGameModeBase* ProjectGameMode = Cast<ATrafficJamSimulationGameModeBase>(
				UGameplayStatics::GetGameMode(this));
			FindCarEntitySystem(ProjectGameMode);
			SpawningEntities();
		});
		return;
	}

	FindCarEntitySystem(ProjectGameMode);
	SpawningEntities();
}
