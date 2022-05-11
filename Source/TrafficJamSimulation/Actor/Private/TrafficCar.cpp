// Fill out your copyright notice in the Description page of Project Settings.


#include "TrafficJamSimulation/Actor/Public/TrafficCar.h"

#include "TrafficJamSimulation/Data/CarData.h"

// Sets default values
ATrafficCar::ATrafficCar()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(MyRootComponent);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(MyRootComponent);
}

FEntityData ATrafficCar::GetData_Implementation()
{
	return FEntityData(Id, MeshComponent->GetStaticMesh(), GetActorTransform());
}
