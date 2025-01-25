// Fill out your copyright notice in the Description page of Project Settings.


#include "PPFPlayerPawn.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "KismetTraceUtils.h"
#include "PPFPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Config/PpfPawnStats.h"
#include "PPFGame/Input/PPFPlayerInputConfig.h"
#include "Logging/StructuredLog.h"
#include "PPFGame/Gravity/GravityComponent.h"
#include "PPFGame/Selection/SelectableInterface.h"
#include "PPFGame/Selection/SelectionUtils.h"
#include "PPFGame/Selection/PpfTimeEnum.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "PPFGame/Debug/DebuggingDefines.h"


DEFINE_LOG_CATEGORY_STATIC(LogPPFPlayerPawn, Log, All);

// Sets default values
APPFPlayerPawn::APPFPlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Components
	m_RootCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	m_RootCapsuleComponent->GetBodyInstance()->SetDOFLock(EDOFMode::Type::SixDOF);
	m_RootCapsuleComponent->GetBodyInstance()->bLockRotation = true;
	m_RootCapsuleComponent->GetBodyInstance()->bLockZTranslation = true;

	m_RootCapsuleComponent->SetSimulatePhysics(true);
	m_RootCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	SetRootComponent(m_RootCapsuleComponent);
	m_CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	m_CameraComponent->SetupAttachment(GetRootComponent());

	m_AbilitySphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	m_AbilitySphere->SetupAttachment(GetRootComponent());
	m_AbilitySphere->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

	m_GravityComponent = CreateDefaultSubobject<UGravityComponent>(TEXT("GravityComponent"));
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
	HandlePhysMat();
	HandleMovement();
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
		EnhancedInputComponent->BindAction(m_InputConfig->m_MoveInputEntry.m_InputAction, ETriggerEvent::Completed, this, &APPFPlayerPawn::OnMoveInput);
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

bool APPFPlayerPawn::IsCharacterGrounded()
{
	FHitResult HitResult;
	const float HalfHeight = m_RootCapsuleComponent->GetScaledCapsuleHalfHeight();
	const FVector Down = m_RootCapsuleComponent->GetUpVector() * -1.0f;
	const FVector BottomOfCapsule = m_RootCapsuleComponent->GetComponentLocation() + (Down * HalfHeight);
	const FVector Start = BottomOfCapsule - Down * m_RootCapsuleComponent->GetScaledCapsuleHalfHeight() * 0.1f;
	const FVector End = BottomOfCapsule + Down * m_PlayerStats->m_GroundCheckDistance;
	FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams::DefaultQueryParam;
	CollisionQueryParams.AddIgnoredActor(this);
	
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;
	TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1));
	TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	TArray<AActor*> ActorsToIgnore {this};
	UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), BottomOfCapsule, Start, m_RootCapsuleComponent->GetScaledCapsuleRadius() * 0.8f, TraceObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true);
	
	// GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_WorldStatic, CollisionQueryParams);
	// DrawDebugLineTraceSingle(GetWorld(), Start, End, EDrawDebugTrace::ForDuration, HitResult.bBlockingHit, HitResult, FLinearColor::Red, FLinearColor::Green, 1.0f);
	
	return HitResult.bBlockingHit;
}
#endif

void APPFPlayerPawn::OnMoveInput(const FInputActionValue& InputActionValue)
{
	m_MoveInputX = InputActionValue.Get<FVector2D>().X;


	UE_LOGFMT(LogPPFPlayerPawn, Warning, "input {Input}", m_MoveInputX);
}

void APPFPlayerPawn::OnJumpInput(const FInputActionValue& InputActionValue)
{
	UE_LOGFMT(LogPPFPlayerPawn, Warning, "Jump input!");
	check(IsValid(m_PlayerStats))
	if (IsCharacterGrounded())
	{
		m_RootCapsuleComponent->AddImpulse(FVector::YAxisVector * m_PlayerStats->m_JumpSpeed, NAME_None, true);
	}
}

void APPFPlayerPawn::TraceTest(const ETimeMode TimeModeToApply)
{
	TObjectPtr<APPFPlayerController> PpfPlayerController = Cast<APPFPlayerController>(GetController());
	FVector Direction, Location;
	PpfPlayerController->DeprojectMousePositionToWorld(Location, Direction);

	FVector FoundLocation = FMath::RayPlaneIntersection(m_CameraComponent->GetComponentLocation(), Direction, FPlane(FVector::ZeroVector, FVector::UpVector));

	const FVector ToMouse = FoundLocation - GetActorLocation();

#ifdef PPF_DEBUG_TRACES
	DrawDebugBox(GetWorld(), FoundLocation, FVector(10, 10, 10), FColor::Red, true, 4.f, 0, 10.0f);
#endif

	TArray<ISelectableInterface*> SelectableInterfaces = USelectionUtils::QuerySelectableObjectsInCone(*this, FVector2D(GetActorLocation()), FVector2D(ToMouse), 30.0f, 500.0f);
	for (ISelectableInterface* const SelectableInterface : SelectableInterfaces)
	{
		const AActor* const FoundActor = Cast<AActor>(SelectableInterface);

		const bool ValidSelect = SelectableInterface->TrySelect();
		if (ValidSelect)
		{
			const ETimeMode SetTimeMode = SelectableInterface->OnSelect(TimeModeToApply);
			m_OnUseAbility.Broadcast(FVector2D(Direction), SetTimeMode);
		}

#if PPF_DEBUG_TRACES
		DrawDebugBox(GetWorld(), FoundActor->GetActorLocation(), FVector(1000, 10, 10), FColor::Red, false, 1.f, 0, 10.0f);
#endif
	}
}

void APPFPlayerPawn::OnPastInput(const FInputActionValue& InputActionValue)
{
	UE_LOGFMT(LogPPFPlayerPawn, Warning, "Past input!");

	TraceTest(ETimeMode::Past);
}

void APPFPlayerPawn::OnFutureInput(const FInputActionValue& InputActionValue)
{
	UE_LOGFMT(LogPPFPlayerPawn, Warning, "Future input!");
	TraceTest(ETimeMode::Future);
}

void APPFPlayerPawn::HandlePhysMat()
{
	if (IsCharacterGrounded() && FMath::IsNearlyZero(m_MoveInputX))
	{
		m_RootCapsuleComponent->SetPhysMaterialOverride(m_PlayerStats->m_StickPhysMat);
		return;
	}
	
	if (IsCharacterGrounded())
	{
		m_RootCapsuleComponent->SetPhysMaterialOverride(m_PlayerStats->m_GlidePhysMat);
	}
	else
	{
		m_RootCapsuleComponent->SetPhysMaterialOverride(m_PlayerStats->m_StickPhysMat);
	}
}

void APPFPlayerPawn::HandleMovement()
{
	// Lol no data driven design in this house :)
	if (!IsCharacterGrounded() && FMath::IsNearlyZero(m_MoveInputX))
	{
		return;
	}

	const float TargetSpeed = -m_MoveInputX * m_PlayerStats->m_MovementGroundedMaxSpeed;
	const float CurrentSpeed = m_RootCapsuleComponent->GetComponentVelocity().X;

	const float Diff = TargetSpeed - CurrentSpeed;

	const float Acceleration = Diff * m_PlayerStats->m_MovementAcceleration;

	// UE_LOGFMT(LogPPFPlayerPawn, Warning, "Acceleration {Acceleration}", Acceleration);

	m_RootCapsuleComponent->AddForce(FVector(Acceleration, 0, 0), NAME_None, true);
}
