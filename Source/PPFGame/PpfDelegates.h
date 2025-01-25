// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEnterFuture, const FVector& /*, Velocity*/);

/**
 * 
 */
class PPFGAME_API PpfDelegates
{
public:
	PpfDelegates();
	~PpfDelegates();
};
