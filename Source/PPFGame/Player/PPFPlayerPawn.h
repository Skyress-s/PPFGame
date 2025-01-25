// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "PPFPlayerPawn.generated.h"

class UGravityComponent;
class UPpfPawnStats;
class USphereComponent;
class UCapsuleComponent;
class UCameraComponent;
class UPPFPlayerInputConfig;

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
	void OnMoveInput(const FInputActionValue& InputActionValue);
	void OnJumpInput(const FInputActionValue& InputActionValue);
	void OnPastInput(const FInputActionValue& InputActionValue);
	void OnFutureInput(const FInputActionValue& InputActionValue);

#pragma endregion
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
#pragma endregion
};
