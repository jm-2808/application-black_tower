// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThirdPersonCharacter.h"
#include "UmbraRobotCharacter.generated.h"

class AUmbraGhostCharacter;

UCLASS()
class THIRDPERSON_API AUmbraRobotCharacter : public AThirdPersonCharacter
{
	GENERATED_BODY()
	
    /** Unpossess Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* UnpossessAction;

public:
    AUmbraRobotCharacter();

	// APawn interface
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Highlight
public:
    UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="Begin Highlight"))
    void BeginHighlight(const FString& prompt);

    UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="End Highlight"))
    void EndHighlight();

    // Possession
public:
    UFUNCTION(BlueprintPure)
    const bool IsPossessed() const { return bIsPossessed; }

    UFUNCTION(BlueprintNativeEvent, meta=(DisplayName="On Begin Possession"))
    void OnBeginPossession(AUmbraGhostCharacter* ghost);

    UFUNCTION(BlueprintNativeEvent, meta=(DisplayName="On End Possession"))
    void OnEndPossession(AUmbraGhostCharacter* ghost);

protected:
    void TryUnpossess();

private:
    bool bIsPossessed = false;
    
};
