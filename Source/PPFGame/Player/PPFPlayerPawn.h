﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "PPFGame/Selection/PpfTimeEnum.h"
#include "PPFPlayerPawn.generated.h"

class UGravityComponent;
class UPpfPawnStats;
class USphereComponent;
class UCapsuleComponent;
class UCameraComponent;
class UPPFPlayerInputConfig;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUseAbility, const FVector2D&, Direction, ETimeMode, TimeMode);

UCLASS()
class PPFGAME_API APPFPlayerPawn : public APawn {
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APPFPlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
public:
	bool IsCharacterGrounded() const;

private:
#pragma region PrivateMethods
	// Input
	void OnMoveInput(const FInputActionValue& InputActionValue);
	void OnJumpInput(const FInputActionValue& InputActionValue);
	void TraceTest(ETimeMode TimeModeToApply);
	void OnPastInput(const FInputActionValue& InputActionValue);
	void OnFutureInput(const FInputActionValue& InputActionValue);

	// Movement
	void HandlePhysMat();
	void HandleMovement();
	
#pragma endregion
public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnUseAbility m_OnUseAbility;
private:
#pragma region PrivateFields
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UPPFPlayerInputConfig> m_InputConfig {};
	
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	TObjectPtr<UPpfPawnStats> m_PlayerStats {};
	
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> m_CameraComponent {};

	// Root comp
	UPROPERTY(EditDefaultsOnly, Category = "Body")
	TObjectPtr<UCapsuleComponent> m_RootCapsuleComponent {};

	// Defines the range of the character
	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TObjectPtr<USphereComponent> m_AbilitySphere {};

	UPROPERTY(EditDefaultsOnly, Category = "Gravity")
	TObjectPtr<UGravityComponent> m_GravityComponent {};

	struct
	{
		float m_MoveInputX {};
	};
#pragma endregion
};
