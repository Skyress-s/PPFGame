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

float UMathUtility::AngleVectorsSigned(const FVector& Vector1, const FVector& Vector2, const FVector& UpVector)
{
	// Normalize the vectors
	FVector NormalizedVector1 = Vector1.GetSafeNormal();
	FVector NormalizedVector2 = Vector2.GetSafeNormal();

	// Calculate the dot product
	float DotProduct = FVector::DotProduct(NormalizedVector1, NormalizedVector2);

	// Calculate the angle in radians
	float AngleInRadians = FMath::Acos(DotProduct);

	// Calculate the cross product to determine the sign of the angle
	FVector CrossProduct = FVector::CrossProduct(NormalizedVector1, NormalizedVector2);

	// Determine the sign of the angle
	float Sign = FVector::DotProduct(CrossProduct, UpVector) < 0 ? -1.0f : 1.0f;

	// Convert the angle to degrees and apply the sign
	float AngleInDegrees = FMath::RadiansToDegrees(AngleInRadians) * Sign;

	return AngleInDegrees;
}
