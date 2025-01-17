// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScorePresenter.generated.h"

UCLASS()
class JURASSIC_API AScorePresenter : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AScorePresenter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> ScoreTextWidget;

	TWeakObjectPtr<class UUserWidget> pScoreTextWidget;

	TWeakObjectPtr<class UTextBlock> pScoreText;
	TWeakObjectPtr<class UTextBlock> pAppleText;

	UFUNCTION(BlueprintCallable, Category = "Score")
	void SetScore(int Score);

	UFUNCTION(BlueprintCallable, Category = "Apples")
	void SetApples(int Apples);
};

