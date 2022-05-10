// Copyright Epic Games, Inc. All Rights Reserved.


#include "TrafficJamSimulation/EntityComponentSystem/Public/EntitySystem.h"

#include "TrafficJamSimulation/Data/CarData.h"

AEntitySystem::AEntitySystem()
{
	PrimaryActorTick.bCanEverTick = true;

	MyRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(MyRootComponent);

	ViewEntities = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("ViewEntities"));
	ViewEntities->SetupAttachment(MyRootComponent);
}

void AEntitySystem::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TArray<int*> Indexes;
	GetDataContainer().GetKeys(Indexes);

	for(const int* Index : Indexes)
		UpdateSystem(*Index, Indexes.Last() == Index);
}

void AEntitySystem::UpdateInstanceLocation(int InstanceIndex, FVector Location, bool bShouldUpdateRender)
{
	FEntityData* EntityData = DataContainer.Find(&InstanceIndex);
	EntityData->Transform.SetLocation(Location);
	ViewEntities->UpdateInstanceTransform(InstanceIndex, EntityData->Transform, true, bShouldUpdateRender, true);
}

void AEntitySystem::AddDataToContainer(int32* Index, FEntityData Data)
{
	DataContainer.Add(Index, Data);
}

void AEntitySystem::AddNewEntity(FEntityData EntityData)
{
	AddDataToContainer(reinterpret_cast<int32*>(ViewEntities->AddInstance(EntityData.Transform)), EntityData);
}

void AEntitySystem::RemoveEntity(int InstanceIndex) const
{
	ViewEntities->RemoveInstance(InstanceIndex);
}
