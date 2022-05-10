// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EntityManager.h"
#include "UObject/Interface.h"
#include "EntityInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEntityInterface : public UInterface
{
	GENERATED_BODY()
};

class TRAFFICJAMSIMULATION_API IEntityInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	FEntityData GetData();
};
