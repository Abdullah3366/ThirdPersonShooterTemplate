// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivalGameMode.h"
#include "Engine/TriggerVolume.h"

ASurvivalGameMode::ASurvivalGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	EndPlatform = CreateDefaultSubobject<ATriggerVolume>("EndPlatformVolume");
	//EndPlatform->SetOwner(this);
}

void ASurvivalGameMode::BeginPlay()
{
	Timer = 180.f;
	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void ASurvivalGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timer = Timer - DeltaTime;

	if (Timer < 0.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Time Over"));
		Player->Destroy();		
		Reason = "You ran out of time";
		GameOver = true;
	}
}
