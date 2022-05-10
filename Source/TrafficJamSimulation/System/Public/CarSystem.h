// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrafficJamSimulation/EntityComponentSystem/Public/EntitySystem.h"
#include "CarSystem.generated.h"


struct FCarData;
UCLASS()
class TRAFFICJAMSIMULATION_API ACarSystem : public AEntitySystem
{
	GENERATED_BODY()


public:
	ACarSystem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Raycasting")
	float RaycastBegin = 250.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Raycasting")
	float RaycastCarDistance = 4000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Raycasting")
	float RaycastFinishDistance = 30.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Raycasting")
	float ZFixedLocation = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed",
		meta = (ClampMin = "0.0", ClampMax = "300.0", UIMin = "0.0", UIMax = "300.0"))
	float MinRandEngineSpeed = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed",
		meta = (ClampMin = "0.0", ClampMax = "300.0", UIMin = "0.0", UIMax = "300.0"))
	float MaxRandEngineSpeed = 80.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed",
		meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MinRandCarAcceleration = 0.001f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed",
		meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MaxRandCarAcceleration = 0.002f;

	UFUNCTION()
	void GetLineTracePoints(int InstanceIndex, float Length, FVector& OutStart, FVector& OutEnd) const;

	UFUNCTION()
	float GetRaycastCarDistance() const
	{
		return RaycastCarDistance + RaycastBegin;
	};

	UFUNCTION()
	float GetRaycastFinishDistance() const
	{
		return RaycastFinishDistance + RaycastBegin;
	};

	UFUNCTION()
	float GetSpeedModifier(int InstanceIndex) const;

	UFUNCTION()
	void SetSpeedModifier(int InstanceIndex, float SpeedModifier);
	
	virtual void AddNewEntity(FEntityData EntityData) override;
	virtual void AddDataToContainer(int32* Index, FEntityData Data) override;

protected:
	virtual void UpdateSystem(int EntityIndex, bool bShouldRender) override;

private:
	bool CheckFinishOverlap(int InstanceIndex);

	void UpdateCarCrashPrevention(int InstanceIndex);
	bool CheckCarCrash(int InstanceIndex);

	FCarData* CarData;
};
