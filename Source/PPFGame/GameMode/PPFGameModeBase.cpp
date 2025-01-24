// Fill out your copyright notice in the Description page of Project Settings.


#include "PPFGameModeBase.h"


// Sets default values
APPFGameModeBase::APPFGameModeBase() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APPFGameModeBase::BeginPlay() {
	Super::BeginPlay();
	
}

// Called every frame
void APPFGameModeBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

