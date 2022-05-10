// Fill out your copyright notice in the Description page of Project Settings.


#include "TrafficJamSimulation/Actor/Public/DestroyCar.h"


// Sets default values
ADestroyCar::ADestroyCar()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADestroyCar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestroyCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

