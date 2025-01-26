// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "PPFGame/PpfObject/FutureNotifier.h"
#include "PPFGame/Selection/PpfTimeEnum.h"
#include "PPFPlayerPawn.generated.h"

class UBoxComponent;

enum class EWallDetectionSide : uint8
{
	None = 1 << 0,
	Left = 1 << 1,
	Right = 1 << 2,
};

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
	uint8 IsCharacterWalled();
	bool IsCharacterGrounded();

private:
#pragma region PrivateMethods
	// Input
	void OnMoveInput(const FInputActionValue& InputActionValue);
	void OnJumpInput(const FInputActionValue& InputActionValue);
	void OnResetInput(const FInputActionValue& InputActionValue);
	void OnPastInput(const FInputActionValue& InputActionValue);
	void OnFutureInput(const FInputActionValue& InputActionValue);

	// Movement
	void HandlePhysMat();
	void HandleMovement();
	
	void UsePpfAbility(ETimeMode TimeModeToApply);

	void OnAdjecentObjectEnterFuture(const FVector& Vector);
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void UpdateMpcHaha();
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

	UPROPERTY(EditDefaultsOnly, Category = "Body")
	TObjectPtr<UBoxComponent> m_LeftBoxQueryBox {};
	
	UPROPERTY(EditDefaultsOnly, Category = "Body")
	TObjectPtr<UBoxComponent> m_RightBoxQueryBox {};
	
	UPROPERTY(EditDefaultsOnly, Category = "Body")
	TObjectPtr<UBoxComponent> m_EnterFutureDetectionRange {};

	// Defines the range of the character
	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TObjectPtr<USphereComponent> m_AbilitySphere {};

	UPROPERTY(EditDefaultsOnly, Category = "Gravity")
	TObjectPtr<UGravityComponent> m_GravityComponent {};

	UPROPERTY(EditDefaultsOnly, Category = "Art", meta = (AllowPrivateAccess = "true"))
	UMaterialParameterCollection* m_MaterialParameterCollection {};

	// todo This is very memory safe. Because i have hope.
	TMap<AActor*, FDelegateHandle> m_FutureDetectionHandles {};

	struct
	{
		float m_MoveInputX {};
	};
#pragma endregion
};

