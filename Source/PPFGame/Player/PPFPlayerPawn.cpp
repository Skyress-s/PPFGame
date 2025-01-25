// Fill out your copyright notice in the Description page of Project Settings.


#include "PPFPlayerPawn.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PPFGame/Input/PPFPlayerInputConfig.h"
#include "Logging/StructuredLog.h"

DEFINE_LOG_CATEGORY_STATIC(LogPPFPlayerPawn, Log, All);

// Sets default values
APPFPlayerPawn::APPFPlayerPawn() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APPFPlayerPawn::BeginPlay() {
	Super::BeginPlay();
	//Add Input Mapping Context
	
	check(IsValid(m_InputConfig))
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			for (const TObjectPtr<UInputMappingContext>& IMC : m_InputConfig->m_InputMappingContexts) {
				Subsystem->AddMappingContext(IMC, 0);
			}
		}
	}
}

// Called every frame
void APPFPlayerPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APPFPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		check(IsValid(EnhancedInputComponent));
		for (const FInputActionEntry& InputEntry : m_InputConfig->m_InputActionsEntries) {
			const UInputAction* InputActionToBind = InputEntry.m_InputAction;
			
			EnhancedInputComponent->BindAction(InputActionToBind, ETriggerEvent::Triggered, this, &APPFPlayerPawn::OnMoveInput);
		}
	}
}

void APPFPlayerPawn::OnMoveInput(const FInputActionValue& InputActionValue) {
	FVector2D Input = InputActionValue.Get<FVector2D>();

	UE_LOGFMT(LogPPFPlayerPawn, Warning, "input {Input}", Input);
}

