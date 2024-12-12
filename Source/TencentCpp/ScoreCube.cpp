// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreCube.h"


// Sets default values
AScoreCube::AScoreCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AScoreCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AScoreCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AScoreCube::ReceiveDamage_Implementation(float DamageAmount, ACharacter* SourceCharacter)
{
}

