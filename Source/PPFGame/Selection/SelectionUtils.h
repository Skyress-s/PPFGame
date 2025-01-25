// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject/Object.h"
#include "SelectionUtils.generated.h"

class ISelectableInterface;
/**
 * 
 */
UCLASS()
class PPFGAME_API USelectionUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static TArray<ISelectableInterface*> QuerySelectableObjectsInCone(const UObject& WorldContextObject, const FVector2D& Location, const FVector2D& Direction,
	                                                                  const float Degrees, const float Range);
};
