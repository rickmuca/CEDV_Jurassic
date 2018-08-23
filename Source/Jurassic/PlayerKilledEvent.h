// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameEvent.h"
#include "PlayerKilledEvent.generated.h"

/**
 * Event to detect when the player is about to be killed
 */
UCLASS(BlueprintType)
class JURASSIC_API UPlayerKilledEvent : public UGameEvent
{
	GENERATED_BODY()
	
public:
	FString Type;

	UPlayerKilledEvent();
	~UPlayerKilledEvent();
};
