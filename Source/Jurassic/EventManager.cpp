// Fill out your copyright notice in the Description page of Project Settings.

#include "EventManager.h"
#include "EngineMinimal.h"
#include "EngineUtils.h"
#include "EventBus.h"
#include "MySaveGame.h"
#include "PlayerKilledEvent.h"
#include "KillEnemyEvent.h"
#include "GotFruitEvent.h"
#include "GotKeyEvent.h"
#include "JurassicGameStateBase.h"

// Sets default values
AEventManager::AEventManager() : KilledEnemies(0), Score(0), FruitsCollected(0), GotKey(false)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (KilledEnemiesToGainBonus <= 0) {
		this->KilledEnemiesToGainBonus = 10;
	}
}

// Called when the game starts or when spawned
void AEventManager::BeginPlay()
{
	Super::BeginPlay();

	Instance = this;
	if (GetWorld() != NULL) {
		AJurassicGameStateBase* GameState = GetWorld()->GetGameState<AJurassicGameStateBase>();

		EventBus = GameState->GetEventBus();
		if (EventBus != NULL) {
			EventBus->Register(Instance.Get());
		}
	}
}

// Called every frame
void AEventManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEventManager::OnNotify(UObject* Entity, UGameEvent* Event)
{
	if (Event == NULL) return;

	switch (Event->Code) {
	case UGameEvent::KILL_EVENT:
		this->KilledEnemies++;

		if (Event->IsA(UKillEnemyEvent::StaticClass())) {
			UKillEnemyEvent* KillEvent = Cast<UKillEnemyEvent>(Event);
			this->EvaluateScoreAccordingKilledEnemies(KillEvent->Score);
		}
		break;

	case UGameEvent::GOT_KEY_EVENT:
		this->GotKey = true;
		break;

	case UGameEvent::GOT_FRUIT_EVENT:
		this->FruitsCollected++;
		this->ShowFruitsCollected();
		break;

	case UGameEvent::PLAYER_KILLED_EVENT:
		this->SaveGame();
		TWeakObjectPtr<APawn> PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		/*UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleSystem.Get(), PlayerPawn.Get()->GetActorLocation());
		UGameplayStatics::OpenLevel(GetWorld(), "MainMap");*/
		break;
	}
}

// Save current score and name
void AEventManager::SaveGame()
{
	FDateTime currentDateTime = FDateTime::Now();

	// Player name will be the current date in this version
	UMySaveGame::SaveMaxScore(currentDateTime.ToString(), this->Score);
}

void AEventManager::ShowFruitsCollected() {
	if (ScorePresenter != NULL) {
		ScorePresenter->SetApples(this->FruitsCollected);
	}
}

void AEventManager::EvaluateScoreAccordingKilledEnemies(int32 ScoreToAdd) {
	this->Score += ScoreToAdd;
	if (this->KilledEnemies >= KilledEnemiesToGainBonus) {
		this->KilledEnemies = 0;
		this->Score += ScoreToAdd + this->Score / 5;
	}

	if (ScorePresenter != NULL) {
		ScorePresenter->SetScore(this->Score);
	}
}
