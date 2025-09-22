// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/CharacterController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ACharacterController::ACharacterController()
{
    bShowMouseCursor = false;
    DefaultMouseCursor = EMouseCursor::Default;
}

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
            EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACharacterController::Move);
        }
        if (LookAction)
        {
            EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACharacterController::Look);
        }
        if (SprintAction)
        {
            EIC->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ACharacterController::StartSprint);
            EIC->BindAction(SprintAction, ETriggerEvent::Completed, this, &ACharacterController::StopSprint);
        }
    }
}

void ACharacterController::Move(const FInputActionValue& Value)
{
    if (APawn* ControlledPawn = GetPawn())
    {
        const FVector2D MovementVector = Value.Get<FVector2D>();

        const FRotator Rotation = GetControlRotation();
        const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
    }
    
}

void ACharacterController::Look(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    // Add yaw normally
    AddYawInput(LookAxisVector.X);

    // Clamp pitch manually
    FRotator ControlRot = GetControlRotation();
    float NewPitch = ControlRot.Pitch + LookAxisVector.Y;

    NewPitch = FMath::ClampAngle(NewPitch, MinPitch, MaxPitch);

    SetControlRotation(FRotator(NewPitch, ControlRot.Yaw, ControlRot.Roll));
}


void ACharacterController::StartSprint()
{
    if (ACharacter* PC = Cast<ACharacter>(GetPawn()))
    {
        if (UCharacterMovementComponent* MoveComp = PC->GetCharacterMovement())
        {
            bIsSprint = true;
            MoveComp->MaxWalkSpeed = JogSpeed;
        }
    }
}

void ACharacterController::StopSprint()
{
    if (ACharacter* PC = Cast<ACharacter>(GetPawn()))
    {
        if (UCharacterMovementComponent* MoveComp = PC->GetCharacterMovement())
        {
            bIsSprint = false;
            MoveComp->MaxWalkSpeed = WalkSpeed;
        }
    }
}
