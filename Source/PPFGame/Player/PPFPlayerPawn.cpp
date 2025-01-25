// Fill out your copyright notice in the Description page of Project Settings.


#include "PPFPlayerPawn.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PPFPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Config/PpfPawnStats.h"
#include "PPFGame/Input/PPFPlayerInputConfig.h"
#include "Logging/StructuredLog.h"
#include "PPFGame/Selection/SelectableInterface.h"
#include "PPFGame/Selection/SelectionUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogPPFPlayerPawn, Log, All);

// Sets default values
APPFPlayerPawn::APPFPlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_RootCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	m_RootCapsuleComponent->SetConstraintMode(EDOFMode::Type::SixDOF);
	m_RootCapsuleComponent->BodyInstance.bLockRotation = true;
	m_RootCapsuleComponent->BodyInstance.bLockZRotation = true;


	m_RootCapsuleComponent->SetSimulatePhysics(true);
	m_RootCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	SetRootComponent(m_RootCapsuleComponent);
	m_CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	m_CameraComponent->SetupAttachment(GetRootComponent());

	m_AbilitySphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	m_AbilitySphere->SetupAttachment(GetRootComponent());
	m_AbilitySphere->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

// Called when the game starts or when spawned
void APPFPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	check(IsValid(m_PlayerStats))
	// Unlock Mouse Cursor
	TObjectPtr<APPFPlayerController> PpfPlayerController = Cast<APPFPlayerController>(GetController());
	check(IsValid(PpfPlayerController))
	PpfPlayerController->bShowMouseCursor = true;

	//Add Input Mapping Context
	check(IsValid(m_InputConfig))
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			for (const TObjectPtr<UInputMappingContext>& IMC : m_InputConfig->m_InputMappingContexts)
			{
				Subsystem->AddMappingContext(IMC, 0);
			}
		}
	}
}

// Called every frame
void APPFPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APPFPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		check(IsValid(EnhancedInputComponent))
		check(IsValid(m_InputConfig))

		EnhancedInputComponent->BindAction(m_InputConfig->m_MoveInputEntry.m_InputAction, ETriggerEvent::Triggered, this, &APPFPlayerPawn::OnMoveInput);
		EnhancedInputComponent->BindAction(m_InputConfig->m_JumpInputEntry.m_InputAction, ETriggerEvent::Completed, this, &APPFPlayerPawn::OnJumpInput);
		EnhancedInputComponent->BindAction(m_InputConfig->m_FutureInputEntry.m_InputAction, ETriggerEvent::Completed, this, &APPFPlayerPawn::OnFutureInput);
		EnhancedInputComponent->BindAction(m_InputConfig->m_PastInputEntry.m_InputAction, ETriggerEvent::Completed, this, &APPFPlayerPawn::OnPastInput);
	}
}

#if WITH_EDITOR
void APPFPlayerPawn::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	m_AbilitySphere->SetRelativeScale3D(FVector::OneVector);
}
#endif

void APPFPlayerPawn::OnMoveInput(const FInputActionValue& InputActionValue)
{
	FVector2D Input = InputActionValue.Get<FVector2D>();

	m_RootCapsuleComponent->AddForce(FVector(-Input.X, 0, 0) * 1000, NAME_None, true);

	UE_LOGFMT(LogPPFPlayerPawn, Warning, "input {Input}", Input.ToString());
}

void APPFPlayerPawn::OnJumpInput(const FInputActionValue& InputActionValue)
{
	UE_LOGFMT(LogPPFPlayerPawn, Warning, "Jump input!");
	check(IsValid(m_PlayerStats))
	m_RootCapsuleComponent->AddImpulse(FVector::YAxisVector * m_PlayerStats->m_JumpSpeed, NAME_None, true);
}

void APPFPlayerPawn::OnPastInput(const FInputActionValue& InputActionValue)
{
	UE_LOGFMT(LogPPFPlayerPawn, Warning, "Past input!");

	TObjectPtr<APPFPlayerController> PpfPlayerController = Cast<APPFPlayerController>(GetController());
	FVector Direction, Location;
	PpfPlayerController->DeprojectMousePositionToWorld(Location, Direction);

	FVector FoundLocation = FMath::RayPlaneIntersection(m_CameraComponent->GetComponentLocation(), Direction, FPlane(FVector::ZeroVector, FVector::UpVector));

	const FVector ToMouse = FoundLocation - GetActorLocation();
	// DrawDebugLine(GetWorld(), FoundLocation, FoundLocation + FVector(0, 0, 1000), FColor::Red, true, 4.f, 0, 10.0f);
	DrawDebugBox(GetWorld(), FoundLocation, FVector(10, 10, 10), FColor::Red, true, 4.f, 0, 10.0f);

	TArray<ISelectableInterface*> SelectableInterfaces = USelectionUtils::QuerySelectableObjectsInCone(*this, FVector2D(GetActorLocation()), FVector2D(ToMouse), 30.0f, 500.0f);
	for (ISelectableInterface* const SelectableInterface : SelectableInterfaces)
	{
		const AActor* const FoundActor = Cast<AActor>(SelectableInterface);

		const bool ValidSelect = SelectableInterface->TrySelect();
		if (ValidSelect)
		{
			SelectableInterface->OnSelect(EPpfTime::Past);
		}
		
		DrawDebugBox(GetWorld(), FoundActor->GetActorLocation(), FVector(1000, 10, 10), FColor::Red, false, 1.f, 0, 10.0f);
	}
	
}

void APPFPlayerPawn::OnFutureInput(const FInputActionValue& InputActionValue)
{
	UE_LOGFMT(LogPPFPlayerPawn, Warning, "Future input!");
}
