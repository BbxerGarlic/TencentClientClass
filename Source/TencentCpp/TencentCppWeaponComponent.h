// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "TencentCppWeaponComponent.generated.h"

class ATencentCppCharacter;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TENCENTCPP_API UTencentCppWeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class ATencentCppProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector MuzzleOffset;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	/** Sets default values for this component's properties */
	UTencentCppWeaponComponent();

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	bool AttachWeapon(ATencentCppCharacter* TargetCharacter);

	/** Make the weapon Fire a Projectile */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void FireByPos(const FVector& EndLocation);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
	bool CanFire();

	virtual bool CanFire_Implementation();

	UFUNCTION(Server, Reliable)
	void ServerFire(const FVector& SpawnLocation, const FRotator& SpawnRotation);
	void ServerFire_Implementation(const FVector& SpawnLocation, const FRotator& SpawnRotation);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerFireRaycast(const FVector& StartLocation, const FVector& EndLocation, const FRotator& FireRotation);


	void ServerFireRaycast_Implementation(const FVector& StartLocation, const FVector& EndLocation, const FRotator& FireRotation);

	UFUNCTION(Client, Reliable)
	void ClientDrawDebugRay(const FVector& StartLocation, const FVector& EndLocation, const FColor& Color);

	void ClientDrawDebugRay_Implementation(const FVector& StartLocation, const FVector& EndLocation, const FColor& Color);


protected:
	/** Ends gameplay for this component. */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/** The Character holding this weapon*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	ACharacter* Character;

};
