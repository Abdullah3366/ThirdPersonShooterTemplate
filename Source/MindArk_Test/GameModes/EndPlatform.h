// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndPlatform.generated.h"

class ATriggerVolume;

UCLASS()
class MINDARK_TEST_API AEndPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEndPlatform();

	UPROPERTY(EditAnywhere)
	ATriggerVolume* EndPlatformVol;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:

	UPROPERTY(EditAnywhere)
	AActor* Player;
};
