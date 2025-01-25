// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PpfTimeEnum.h"
#include "UObject/Interface.h"
#include "SelectableInterface.generated.h"

enum class EPpfTime : uint8;

// This class does not need to be modified.
UINTERFACE()
class USelectableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PPFGAME_API ISelectableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// Checks if the object can be selected.
	virtual bool TrySelect(){ return false; }

	EPpfTime OnSelect(const EPpfTime Time) { return EPpfTime::None; }
};
