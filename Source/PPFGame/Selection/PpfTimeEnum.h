// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

namespace EPpfTime {
/**
 * 
 */
UENUM(BlueprintType)
enum class EType : uint8
{
	None UMETA(DisplayName = "None"),
	Future UMETA(DisplayName = "Future"),
	Present UMETA(DisplayName = "Present"),
	Past UMETA(DisplayName = "Past")
};



// Return the next state.
EType GetNextState(const EType Current, const EType Applied);
}
