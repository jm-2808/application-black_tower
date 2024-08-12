// Fill out your copyright notice in the Description page of Project Settings.

#include "UmbraGameMode.h"

#include "UmbraPlayerController.h"

#include "GameFramework/HUD.h"
#include "UObject/ConstructorHelpers.h"

AUmbraGameMode::AUmbraGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Umbra/Characters/BP_UmbraGhostCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

    PlayerControllerClass = AUmbraPlayerController::StaticClass();

	static ConstructorHelpers::FClassFinder<AHUD> HUDBPClass(TEXT("/Game/ThirdPerson/Umbra/HUD/UI_HUD"));
	if (HUDBPClass.Class != NULL)
	{
		HUDClass = HUDBPClass.Class;
	}
}
