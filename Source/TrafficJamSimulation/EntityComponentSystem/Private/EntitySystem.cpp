// Copyright Epic Games, Inc. All Rights Reserved.


#include "TrafficJamSimulation/EntityComponentSystem/Public/EntitySystem.h"

#include "Kismet/KismetSystemLibrary.h"
#include "TrafficJamSimulation/Data/CarData.h"

AEntitySystem::AEntitySystem()
{
	PrimaryActorTick.bCanEverTick = true;

	MyRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(MyRootComponent);

	ViewEntities = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("ViewEntities"));
	ViewEntities->SetupAttachment(MyRootComponent);
}

void AEntitySystem::UpdateInstanceLocation(int InstanceIndex, FVector Location, bool bShouldUpdateRender)
{
}

void AEntitySystem::AddNewEntity_Implementation(FEntityData EntityData)
{
	ViewEntities->AddInstance(EntityData.Transform);
	AddDataToContainer_Implementation(EntityData);
}

void AEntitySystem::RemoveEntity_Implementation(int InstanceIndex)
{
	ViewEntities->RemoveInstance(InstanceIndex);
}
