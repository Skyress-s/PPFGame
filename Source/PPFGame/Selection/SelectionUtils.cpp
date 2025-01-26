// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectionUtils.h"

#include "PPFGame/Debug/DebuggingDefines.h"
#include "SelectableInterface.h"

TArray<ISelectableInterface*> USelectionUtils::QuerySelectableObjectsInCone(const UObject& WorldContextObject, const FVector2D& Location, const FVector2D& Direction,
                                                                            const float Degrees, const float Range)
{
	TArray<ISelectableInterface*> SelectableObjectsFound;

	const uint8 NumTraces {10};
	
	FVector test = FVector(Direction, 0);
	const FVector Bottom = test.RotateAngleAxis(-Degrees/2.0f, FVector::UpVector);
	const float AngleBetweenTraces = Degrees / (NumTraces-1);

	TArray<AActor*> FoundActors {};
	for (int i = 0; i < NumTraces; ++i)
	{
		const FVector NewDirection = Bottom.RotateAngleAxis(i * (AngleBetweenTraces), FVector::UpVector);
		const FVector2D NewDirection2D = FVector2D(NewDirection);
		FHitResult ShitResult {};
		FCollisionObjectQueryParams Params {};
		Params.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel1);
		WorldContextObject.GetWorld()->LineTraceSingleByObjectType(ShitResult, FVector(Location, 0), FVector(Location + NewDirection2D * Range, 0), Params);
		if (IsValid(ShitResult.GetActor()) && !FoundActors.Contains(ShitResult.GetActor()))
		{
			FoundActors.Add(ShitResult.GetActor());
		}

#ifdef PPF_DEBUG_TRACES
		DrawDebugLine(WorldContextObject.GetWorld(), FVector(Location, 0), FVector(Location + NewDirection2D * Range, 0), FColor::Red, false, 0.5f, 0, 10);
#endif
		
	}
	
	// const FQuat Rotation = FRotationMatrix::MakeFromXY(X, Y).ToQuat();
	
	// TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;
	// TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1));
	//
	FVector SphereCenter = FVector(Location, 0);
	// UKismetSystemLibrary::SphereOverlapActors(&WorldContextObject, SphereCenter, Range, TraceObjectTypes, AActor::StaticClass(), {}, FoundActors);
	
	for (AActor* ActorToTest : FoundActors)
	{
		if (ActorToTest->Implements<USelectableInterface>())
		{
			// FVector2D FromTo = FVector2D(ActorToTest->GetActorLocation() - SphereCenter);
			
			// float Angle = UMathUtility::AngleVectors(FVector(FromTo, 0), FVector(Direction, 0));
			// if (Angle <= Degrees/2.0f)
			// {
				SelectableObjectsFound.Add(Cast<ISelectableInterface>(ActorToTest));
			// }
		}
	}
	
	return SelectableObjectsFound;
}
