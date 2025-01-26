// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PPFGame/Selection/SelectableInterface.h"
#include "Rock.generated.h"

class UPresentIndicator;
class UFutureNotifier;
class UGravityComponent;
class UBoxComponent;

enum class ETimeMode : uint8;

UCLASS()
class PPFGAME_API ARock : public AActor, public ISelectableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARock();
	virtual void BeginPlay() override;
	// ISelectableInterface START
public:
	// Checks if the object can be selected.
	virtual bool TrySelect();

	virtual ETimeMode OnSelect(const ETimeMode Time);
	// ISelectableInterface END
private:

	void EnterToPastTimeMode();
	void EnterToPresentTimeMode();
	void EnterToFutureTimeMode();

	void LeavePastTimeMode();
	void LeavePresentTimeMode();
	void LeaveFutureTimeMode();
public:
	UPROPERTY(EditAnywhere, Category = "Root")
	TObjectPtr<UBoxComponent> m_RootBoxComponent {};
	
	UPROPERTY(EditAnywhere, Category = "Gravity")
	TObjectPtr<UGravityComponent> m_GravityComponent {};
	
	UPROPERTY(EditAnywhere, Category = "Indication")
	TObjectPtr<UPresentIndicator> m_IndicatorStaticMeshComp {};
	
	UPROPERTY(EditAnywhere, Category = "FutureNotifier")
	TObjectPtr<UFutureNotifier> m_FutureNotifier {};
private:
	ETimeMode m_CurrentTimeMode = ETimeMode::Present;
	UPROPERTY(EditAnywhere, Category = "Velocity", meta = (AllowPrivateAccess = "true"))
	FVector m_VelocityEnLeaveFuture = FVector::ZeroVector;
};
