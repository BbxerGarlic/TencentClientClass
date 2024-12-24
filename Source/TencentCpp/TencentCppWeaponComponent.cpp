// Copyright Epic Games, Inc. All Rights Reserved.


#include "TencentCppWeaponComponent.h"
#include "TencentCppCharacter.h"
#include "TencentCppProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Animation/AnimInstance.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UTencentCppWeaponComponent::UTencentCppWeaponComponent()
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);

}


//void UTencentCppWeaponComponent::Fire()
//{
//	if (Character == nullptr || Character->GetController() == nullptr)
//	{
//		return;
//	}
//
//	// Try and fire a projectile
//	if (ProjectileClass != nullptr)
//	{
//		UWorld* const World = GetWorld();
//		if (World != nullptr)
//		{
//			APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
//			const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
//			const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
//
//			// Only execute on the server
//			if (GetOwner()->HasAuthority())
//			{
//				ServerFire(SpawnLocation, SpawnRotation);
//			}
//			else
//			{
//				// If client, request the server to fire
//				ServerFire(SpawnLocation, SpawnRotation);
//				UE_LOG(LogTemp, Warning, TEXT("Fire function called!"));
//			}
//		}
//	}
//	
//	// Try and play the sound if specified
//	if (FireSound != nullptr)
//	{
//		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
//	}
//	
//	// Try and play a firing animation if specified
//	if (FireAnimation != nullptr)
//	{
//		// Get the animation object for the arms mesh
//		UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
//		if (AnimInstance != nullptr)
//		{
//			AnimInstance->Montage_Play(FireAnimation, 1.f);
//		}
//	}
//}

void UTencentCppWeaponComponent::FireByPos(const FVector& EndLocation)
{

	if (!CanFire())return;

	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		AController* PlayerController = Cast<AController>(Character->GetController());
		const FRotator SpawnRotation = FRotator::ZeroRotator;
		const FVector StartLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
		

		if (GetOwner()->HasAuthority())
		{
			// 服务器发射射线
			ServerFireRaycast(StartLocation, EndLocation, SpawnRotation);

		}
		else
		{
			// 客户端请求服务器发射射线
			ServerFireRaycast(StartLocation, EndLocation, SpawnRotation);
		}
	}
	//}

	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}

}

void UTencentCppWeaponComponent::Fire()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}
	if (!CanFire())return;
	

	// 发射射线
	//if (ProjectileClass == nullptr)  // 没有 ProjectileClass，就用射线
	//{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
			const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			const FVector StartLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
			const FVector EndLocation = StartLocation + SpawnRotation.Vector() * 10000.0f; // 射线的最大长度

			if (GetOwner()->HasAuthority())
			{
				// 服务器发射射线
				ServerFireRaycast(StartLocation, EndLocation, SpawnRotation);

			}
			else
			{
				// 客户端请求服务器发射射线
				ServerFireRaycast(StartLocation, EndLocation, SpawnRotation);
			}
		}
	//}

	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}
	
}



bool UTencentCppWeaponComponent::CanFire_Implementation()
{
	return false;
}



void UTencentCppWeaponComponent::ServerFireRaycast_Implementation(const FVector& StartLocation, const FVector& EndLocation, const FRotator& FireRotation)
{

	// 获取世界
	UWorld* World = this->GetWorld();  // 使用 this 调用 GetWorld()

	if (World == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("World is null, cannot perform raycast."));
		return;
	}

	// 发射射线进行碰撞检测
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;


	if (this->GetOwner() != nullptr){
		CollisionParams.AddIgnoredActor(this->GetOwner());  // 使用 this 调用 GetOwner()
			if(this->GetOwner()->GetOwner()!=nullptr)CollisionParams.AddIgnoredActor(this->GetOwner()->GetOwner());  // 使用 this 调用 GetOwner()
	}

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, CollisionParams);


	if (bHit)
	{
		// 如果射线碰撞到物体
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			// 执行射击命中反馈
			UE_LOG(LogTemp, Log, TEXT("Hit actor: %s"), *HitActor->GetName());
			if (HitActor && HitActor->Implements<UDamageableInterface>())
			{
				// 通过接口调用伤害处理方法
				IDamageableInterface::Execute_ReceiveDamage(HitActor, 20.f,Character);
				ClientDrawDebugRay(StartLocation, HitResult.ImpactPoint, FColor::Red);
			}
			else {

				ClientDrawDebugRay(StartLocation, HitResult.ImpactPoint, FColor::Yellow);
			}

		}

	}
	else
	{
		ClientDrawDebugRay(StartLocation, EndLocation, FColor::Yellow);
	}
}

void UTencentCppWeaponComponent::ClientDrawDebugRay_Implementation(const FVector& StartLocation, const FVector& EndLocation , const FColor& Color)
{
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, Color, false, 0.3f, 0, 1.0f);
}

bool UTencentCppWeaponComponent::ServerFireRaycast_Validate(const FVector& StartLocation, const FVector& EndLocation, const FRotator& FireRotation)
{
	// 在这里添加验证逻辑，确保客户端请求是有效的
	return true;
}

void UTencentCppWeaponComponent::ServerFire_Implementation(const FVector& SpawnLocation, const FRotator& SpawnRotation)
{
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			ActorSpawnParams.Owner = Character;

			// Spawn the projectile on the server
			ATencentCppProjectile* Bullet = World->SpawnActor<ATencentCppProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

			if (Bullet)
			{
				Bullet->SetInstigator(Character);
			}
			UE_LOG(LogTemp, Warning, TEXT("Bullet created!"));

		}
	}
}


bool UTencentCppWeaponComponent::AttachWeapon(ATencentCppCharacter* TargetCharacter)
{
	Character = TargetCharacter;

	// Check that the character is valid, and has no weapon component yet
	if (Character == nullptr || Character->GetInstanceComponents().FindItemByClass<UTencentCppWeaponComponent>())
	{
		return false;
	}

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);

	if (ATencentCppCharacter* Player = Cast<ATencentCppCharacter>(Character)) {
		AttachToComponent(Player->GetMeshMan(), AttachmentRules, FName(TEXT("GripPoint")));
	}



	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Fire
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UTencentCppWeaponComponent::Fire);
		}
	}

	return true;
}

void UTencentCppWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// ensure we have a character owner
	if (Character != nullptr)
	{
		// remove the input mapping context from the Player Controller
		if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->RemoveMappingContext(FireMappingContext);
			}
		}
	}

	// maintain the EndPlay call chain
	Super::EndPlay(EndPlayReason);
}