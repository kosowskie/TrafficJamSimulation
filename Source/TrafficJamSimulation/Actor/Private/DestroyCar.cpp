// Fill out your copyright notice in the Description page of Project Settings.


#include "TrafficJamSimulation/Actor/Public/DestroyCar.h"

#define ECC_Finish ECC_GameTraceChannel2

// Sets default values
ADestroyCar::ADestroyCar()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(MyRootComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(MyRootComponent);
	BoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Finish, ECollisionResponse::ECR_Block);
}

