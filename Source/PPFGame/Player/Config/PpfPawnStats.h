// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PpfPawnStats.generated.h"

/**
 * 
 */
UCLASS()
class PPFGAME_API UPpfPawnStats : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (ClampMin = "0.0"))
	float m_JumpSpeed { 1000.0f };
};
