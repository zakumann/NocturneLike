// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "CharacterController.generated.h"

/**
 * 
 */
UCLASS()
class NOCTURNELIKE_API ACharacterController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ACharacterController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	// Input actions
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* SprintAction;

	// Walk Setting
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float WalkSpeed = 300.f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float JogSpeed = 600.f;

	// Walking
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bIsSprint = false;

	// === Camera Pitch Limit ===
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float MinPitch = -70.f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float MaxPitch = 70.f;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartSprint();
	void StopSprint();
};
