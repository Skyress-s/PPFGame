// Fill out your copyright notice in the Description page of Project Settings.


#include "WinTirggerBox.h"

#include "Logging/StructuredLog.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "Player/PPFPlayerPawn.h"


// Sets default values
AWinTirggerBox::AWinTirggerBox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWinTirggerBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWinTirggerBox::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (!OtherActor->IsA<APPFPlayerPawn>())
	{
		return;
	}

	UE_LOGFMT(LogTemp, Error, "Player Overlap Win Trigger Box");
	
	FVector2D ScreenPosition;
	GetWorld()->GetFirstPlayerController()->ProjectWorldLocationToScreen(OtherActor->GetActorLocation(), ScreenPosition);
	
	GetWorld()->GetParameterCollectionInstance(m_GlobalMPC)->SetVectorParameterValue("PlayerScreenPosition", FVector(ScreenPosition, 0));
}

// Called every frame
void AWinTirggerBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

