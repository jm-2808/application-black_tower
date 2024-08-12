// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThirdPersonCharacter.h"
#include "UmbraGhostCharacter.generated.h"

class AUmbraRobotCharacter;

UCLASS()
class THIRDPERSON_API AUmbraGhostCharacter : public AThirdPersonCharacter
{
	GENERATED_BODY()
	
    /** Possess Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PossessAction;

    /** Teleport Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* TeleportAction;

public:
    AUmbraGhostCharacter();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString PossessPrompt = "Press [E] / [Left Face Button] to Possess";

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString TeleportPrompt = "Release [Q] / [Right Face Button] to Possess";

    // AActor interface
protected:
	virtual void BeginPlay();

public:
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	// APawn interface
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Possession
public:
    UFUNCTION(BlueprintPure)
    const bool IsPossessing() const { return bIsPossessing; }

    UFUNCTION(BlueprintNativeEvent, meta=(DisplayName="On Begin Possession"))
    void OnBeginPossession(AUmbraRobotCharacter* robot);

    UFUNCTION(BlueprintNativeEvent, meta=(DisplayName="On End Possession"))
    void OnEndPossession(AUmbraRobotCharacter* robot);

protected:
    void TryPossess();

private:
    bool bIsPossessing = false;

    // Teleport
protected:
    void BeginTeleport();
    void EndTeleport();

    void UpdateTeleport(float deltaTime);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float MaximumTeleportRange = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float TeleportRangeRate = 750.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<AActor> MarkerClass;

private:
    bool bIsTeleporting = false;
    float TeleportRange = 0.0f;
    
    FVector TeleportLocation;
    UPROPERTY()
    AUmbraRobotCharacter* TeleportTarget = nullptr;
    UPROPERTY()
    AActor* TeleportMarker = nullptr;

};
