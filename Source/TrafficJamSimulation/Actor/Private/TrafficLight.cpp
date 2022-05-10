// Fill out your copyright notice in the Description page of Project Settings.


#include "TrafficJamSimulation/Actor/Public/TrafficLight.h"

#include "Kismet/KismetMathLibrary.h"


// Sets default values
ATrafficLight::ATrafficLight()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(MyRootComponent);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(MyRootComponent);
}

// Called when the game starts or when spawned
void ATrafficLight::BeginPlay()
{
	Super::BeginPlay();

	UKismetMathLibrary::RandomBool() ? SetRedLight() : SetGreenLight();
}

#define ECC_Car ECC_GameTraceChannel1

void ATrafficLight::SetRedLight()
{
	MeshComponent->SetMaterial(0, RedLightMaterial);
	MeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Car, ECollisionResponse::ECR_Block);
	
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATrafficLight::SetGreenLight, RedLightTime);
}

void ATrafficLight::SetGreenLight()
{
	MeshComponent->SetMaterial(0, GreenLightMaterial);
	MeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Car, ECollisionResponse::ECR_Ignore);
	
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATrafficLight::SetRedLight, GreenLightTime);
}
