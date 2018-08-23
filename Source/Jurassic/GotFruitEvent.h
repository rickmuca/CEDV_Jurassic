// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameEvent.h"
#include "GotFruitEvent.generated.h"

/**
 * Got fruit broadcasting event
 */
UCLASS()
class JURASSIC_API UGotFruitEvent : public UGameEvent
{
	GENERATED_BODY()

public:
	UGotFruitEvent();
	~UGotFruitEvent();
};
