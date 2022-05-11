// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrafficLight.generated.h"

class UBoxComponent;

UENUM()
enum class ELightsMode : uint8
{
	FirstCrossoverGreen = 0 UMETA(DisplayName = "FirstCrossoverGreen"),
	SecondCrossoverGreen = 1 UMETA(DisplayName = "SecondCrossoverGreen"),
	FirstCrossoverOrange = 2 UMETA(DisplayName = "FirstCrossoverOrange"),
	SecondCrossoverOrange = 3 UMETA(DisplayName = "SecondCrossoverOrange"),
};

UCLASS()
class TRAFFICJAMSIMULATION_API ATrafficLight : public AActor
{
	GENERATED_BODY()

public:
	ATrafficLight();

	// Components
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* MyRootComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* FirstCrossoverContainerComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* SecondCrossoverContainerComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timers")
	float FirstCrossoverTime = 15.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timers")
	float SecondCrossoverTime = 15.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timers")
	float AllRedTime = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInterface* RedLightMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInterface* GreenLightMaterial;

	/* Starting All Light Logic with starting specific Mode
	* @param  LightsMode		Change LightMode from ELightsMode enum
	*/
	UFUNCTION()
	void StartLights(ELightsMode LightsMode);

	/* Changing Light to red or green
	* @param  MeshComponent		Mesh Component to change Material and collision preset
	* @param  bSetToGreen		If true setting to green otherwise red
	*/
	UFUNCTION()
	void ChangeLight(UStaticMeshComponent* MeshComponent, bool bSetToGreen);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Binding Crossover Lists to prevent iteration every time we changing lights
	UPROPERTY()
	TArray<UStaticMeshComponent*> FirstCrossoverLights;

	UPROPERTY()
	TArray<UStaticMeshComponent*> SecondCrossoverLights;
};
