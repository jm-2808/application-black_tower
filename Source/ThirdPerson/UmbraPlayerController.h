// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UmbraPlayerController.generated.h"

class AUmbraGhostCharacter;
class AUmbraRobotCharacter;

UCLASS()
class THIRDPERSON_API AUmbraPlayerController : public APlayerController
{
	GENERATED_BODY()

    // Possession
public:
    UFUNCTION(BlueprintPure, Category="Possession")
    AUmbraGhostCharacter* GetGhost() { return GhostCharacter; }

    UFUNCTION(BlueprintCallable, Category="Possession")
    void RegisterGhost(AUmbraGhostCharacter* ghost) { GhostCharacter = ghost; }
    
    UFUNCTION(BlueprintCallable, Category="Possession")
    void PossessRobot(AUmbraRobotCharacter* robot);

    UFUNCTION(BlueprintCallable, Category="Possession")
    void UnpossessRobot(AUmbraRobotCharacter* robot);

private:
    UPROPERTY()
    AUmbraGhostCharacter* GhostCharacter = nullptr;
	
};
