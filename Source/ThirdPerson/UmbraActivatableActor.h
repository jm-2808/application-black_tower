// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UmbraActivatableActor.generated.h"

UCLASS()
class THIRDPERSON_API AUmbraActivatableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AUmbraActivatableActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

    // Activation
public:
    UFUNCTION(BlueprintCallable)
    void Activate();

    UFUNCTION(BlueprintCallable)
    void Deactivate();

protected:
    virtual void OnActivate();
    UFUNCTION(BlueprintNativeEvent, meta=(DisplayName="On Activated"))
    void NotifyOnActivate();

    virtual void OnDeactivate();
    UFUNCTION(BlueprintNativeEvent, meta=(DisplayName="On Deactivated"))
    void NotifyOnDeactivate();

protected:
    UPROPERTY(EditAnywhere)
    int RequiredActivations = 1;

private:
    int ActivationCount = 0;
    bool bActive = false;

};
