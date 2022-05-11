// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrafficJamSimulation/EntityComponentSystem/Public/EntityManager.h"

#include "CarData.generated.h"

USTRUCT()
struct FCarData : public FEntityData
{
	GENERATED_BODY()

	
	UPROPERTY()
	float EngineSpeed;

	UPROPERTY()
	float CarAcceleration;

	UPROPERTY()
	float SpeedModifier;

	UPROPERTY()
	float LastCarDistance;

	FCarData(): EngineSpeed(0.f), CarAcceleration(0.f), SpeedModifier(0.f), LastCarDistance(0.f)
	{
	}
	
	FCarData(FString _Id, UStaticMesh* _ViewRepresentation, FTransform _Transform) : Super(_Id, _ViewRepresentation,
		_Transform), EngineSpeed(0.f), CarAcceleration(0.f), SpeedModifier(0.f), LastCarDistance(0.f)
	{
	}

	FCarData(FString _Id, UStaticMesh* _ViewRepresentation, FTransform _Transform,
	         float _EngineSpeed, float _CarAcceleration, float _SpeedModifier,
	         float _LastCarDistance) :
		Super(_Id, _ViewRepresentation, _Transform), EngineSpeed(_EngineSpeed),
		CarAcceleration(_CarAcceleration), SpeedModifier(_SpeedModifier),
		LastCarDistance(_LastCarDistance)
	{
	}
};
