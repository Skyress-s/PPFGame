// Fill out your copyright notice in the Description page of Project Settings.


#include "MathUtility.h"

float UMathUtility::AngleVectors(const FVector& Vector1, const FVector& Vector2)
{
	// Thanks gpt
	// Normalize the vectors
	FVector NormalizedVector1 = Vector1.GetSafeNormal();
	FVector NormalizedVector2 = Vector2.GetSafeNormal();

	// Calculate the dot product
	float DotProduct = FVector::DotProduct(NormalizedVector1, NormalizedVector2);

	// Calculate the angle in radians
	float AngleInRadians = FMath::Acos(DotProduct);

	// Convert the angle to degrees
	float AngleInDegrees = FMath::RadiansToDegrees(AngleInRadians);

	return AngleInDegrees;
}
