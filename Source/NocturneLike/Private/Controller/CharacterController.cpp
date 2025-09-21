// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/CharacterController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Character/PlayerCharacter.h"
#include "InputMappingContext.h"
#include "InputAction.h"

void ACharacterController::BeginPlay()
{
    Super::BeginPlay();

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
        ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        if (InputMappingContext)
        {
            Subsystem->AddMappingContext(InputMappingContext, 0);
        }
    }
}

void ACharacterController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
    {
        if (MoveAction)
        {
            EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACharacterController::HandleMove);
        }
        if (LookAction)
        {
            EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACharacterController::HandleLook);
        }
        if (SprintAction)
        {
            EIC->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ACharacterController::HandleStartSprint);
            EIC->BindAction(SprintAction, ETriggerEvent::Completed, this, &ACharacterController::HandleStopSprint);
        }
    }
}

void ACharacterController::HandleMove(const FInputActionValue& Value)
{
    if (APlayerCharacter* PC = Cast<APlayerCharacter>(GetPawn()))
    {
        PC->Move(Value);
    }
}

void ACharacterController::HandleLook(const FInputActionValue& Value)
{
    if (APlayerCharacter* PC = Cast<APlayerCharacter>(GetPawn()))
    {
        PC->Look(Value);
    }
}

void ACharacterController::HandleStartSprint()
{
    if (APlayerCharacter* PC = Cast<APlayerCharacter>(GetPawn()))
    {
        PC->StartSprint();
    }
}

void ACharacterController::HandleStopSprint()
{
    if (APlayerCharacter* PC = Cast<APlayerCharacter>(GetPawn()))
    {
        PC->StopSprint();
    }
}
