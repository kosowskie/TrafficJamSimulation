// Fill out your copyright notice in the Description page of Project Settings.

#include "TrafficJamSimulation/System/Public/CarSystem.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TrafficJamSimulation/Data/CarData.h"

ACarSystem::ACarSystem()
{
}

#define ECC_Finish ECC_GameTraceChannel2

bool ACarSystem::CheckFinishOverlap(int InstanceIndex)
{
	// LineTracing for search finish channel object
	FVector StartLineTrace;
	FVector EndLineTrace;
	GetLineTracePoints(InstanceIndex, GetRaycastFinishDistance(), StartLineTrace, EndLineTrace);

	FHitResult OutResult;
	const bool bIsHitting = UKismetSystemLibrary::LineTraceSingle(this, StartLineTrace, EndLineTrace,
	                                                              UEngineTypes::ConvertToTraceType(
		                                                              ECollisionChannel::ECC_Finish),
	                                                              true, TArray<AActor*>(), EDrawDebugTrace::None,
	                                                              OutResult,
	                                                              true);

	if (!bIsHitting)
		return false;

	// Deleting Entity when reach Finish
	RemoveEntity(InstanceIndex);
	return true;
}

void ACarSystem::UpdateCarCrashPrevention(int InstanceIndex)
{
	if(CheckCarCrash(InstanceIndex))
		return;

	SetSpeedModifier(InstanceIndex, CarData->CarAcceleration + CarData->SpeedModifier);
}

bool ACarSystem::CheckCarCrash(int InstanceIndex)
{
	// TODO: Check Car Crash From Blueprint
	return false;
}

void ACarSystem::GetLineTracePoints(int InstanceIndex, float Length, FVector& OutStart, FVector& OutEnd) const
{
	FTransform InstanceTransform;
	ViewEntities->GetInstanceTransform(InstanceIndex, InstanceTransform);

	const FVector ActualInstanceLocation = InstanceTransform.GetLocation();
	const FVector ActualForwardVector = UKismetMathLibrary::GetForwardVector(InstanceTransform.GetRotation().Rotator());

	OutStart = ActualForwardVector * RaycastBegin + ActualInstanceLocation;
	OutStart.Z += ZFixedLocation;

	OutEnd = ActualForwardVector * Length + OutStart;
}

float ACarSystem::GetSpeedModifier(int InstanceIndex) const
{
	const FCarData* LocalCarData = static_cast<FCarData*>(GetDataContainer().Find(&InstanceIndex));
	return FMath::Clamp(LocalCarData->SpeedModifier, 0.f, 1.f);
}

void ACarSystem::SetSpeedModifier(int InstanceIndex, float SpeedModifier)
{
	FCarData* LocalCarData = static_cast<FCarData*>(GetDataContainer().Find(&InstanceIndex));
	LocalCarData->SpeedModifier = FMath::Clamp(SpeedModifier, 0.f, 1.f);
}

void ACarSystem::UpdateSystem(int EntityIndex, bool bShouldRender)
{
	Super::UpdateSystem(EntityIndex, bShouldRender);

	FEntityData* EntityData = GetDataContainer().Find(&EntityIndex);
	CarData = static_cast<FCarData*>(EntityData);
	
	if (CarData == nullptr || CheckFinishOverlap(EntityIndex))
		return;

	UpdateCarCrashPrevention(EntityIndex);
}

#define ECC_Car ECC_GameTraceChannel1

void ACarSystem::AddNewEntity(FEntityData EntityData)
{
	Super::AddNewEntity(EntityData);

	if(ViewEntities->GetStaticMesh() != nullptr)
		return;

	ViewEntities->SetStaticMesh(EntityData.ViewRepresentation);
	ViewEntities->SetCollisionResponseToChannel(ECollisionChannel::ECC_Car, ECollisionResponse::ECR_Block);
}

void ACarSystem::AddDataToContainer(int32* Index, FEntityData Data)
{
	if(Data.StaticStruct() != FCarData::StaticStruct())
		return;
	
	FCarData* LocalCarData = static_cast<FCarData*>(&Data);
	LocalCarData->EngineSpeed = UKismetMathLibrary::RandomFloatInRange(MinRandEngineSpeed, MaxRandEngineSpeed);
	LocalCarData->CarAcceleration = UKismetMathLibrary::RandomFloatInRange(MinRandCarAcceleration, MaxRandCarAcceleration);
	
	Super::AddDataToContainer(Index, *LocalCarData);
}
