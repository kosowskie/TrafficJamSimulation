// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrafficLight.generated.h"

class UBoxComponent;
UCLASS()
class TRAFFICJAMSIMULATION_API ATrafficLight : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATrafficLight();
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* MyRootComponent;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RedLightTime = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GreenLightTime = 10.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* RedLightMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* GreenLightMaterial;

	UFUNCTION()
	void SetRedLight();

	UFUNCTION()
	void SetGreenLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
