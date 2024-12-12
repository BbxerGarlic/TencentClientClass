// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/Interface.h"
#include "UDamageableInterface.generated.h"

/**
 * 
 */
UINTERFACE(Blueprintable)
class UDamageableInterface : public UInterface
{
    GENERATED_BODY()
};
//
class IDamageableInterface
{
    GENERATED_BODY()

public:
    // 接口方法，接受伤害
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
    void ReceiveDamage(float DamageAmount, ACharacter* SourceCharacter);
};