// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "PresentIndicator.generated.h"

/**
 * 
 */
UCLASS()
class PPFGAME_API UPresentIndicator : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	// nthis is a dogshit name
	void NotifyOfVector(const FVector& Vector);
	void Enable();
	void Disable();


	UPROPERTY(BlueprintReadOnly)
	FVector m_Vector = FVector::ZeroVector;
};
