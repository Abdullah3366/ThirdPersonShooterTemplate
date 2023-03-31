// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MindArk_TestGameModeBase.generated.h"

/**
 * 
 */
class ATriggerVolume;

UCLASS()
class MINDARK_TEST_API AMindArk_TestGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Volumes")
	ATriggerVolume* EndPlatform;

protected:

	virtual void BeginPlay() override;
};
