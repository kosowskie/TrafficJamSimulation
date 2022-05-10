// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "DestroyCar.generated.h"

UCLASS()
class TRAFFICJAMSIMULATION_API ADestroyCar : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADestroyCar();
	
	UPROPERTY(Category = CarCollision, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* MyRootComponent;
	
	UPROPERTY(Category = CarCollision, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxComponent;
	
};
