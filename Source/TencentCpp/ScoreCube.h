// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UDamageableInterface.h"
#include "ScoreCube.generated.h"

UCLASS()
class TENCENTCPP_API AScoreCube : public AActor, public IDamageableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScoreCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ReceiveDamage_Implementation(float DamageAmount, ACharacter* SourceCharacter) override;
	
	
};
