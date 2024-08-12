// Fill out your copyright notice in the Description page of Project Settings.

#include "UmbraPlayerController.h"

#include "UmbraGhostCharacter.h"
#include "UmbraRobotCharacter.h"

//////////////////////////////////////////////////////////////////////////
// Possession

void AUmbraPlayerController::PossessRobot(AUmbraRobotCharacter* robot)
{
    if(robot == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("'%s' - Possess Robot: Invalid Robot"), *GetNameSafe(this));
        return;
    }

    if(GhostCharacter == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("'%s' - Possess Robot: Invalid Ghost"), *GetNameSafe(this));
        return;
    }

    FRotator control = GetControlRotation();
    Possess(robot);
    SetControlRotation(control);

    GhostCharacter->OnBeginPossession(robot);
    robot->OnBeginPossession(GhostCharacter);
}

//------------------------------------------------------------------------

void AUmbraPlayerController::UnpossessRobot(AUmbraRobotCharacter* robot)
{
    if(robot == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("'%s' - Unpossess Robot: Invalid Robot"), *GetNameSafe(this));
        return;
    }

    if(GhostCharacter == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("'%s' - Unpossess Robot: Invalid Ghost"), *GetNameSafe(this));
        return;
    }

    FRotator control = GetControlRotation();
    Possess(GhostCharacter);
    SetControlRotation(control);

    GhostCharacter->SetActorLocation(robot->GetActorLocation());
    GhostCharacter->SetActorRotation(robot->GetActorRotation());

    GhostCharacter->OnEndPossession(robot);
    robot->OnEndPossession(GhostCharacter);
}