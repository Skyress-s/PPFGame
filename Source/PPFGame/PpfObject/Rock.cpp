// Fill out your copyright notice in the Description page of Project Settings.


#include "Rock.h"

#include "FutureNotifier.h"
#include "PresentIndicator.h"
#include "Components/BoxComponent.h"
#include "Logging/StructuredLog.h"
#include "PPFGame/Gravity/GravityComponent.h"
#include "PPFGame/Selection/PpfTimeEnum.h"
DEFINE_LOG_CATEGORY_STATIC(LogRock, Log, All);

// Sets default values
ARock::ARock()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_RootBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootBoxComponent"));
	m_RootBoxComponent->SetSimulatePhysics(true);
	m_RootBoxComponent->SetEnableGravity(false);
	m_RootBoxComponent->SetCollisionObjectType(ECC_GameTraceChannel1);
	
	SetRootComponent(m_RootBoxComponent);

	m_FutureNotifier = CreateDefaultSubobject<UFutureNotifier>(TEXT("FutureNotifier"));

	m_GravityComponent = CreateDefaultSubobject<UGravityComponent>(TEXT("GravityComponent"));

	m_IndicatorStaticMeshComp = CreateDefaultSubobject<UPresentIndicator>(TEXT("PresentIndicator"));
	m_IndicatorStaticMeshComp->SetupAttachment(GetRootComponent());
}

void ARock::BeginPlay()
{
	Super::BeginPlay();
	EnterToPresentTimeMode();
}

bool ARock::TrySelect()
{
	UE_LOGFMT(LogRock, Log, "Rock Was Try Selected");
	return true;
}

ETimeMode ARock::OnSelect(const ETimeMode Time)
{
	UE_LOGFMT(LogRock, Log, "Rock Was Selected");

	switch (m_CurrentTimeMode) {
	case ETimeMode::Future:
		LeaveFutureTimeMode();
		break;
	case ETimeMode::Present:
		LeavePresentTimeMode();
		break;
	case ETimeMode::Past:
		LeavePastTimeMode();
		break;
	}
	
	m_CurrentTimeMode = TimeMode::GetNextState(m_CurrentTimeMode, Time);

	switch (m_CurrentTimeMode) {
	case ETimeMode::Future:
		EnterToFutureTimeMode();
		break;
	case ETimeMode::Present:
		EnterToPresentTimeMode();
		break;
	case ETimeMode::Past:
		EnterToPastTimeMode();
		break;
	}
	
	
	return m_CurrentTimeMode;
}

void ARock::EnterToPastTimeMode()
{
}

void ARock::EnterToPresentTimeMode()
{
	m_RootBoxComponent->SetSimulatePhysics(false);
	m_IndicatorStaticMeshComp->NotifyOfVector(m_VelocityEnLeaveFuture);
	m_IndicatorStaticMeshComp->Enable();
}

void ARock::EnterToFutureTimeMode()
{
	m_RootBoxComponent->SetSimulatePhysics(true);
	m_RootBoxComponent->SetPhysicsLinearVelocity(m_VelocityEnLeaveFuture);
	m_FutureNotifier->m_OnEnterFuture.Broadcast(m_VelocityEnLeaveFuture);
}

void ARock::LeavePastTimeMode()
{
}

void ARock::LeavePresentTimeMode()
{
	m_IndicatorStaticMeshComp->Disable();
}

void ARock::LeaveFutureTimeMode()
{
	m_VelocityEnLeaveFuture = m_RootBoxComponent->GetPhysicsLinearVelocity();
}
