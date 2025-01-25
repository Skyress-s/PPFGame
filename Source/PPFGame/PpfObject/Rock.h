// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PPFGame/Selection/SelectableInterface.h"
#include "Rock.generated.h"

UCLASS()
class PPFGAME_API ARock : public AActor, public ISelectableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARock();
	// ISelectableInterface START
public:
	// Checks if the object can be selected.
	virtual bool TrySelect();

	EPpfTime::EType OnSelect(const EPpfTime::EType Time);
	// ISelectableInterface END
public:
	EPpfTime::EType m_CurrentPpfTime = EPpfTime::EType::Present;
};
