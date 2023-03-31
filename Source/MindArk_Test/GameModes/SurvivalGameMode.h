// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SurvivalGameMode.generated.h"

class ATriggerVolume;
class ABoxTrigger;
/**
 * 
 */
UCLASS()
class MINDARK_TEST_API ASurvivalGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	ASurvivalGameMode();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Volumes")
	ATriggerVolume* EndPlatform;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Rules")
	float Timer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Rules")
	FString Reason = "Timer Ran Out";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Rules")
	bool GameOver = false;

protected:

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	AActor* Player;
};
