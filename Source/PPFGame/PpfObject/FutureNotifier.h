﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PPFGame/PpfDelegates.h"
#include "FutureNotifier.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PPFGAME_API UFutureNotifier : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFutureNotifier();

	
	FOnEnterFuture m_OnEnterFuture;
	
};
