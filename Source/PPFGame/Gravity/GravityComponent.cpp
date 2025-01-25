// Fill out your copyright notice in the Description page of Project Settings.


#include "GravityComponent.h"


// Sets default values for this component's properties
UGravityComponent::UGravityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGravityComponent::BeginPlay()
{
	Super::BeginPlay();
	PrimaryComponentTick.TickGroup = ETickingGroup::TG_PrePhysics;
	// ...
	
}


// Called every frame
void UGravityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Cast<UPrimitiveComponent>( GetOwner()->GetRootComponent())->AddForce(FVector(m_Gravity, 0), NAME_None, true);
	// ...
}

void UGravityComponent::SetGravity(const FVector2D& Gravity)
{
	m_Gravity = Gravity;
}

