// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputMappingContext.h"
#include "PPFPlayerInputConfig.generated.h"

class UInputAction;

USTRUCT()
struct FInputActionEntry {
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> m_InputAction {};
	// todo can add other state here later.
};

/**
 * 
 */
UCLASS(Blueprintable)
class PPFGAME_API UPPFPlayerInputConfig : public UDataAsset {
	GENERATED_BODY()
public:
	// UPROPERTY(EditDefaultsOnly, Category = "Input")
	// TArray<FInputActionEntry> m_InputActionsEntries {};
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FInputActionEntry m_MoveInputEntry {};
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FInputActionEntry m_FutureInputEntry {};
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FInputActionEntry m_PastInputEntry {};

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TArray<TObjectPtr<UInputMappingContext>> m_InputMappingContexts {};
};
