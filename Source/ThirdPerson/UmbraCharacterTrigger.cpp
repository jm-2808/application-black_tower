// Fill out your copyright notice in the Description page of Project Settings.

#include "UmbraCharacterTrigger.h"

#include "ThirdPersonCharacter.h"
#include "UmbraRobotCharacter.h"
#include "UmbraActivatableActor.h"

#include "Components/BoxComponent.h"

//////////////////////////////////////////////////////////////////////////
// AUmbraCharacterTrigger

AUmbraCharacterTrigger::AUmbraCharacterTrigger()
{
    Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
    RootComponent = Trigger;
    Trigger->SetBoxExtent(FVector(150.0f, 150.0f, 150.0f));
    Trigger->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

    CharacterClass = AUmbraRobotCharacter::StaticClass();
}

//////////////////////////////////////////////////////////////////////////
// AActor

void AUmbraCharacterTrigger::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    if(CharacterClass == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("'%s' - Actor Begin Overlap: Invalid Character Class"), *GetNameSafe(this));
        return;
    }

    if(OtherActor->GetClass()->IsChildOf(CharacterClass))
    {
        TArray<AActor*> Result;
        GetOverlappingActors(Result, CharacterClass);
        if(Result.Num() == 1)
        {
            Activate();
        }
    }
}

//------------------------------------------------------------------------

void AUmbraCharacterTrigger::NotifyActorEndOverlap(AActor* OtherActor)
{
    Super::NotifyActorEndOverlap(OtherActor);

    if(CharacterClass == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("'%s' - Actor End Overlap: Invalid Character Class"), *GetNameSafe(this));
        return;
    }

    if(OtherActor->GetClass()->IsChildOf(CharacterClass))
    {
        TArray<AActor*> Result;
        GetOverlappingActors(Result, CharacterClass);
        if(Result.Num() == 0)
        {
            Deactivate();
        }
    }
}

//////////////////////////////////////////////////////////////////////////
// Trigger

void AUmbraCharacterTrigger::Activate()
{
    bActive = true;
    OnActivate();
    NotifyOnActivate();

    for(int i = 0; i < ActivatableActors.Num(); ++i)
    {
        ActivatableActors[i]->Activate();
    }
}

//------------------------------------------------------------------------

void AUmbraCharacterTrigger::OnActivate() { }

//------------------------------------------------------------------------

void AUmbraCharacterTrigger::NotifyOnActivate_Implementation() { }

//------------------------------------------------------------------------

void AUmbraCharacterTrigger::Deactivate()
{
    bActive = false;
    OnDeactivate();
    NotifyOnDeactivate();

    for(int i = 0; i < ActivatableActors.Num(); ++i)
    {
        ActivatableActors[i]->Deactivate();
    }
}

//------------------------------------------------------------------------

void AUmbraCharacterTrigger::OnDeactivate() { }

//------------------------------------------------------------------------

void AUmbraCharacterTrigger::NotifyOnDeactivate_Implementation() { }