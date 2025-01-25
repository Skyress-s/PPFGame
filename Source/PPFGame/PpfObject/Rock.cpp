// Fill out your copyright notice in the Description page of Project Settings.


#include "Rock.h"

#include "Logging/StructuredLog.h"
DEFINE_LOG_CATEGORY_STATIC(LogRock, Log, All);

// Sets default values
ARock::ARock()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

bool ARock::TrySelect()
{
	UE_LOGFMT(LogRock, Log, "Rock Was Try Selected");
	return ISelectableInterface::TrySelect();
}

EPpfTime ARock::OnSelect(const EPpfTime Time)
{
	UE_LOGFMT(LogRock, Log, "Rock Was Selected");

	
	return EPpfTime::Present;
}

