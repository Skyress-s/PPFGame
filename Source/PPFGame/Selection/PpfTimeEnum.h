// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ETimeMode : uint8
{
	None UMETA(DisplayName = "None"),
	Future UMETA(DisplayName = "Future"),
	Present UMETA(DisplayName = "Present"),
	Past UMETA(DisplayName = "Past")
};
namespace TimeMode {

// Return the next state.
ETimeMode GetNextState(const ETimeMode Current, const ETimeMode Applied);
}
