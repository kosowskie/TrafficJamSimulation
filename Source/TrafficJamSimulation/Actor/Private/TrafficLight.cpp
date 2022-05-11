// Fill out your copyright notice in the Description page of Project Settings.


#include "TrafficJamSimulation/Actor/Public/TrafficLight.h"

// Sets default values
ATrafficLight::ATrafficLight()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(MyRootComponent);

	FirstCrossoverContainerComponent = CreateDefaultSubobject<
		USceneComponent>(TEXT("FirstCrossoverContainerComponent"));
	FirstCrossoverContainerComponent->SetupAttachment(MyRootComponent);

	SecondCrossoverContainerComponent = CreateDefaultSubobject<USceneComponent>(
		TEXT("SecondCrossoverContainerComponent"));
	SecondCrossoverContainerComponent->SetupAttachment(MyRootComponent);
}

// Called when the game starts or when spawned
void ATrafficLight::BeginPlay()
{
	Super::BeginPlay();

	// Getting children from containers and binding to local arrays
	TArray<USceneComponent*> FirstCrossoverChildren;
	FirstCrossoverContainerComponent->GetChildrenComponents(false, FirstCrossoverChildren);
	for (USceneComponent* Child : FirstCrossoverChildren)
	{
		if (UStaticMeshComponent* FirstCrossoverLight = Cast<UStaticMeshComponent>(Child))
			FirstCrossoverLights.Add(FirstCrossoverLight);
	}

	TArray<USceneComponent*> SecondCrossoverChildren;
	SecondCrossoverContainerComponent->GetChildrenComponents(false, SecondCrossoverChildren);
	for (USceneComponent* Child : SecondCrossoverChildren)
	{
		if (UStaticMeshComponent* SecondCrossoverLight = Cast<UStaticMeshComponent>(Child))
			SecondCrossoverLights.Add(SecondCrossoverLight);
	}

	StartLights(ELightsMode::FirstCrossoverOrange);
}

void ATrafficLight::StartLights(ELightsMode LightsMode)
{
	float Timer = 0.f;
	// initialize to SecondCrossoverGreen to prevent boilerplate in SecondCrossoverOrange
	ELightsMode NextLightsMode = ELightsMode::SecondCrossoverGreen;

	// Changing light and bind next mode
	switch (LightsMode)
	{
	case ELightsMode::FirstCrossoverGreen:
		for (UStaticMeshComponent* Light : FirstCrossoverLights)
			ChangeLight(Light, true);
		Timer = FirstCrossoverTime;
		NextLightsMode = ELightsMode::SecondCrossoverOrange;
		break;
	case ELightsMode::SecondCrossoverGreen:
		for (UStaticMeshComponent* Light : SecondCrossoverLights)
			ChangeLight(Light, true);
		Timer = SecondCrossoverTime;
		NextLightsMode = ELightsMode::FirstCrossoverOrange;
		break;
	case ELightsMode::FirstCrossoverOrange:
		NextLightsMode = ELightsMode::FirstCrossoverGreen;
	case ELightsMode::SecondCrossoverOrange:
		{
			TArray<UStaticMeshComponent*> AllLights;
			AllLights.Append(FirstCrossoverLights);
			AllLights.Append(SecondCrossoverLights);
			for (UStaticMeshComponent* Light : AllLights)
				ChangeLight(Light, false);
			Timer = AllRedTime;
			break;
		}
	default:
		break;
	}

	// Timer for next light mode
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda([this, NextLightsMode]()
	{
		StartLights(NextLightsMode);
	});
	GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, Timer, false);
}

#define ECC_Car ECC_GameTraceChannel1

void ATrafficLight::ChangeLight(UStaticMeshComponent* MeshComponent, bool bSetToGreen)
{
	MeshComponent->SetMaterial(0, bSetToGreen ? GreenLightMaterial : RedLightMaterial);
	MeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Car,
	                                             bSetToGreen
		                                             ? ECollisionResponse::ECR_Ignore
		                                             : ECollisionResponse::ECR_Block);
}
