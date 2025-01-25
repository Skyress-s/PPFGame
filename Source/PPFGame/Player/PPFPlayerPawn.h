// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "PPFPlayerPawn.generated.h"

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


private:
#pragma region PrivateMethods
	void OnMoveInput(const FInputActionValue& InputActionValue);

#pragma endregion
private:
#pragma region PrivateFields
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UPPFPlayerInputConfig> m_InputConfig {};
#pragma endregion
};
