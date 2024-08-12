// Fill out your copyright notice in the Description page of Project Settings.


#include "UmbraGhostCharacter.h"

#include "UmbraPlayerController.h"
#include "UmbraRobotCharacter.h"

#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"

#include "Kismet/KismetSystemLibrary.h"

//////////////////////////////////////////////////////////////////////////
// AUmbraGhostCharacter

AUmbraGhostCharacter::AUmbraGhostCharacter()
{
    
}

//////////////////////////////////////////////////////////////////////////
// AActor

void AUmbraGhostCharacter::BeginPlay()
{
	Super::BeginPlay();

    if (AUmbraPlayerController* controller = Cast<AUmbraPlayerController>(GetController()))
    {
        controller->RegisterGhost(this);
    }
}

//------------------------------------------------------------------------

void AUmbraGhostCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(bIsTeleporting)
    {
        UpdateTeleport(DeltaTime);
    }
}

//------------------------------------------------------------------------

void AUmbraGhostCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    if(!bIsPossessing)
    {
        if(AUmbraRobotCharacter* robot = Cast<AUmbraRobotCharacter>(OtherActor))
        {
            robot->BeginHighlight(PossessPrompt);
        }
    }
}

//------------------------------------------------------------------------

void AUmbraGhostCharacter::NotifyActorEndOverlap(AActor* OtherActor)
{
    Super::NotifyActorEndOverlap(OtherActor);

    if(!bIsPossessing)
    {
        if(AUmbraRobotCharacter* robot = Cast<AUmbraRobotCharacter>(OtherActor))
        {
            robot->EndHighlight();
        }
    }
}

//////////////////////////////////////////////////////////////////////////
// APawn

void AUmbraGhostCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // Possess
		EnhancedInputComponent->BindAction(PossessAction, ETriggerEvent::Started, this, &AUmbraGhostCharacter::TryPossess);

        // Teleport
		EnhancedInputComponent->BindAction(TeleportAction, ETriggerEvent::Started, this, &AUmbraGhostCharacter::BeginTeleport);
        EnhancedInputComponent->BindAction(TeleportAction, ETriggerEvent::Completed, this, &AUmbraGhostCharacter::EndTeleport);
    }
}

//////////////////////////////////////////////////////////////////////////
// Possession

void AUmbraGhostCharacter::TryPossess()
{
    TArray<AActor*> Result;
    GetOverlappingActors(Result, AUmbraRobotCharacter::StaticClass());
    if(Result.Num() > 0)
    {
        AUmbraRobotCharacter* robot = Cast<AUmbraRobotCharacter>(Result[0]);
        if(AUmbraPlayerController* controller = Cast<AUmbraPlayerController>(GetController()))
        {
            controller->PossessRobot(robot);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("'%s' - Try Possess: Invalid Controller"), *GetNameSafe(this));
        }
    }
}

//------------------------------------------------------------------------

void AUmbraGhostCharacter::OnBeginPossession_Implementation(AUmbraRobotCharacter* robot)
{
    bIsPossessing = true;
    robot->EndHighlight();

    GetCharacterMovement()->Velocity = FVector(0.0f, 0.0f, 0.0f);
}

//------------------------------------------------------------------------

void AUmbraGhostCharacter::OnEndPossession_Implementation(AUmbraRobotCharacter* robot)
{
    bIsPossessing = false;
    robot->BeginHighlight(PossessPrompt);
}

//////////////////////////////////////////////////////////////////////////
// Teleport

void AUmbraGhostCharacter::BeginTeleport()
{
    bIsTeleporting = true;
    TeleportRange = 0.0f;

    if(MarkerClass != nullptr)
    {
        TeleportMarker = GetWorld()->SpawnActor(MarkerClass);
        TeleportMarker->SetActorLocation(GetActorLocation());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("'%s' - Begin Teleport: Invalid Marker Class"), *GetNameSafe(this));
    }
}

//------------------------------------------------------------------------

void AUmbraGhostCharacter::EndTeleport()
{
    bIsTeleporting = false;

    if(TeleportMarker != nullptr)
    {
        TeleportMarker->Destroy();
        TeleportMarker = nullptr;
    }

    SetActorLocation(TeleportLocation);
    TeleportLocation = FVector::ZeroVector;

    if(TeleportTarget != nullptr)
    {
        TeleportTarget->EndHighlight();
        TeleportTarget = nullptr;

        TryPossess();
    }
}
    
//------------------------------------------------------------------------

void AUmbraGhostCharacter::UpdateTeleport(float deltaTime)
{
    // Increase teleport range while held
    if(TeleportRange < MaximumTeleportRange)
    {
        TeleportRange += (TeleportRangeRate * deltaTime);
        if(TeleportRange > MaximumTeleportRange)
        {
            TeleportRange = MaximumTeleportRange;
        }
    }

    // Line trace to look for a target
    FVector endpoint = GetActorLocation() + (GetFollowCamera()->GetForwardVector() * TeleportRange);
    FHitResult hit;
    if(GetWorld()->LineTraceSingleByChannel(hit, GetActorLocation(), endpoint, ECC_Visibility))
    {
        // Target found, set location to target position and update target if appropriate
        if(AUmbraRobotCharacter* robot = Cast<AUmbraRobotCharacter>(hit.GetActor()))
        {
            if(TeleportTarget != robot)
            {
                if((TeleportMarker != nullptr) && (TeleportTarget == nullptr))
                {
                    TeleportMarker->SetActorHiddenInGame(true);
                }

                if(TeleportTarget != nullptr)
                {
                    TeleportTarget->EndHighlight();
                }

                TeleportTarget = robot;
                TeleportTarget->BeginHighlight(TeleportPrompt);

                TeleportLocation = robot->GetActorLocation();
            }
        }
    }
    else
    {
        // Target not found, set location to endpoint and clear target
        TeleportLocation = endpoint;

        if((TeleportMarker != nullptr) && (TeleportTarget != nullptr))
        {
            TeleportMarker->SetActorHiddenInGame(false);
        }

        if(TeleportTarget != nullptr)
        {
            TeleportTarget->EndHighlight();
            TeleportTarget = nullptr;
        }
    }

    // Update marker position
    if(TeleportMarker != nullptr)
    {
        TeleportMarker->SetActorLocation(TeleportLocation);
    }
}
