// Fill out your copyright notice in the Description page of Project Settings.

#include "UmbraActivatableActor.h"

//////////////////////////////////////////////////////////////////////////
// AUmbraActivatableActor

AUmbraActivatableActor::AUmbraActivatableActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

//////////////////////////////////////////////////////////////////////////
// AActor

void AUmbraActivatableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUmbraActivatableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//////////////////////////////////////////////////////////////////////////
// Activation

void AUmbraActivatableActor::Activate()
{
    ++ActivationCount;
    if(!bActive && (ActivationCount >= RequiredActivations))
    {
        bActive = true;

        OnActivate();
        NotifyOnActivate();
    }
}

//------------------------------------------------------------------------

void AUmbraActivatableActor::Deactivate()
{
    --ActivationCount;
    if(bActive && (ActivationCount < RequiredActivations))
    {
        bActive = false;

        OnDeactivate();
        NotifyOnDeactivate();
    }
}

//------------------------------------------------------------------------

void AUmbraActivatableActor::OnActivate() { }

//------------------------------------------------------------------------

void AUmbraActivatableActor::NotifyOnActivate_Implementation() { }

//------------------------------------------------------------------------

void AUmbraActivatableActor::OnDeactivate() { }

//------------------------------------------------------------------------

void AUmbraActivatableActor::NotifyOnDeactivate_Implementation() { }