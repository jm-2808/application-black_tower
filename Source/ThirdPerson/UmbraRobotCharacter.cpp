// Fill out your copyright notice in the Description page of Project Settings.

#include "UmbraRobotCharacter.h"

#include "UmbraPlayerController.h"
#include "UmbraGhostCharacter.h"

#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

//////////////////////////////////////////////////////////////////////////
// AUmbraRobotCharacter

AUmbraRobotCharacter::AUmbraRobotCharacter()
{

}

//////////////////////////////////////////////////////////////////////////
// Input

void AUmbraRobotCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // Unpossess
		EnhancedInputComponent->BindAction(UnpossessAction, ETriggerEvent::Started, this, &AUmbraRobotCharacter::TryUnpossess);
    }
}

//------------------------------------------------------------------------

void AUmbraRobotCharacter::TryUnpossess()
{
    if(AUmbraPlayerController* controller = Cast<AUmbraPlayerController>(GetController()))
    {
        controller->UnpossessRobot(this);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("'%s' - Try Unpossess: Invalid Controller"), *GetNameSafe(this));
    }
}

//------------------------------------------------------------------------

void AUmbraRobotCharacter::OnBeginPossession_Implementation(AUmbraGhostCharacter* ghost)
{
    bIsPossessed = true;
}

//------------------------------------------------------------------------

void AUmbraRobotCharacter::OnEndPossession_Implementation(AUmbraGhostCharacter* ghost)
{
    bIsPossessed = false;
}
