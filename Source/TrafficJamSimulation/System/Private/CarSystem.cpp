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
	if (CheckCarCrash(InstanceIndex))
		return;

	FCarData* CarData = GetDataContainer().Find(InstanceIndex);
	SetSpeedModifier(InstanceIndex, CarData->CarAcceleration + CarData->SpeedModifier);
}

void ACarSystem::UpdateCarMovement(int InstanceIndex, bool bShouldRender)
{
	FCarData* CarData = GetDataContainer().Find(InstanceIndex);
	const FVector CarLocation = CarData->Transform.GetLocation();
	const FVector CarForwardVector = UKismetMathLibrary::GetForwardVector(CarData->Transform.GetRotation().Rotator()) *
		GetAccelerateValue(InstanceIndex, CarData->EngineSpeed);

	UKismetSystemLibrary::PrintString(this, "Location:" + FVector(CarLocation + CarForwardVector).ToString());
	UpdateInstanceLocation(InstanceIndex, CarLocation + CarForwardVector, bShouldRender);
}

void ACarSystem::PreventCarCrashSpeedModifier(int InstanceIndex, float Distance)
{
	EAccelerateMode AccMode;

	FCarData* CarData = GetDataContainer().Find(InstanceIndex);
	const int RoundLastCarDistance = FMath::RoundToInt(CarData->LastCarDistance / 10.f);
	const int RoundDistance = FMath::RoundToInt(Distance / 10.f);

	if (CarData->LastCarDistance == 0.f || RoundLastCarDistance > RoundDistance)
	{
		AccMode = EAccelerateMode::SlowDown;
	}
	else
	{
		AccMode = RoundLastCarDistance == RoundDistance ? EAccelerateMode::ConstSpeed : EAccelerateMode::SpeedUp;
	}

	CarData->LastCarDistance = Distance;
	DataContainer.Add(InstanceIndex, *CarData);

	const float NormalizeModifier = GetNormalizeModifier(
		GetRaycastCarDistance() / FMath::Clamp(Distance, 1.f, Distance));
	float AdditionalModifier = 0.f;
	switch (AccMode)
	{
	case EAccelerateMode::SlowDown:
		AdditionalModifier = NormalizeModifier * GetSpeedModifier(InstanceIndex) * 10.f;
		break;
	case EAccelerateMode::SpeedUp:
		AdditionalModifier = NormalizeModifier * -1.f;
		break;
	default:
		break;
	}

	SetSpeedModifier(InstanceIndex, GetSpeedModifier(InstanceIndex) + AdditionalModifier);
}

float ACarSystem::GetNormalizeModifier(float Value) const
{
	return Value * (1 / (GetRaycastCarDistance() - 1.f)) * -1.f;
}

#define ECC_Car ECC_GameTraceChannel1

bool ACarSystem::CheckCarCrash(int InstanceIndex)
{
	// LineTracing for search car channel object
	FVector StartLineTrace;
	FVector EndLineTrace;
	GetLineTracePoints(InstanceIndex, GetRaycastCarDistance(), StartLineTrace, EndLineTrace);

	FHitResult OutResult;
	const bool bIsHitting = UKismetSystemLibrary::LineTraceSingle(this, StartLineTrace, EndLineTrace,
	                                                              UEngineTypes::ConvertToTraceType(
		                                                              ECollisionChannel::ECC_Car),
	                                                              true, TArray<AActor*>(), EDrawDebugTrace::ForOneFrame,
	                                                              OutResult,
	                                                              false);

	if (!bIsHitting)
	{
		FCarData* CarData = GetDataContainer().Find(InstanceIndex);
		CarData->LastCarDistance = 0.f;
		return false;
	}

	PreventCarCrashSpeedModifier(InstanceIndex, FVector::Distance(StartLineTrace, OutResult.Location));
	return true;
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

float ACarSystem::GetAccelerateValue(int InstanceIndex, float Accelerate) const
{
	return Accelerate * GetSpeedModifier(InstanceIndex);
}

float ACarSystem::GetSpeedModifier(int InstanceIndex) const
{
	FCarData* LocalCarData = GetDataContainer().Find(InstanceIndex);
	return FMath::Clamp(LocalCarData->SpeedModifier, 0.f, 1.f);
}

void ACarSystem::SetSpeedModifier(int InstanceIndex, float SpeedModifier)
{
	FCarData* LocalCarData = DataContainer.Find(InstanceIndex);
	LocalCarData->SpeedModifier = FMath::Clamp(SpeedModifier, 0.f, 1.f);
	UKismetSystemLibrary::PrintString(this, "Modifier: " + FString::SanitizeFloat(LocalCarData->SpeedModifier));
}

void ACarSystem::UpdateSystem(int EntityIndex, bool bShouldRender)
{
	Super::UpdateSystem(EntityIndex, bShouldRender);

	const FCarData* CarData = GetDataContainer().Find(EntityIndex);
	if (CarData == nullptr || CheckFinishOverlap(EntityIndex))
		return;

	UpdateCarCrashPrevention(EntityIndex);
	UpdateCarMovement(EntityIndex, bShouldRender);
}

void ACarSystem::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	for (uint8 i = 0; i < GetDataContainer().Num(); i++)
		UpdateSystem(i, (GetDataContainer().Num() - 1) == i);
}

void ACarSystem::AddNewEntity_Implementation(FEntityData EntityData)
{
	Super::AddNewEntity_Implementation(EntityData);

	if (ViewEntities->GetStaticMesh() != nullptr)
		return;

	ViewEntities->SetStaticMesh(EntityData.ViewRepresentation);
	ViewEntities->SetCollisionResponseToChannel(ECollisionChannel::ECC_Car, ECollisionResponse::ECR_Block);
}

void ACarSystem::AddDataToContainer_Implementation(FEntityData Data)
{
	Super::AddDataToContainer_Implementation(Data);

	FCarData* LocalCarData = static_cast<FCarData*>(&Data);
	if (LocalCarData == nullptr)
		return;

	LocalCarData->EngineSpeed = UKismetMathLibrary::RandomFloatInRange(MinRandEngineSpeed, MaxRandEngineSpeed);
	LocalCarData->CarAcceleration = UKismetMathLibrary::RandomFloatInRange(
		MinRandCarAcceleration, MaxRandCarAcceleration);

	DataContainer.Add(GetDataContainer().Num(), *LocalCarData);
}

void ACarSystem::RemoveEntity_Implementation(int InstanceIndex)
{
	Super::RemoveEntity_Implementation(InstanceIndex);

	GetDataContainer().Remove(InstanceIndex);

	for (int i = InstanceIndex; i < GetDataContainer().Num(); i++)
	{
		FCarData Data = DataContainer.FindRef(i + 1);
		DataContainer.Remove(i + 1);
		DataContainer.Add(i, Data);
	}
}

void ACarSystem::UpdateInstanceLocation(int InstanceIndex, FVector Location, bool bShouldUpdateRender)
{
	FCarData* EntityData = DataContainer.Find(InstanceIndex);
	EntityData->Transform = FTransform(EntityData->Transform.GetRotation(), Location,
	                                   EntityData->Transform.GetScale3D());
	DataContainer.Add(InstanceIndex, *EntityData);
	ViewEntities->UpdateInstanceTransform(InstanceIndex, EntityData->Transform, true,
	                                      true, false);
}

FEntityData ACarSystem::GetDataByIndex_Implementation(int InstanceIndex) const
{
	return GetDataContainer().FindRef(InstanceIndex);
}
