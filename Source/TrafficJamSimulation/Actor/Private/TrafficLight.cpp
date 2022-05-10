// Fill out your copyright notice in the Description page of Project Settings.


#include "TrafficJamSimulation/Actor/Public/TrafficLight.h"


// Sets default values
ATrafficLight::ATrafficLight()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATrafficLight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrafficLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

