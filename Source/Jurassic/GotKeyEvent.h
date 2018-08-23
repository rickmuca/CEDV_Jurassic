// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameEvent.h"
#include "GotKeyEvent.generated.h"

/**
 * Event to broadrcast once the player got the key
 */
UCLASS(BlueprintType)
class JURASSIC_API UGotKeyEvent : public UGameEvent
{
	GENERATED_BODY()
	
public:
	UGotKeyEvent();
	~UGotKeyEvent();
};
