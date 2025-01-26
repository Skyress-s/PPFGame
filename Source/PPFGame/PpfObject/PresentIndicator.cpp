// Fill out your copyright notice in the Description page of Project Settings.


#include "PresentIndicator.h"

void UPresentIndicator::NotifyOfVector(const FVector& Vector)
{
	const FRotator rot = FRotationMatrix::MakeFromXZ(Vector, FVector::UpVector).Rotator();
	m_Vector = Vector;
	SetWorldRotation(rot);
}

void UPresentIndicator::Enable()
{
	SetVisibility(true);
}

void UPresentIndicator::Disable()
{
	SetVisibility(false);
}
