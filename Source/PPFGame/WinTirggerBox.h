// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "WinTirggerBox.generated.h"

UCLASS()
class PPFGAME_API AWinTirggerBox : public ATriggerBox
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWinTirggerBox();

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialParameterCollection> m_GlobalMPC {};
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
