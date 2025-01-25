// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EPpfTime : uint8
{
	None UMETA(DisplayName = "None"),
	Future UMETA(DisplayName = "Future"),
	Present UMETA(DisplayName = "Present"),
	Past UMETA(DisplayName = "Past")
};
