// Fill out your copyright notice in the Description page of Project Settings.


#include "EndPlatform.h"
#include "Engine/TriggerVolume.h"
#include "Kismet/GameplayStatics.h"
#include "SurvivalGameMode.h"

// Sets default values
AEndPlatform::AEndPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEndPlatform::BeginPlay()
{
	Super::BeginPlay();

	//EndPlatform->SetOwner(this);
	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void AEndPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (EndPlatformVol->IsOverlappingActor(Player))
	{
		Cast<ASurvivalGameMode>(GetWorld()->GetAuthGameMode())->GameOver = true;
		Cast<ASurvivalGameMode>(GetWorld()->GetAuthGameMode())->Reason = "Player reached Extraction Point";
		Player->Destroy();
	}
}

