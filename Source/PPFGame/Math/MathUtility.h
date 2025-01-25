// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MathUtility.generated.h"

/**
 * 
 */
UCLASS()
class PPFGAME_API UMathUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static float AngleVectors(const FVector& Vector1, const FVector& Vector2);

	static float AngleVectorsSigned(const FVector& Vector1, const FVector& Vector2, const FVector& UpVector);
};
