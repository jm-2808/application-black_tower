// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UmbraCharacterTrigger.generated.h"

class UBoxComponent;
class AThirdPersonCharacter;
class AUmbraActivatableActor;

UCLASS()
class THIRDPERSON_API AUmbraCharacterTrigger : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    UBoxComponent* Trigger;

public:	
	AUmbraCharacterTrigger();

    // AActor interface
public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

    // Trigger
public:
    UFUNCTION(BlueprintPure)
    const bool IsActivated() const { return bActive; }

protected:
    UFUNCTION(BlueprintCallable)
    void Activate();
    virtual void OnActivate();
    UFUNCTION(BlueprintNativeEvent, meta=(DisplayName="On Activated"))
    void NotifyOnActivate();

    UFUNCTION(BlueprintCallable)
    void Deactivate();
    virtual void OnDeactivate();
    UFUNCTION(BlueprintNativeEvent, meta=(DisplayName="On Deactivated"))
    void NotifyOnDeactivate();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<AThirdPersonCharacter> CharacterClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<AUmbraActivatableActor*> ActivatableActors;

private:
    bool bActive = false;

};
