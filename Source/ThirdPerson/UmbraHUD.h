// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UmbraHUD.generated.h"

UCLASS()
class THIRDPERSON_API AUmbraHUD : public AHUD
{
	GENERATED_BODY()
	
    // AActor interface
protected:
	virtual void BeginPlay();

};
