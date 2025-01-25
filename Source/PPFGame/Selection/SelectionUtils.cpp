// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectionUtils.h"

#include "SelectableInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PPFGame/Math/MathUtility.h"

TArray<ISelectableInterface*> USelectionUtils::QuerySelectableObjectsInCone(const UObject& WorldContextObject, const FVector2D& Location, const FVector2D& Direction,
                                                                            const float Degrees, const float Range)
{
	TArray<ISelectableInterface*> SelectableObjectsFound;
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;
	TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1));

	TArray<AActor*> FoundActors {};
	FVector SphereCenter = FVector(Location, 0);
	UKismetSystemLibrary::SphereOverlapActors(&WorldContextObject, SphereCenter, Range, TraceObjectTypes, AActor::StaticClass(), {}, FoundActors);

	for (AActor* ActorToTest : FoundActors)
	{
		if (ActorToTest->Implements<USelectableInterface>())
		{
			FVector FromTo = (ActorToTest->GetActorLocation() - SphereCenter);
			
			float Angle = UMathUtility::AngleVectors(FromTo, FVector(Direction, 0));
			if (Angle <= Degrees/2.0f)
			{
				SelectableObjectsFound.Add(Cast<ISelectableInterface>(ActorToTest));
			}
		}
	}
	
	return SelectableObjectsFound;
}
