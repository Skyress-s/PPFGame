// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PpfPawnStats.generated.h"

class UPhysicalMaterial;

/**
 * 
 */
UCLASS()
class PPFGAME_API UPpfPawnStats : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (ClampMin = "0.0"))
	float m_JumpSpeed{1000.0f};

	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (ClampMin = "0.0"))
	float m_GroundCheckDistance = 50.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (ClampMin = "0.0"))
	float m_MovementBreakingSpeed = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (ClampMin = "0.0"))
	float m_MovementAcceleration = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (ClampMin = "0.0", Tooltip = "Max speed in u/s."))
	float m_MovementGroundedMaxSpeed = 500.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (ClampMin = "0.0", Tooltip = "Max speed in u/s."))
	float m_ScanDegrees = 30.0f;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionDetection", meta = (ClampMin = "0.0"))
	float m_WallDetectionDistance = 50.0f;


	UPROPERTY(EditDefaultsOnly, Category = "Physics")
	TObjectPtr<UPhysicalMaterial> m_GlidePhysMat{};

	UPROPERTY(EditDefaultsOnly, Category = "Physics")
	TObjectPtr<UPhysicalMaterial> m_StickPhysMat{};
};
