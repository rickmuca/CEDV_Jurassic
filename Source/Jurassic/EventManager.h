// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Observer.h"
#include "JurassicGameStateBase.h"
#include "ScorePresenter.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EventManager.generated.h"

UCLASS()
class JURASSIC_API AEventManager : public AActor, public IObserver
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEventManager();

	void OnNotify(UObject* Entity, UGameEvent* Event) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ScorePresenter")
	AScorePresenter* ScorePresenter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BonusCodition")
	int32 KilledEnemiesToGainBonus;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY()
	UEventBus* EventBus;

	UPROPERTY()
	TWeakObjectPtr<AEventManager> Instance;

	int32 Score;
	int32 KilledEnemies;
	int32 FruitsCollected;
	bool GotKey;

	// Save game on game over
	void SaveGame();

	// Present un UX fruits collected
	void ShowFruitsCollected();

	// Evaluate whether gain bonus or not
	void EvaluateScoreAccordingKilledEnemies(int32 ScoreToAdd);
};
