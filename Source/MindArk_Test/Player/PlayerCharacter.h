// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UCapsuleComponent;
class UCharacterMovementComponent;
class USkeletalMeshComponent;
class AGun;
class ATriggerVolume;

UCLASS()
class MINDARK_TEST_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "True"))
	AGun* PrimaryWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "True"))
	float Health = 100.f;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "True"))
		UCameraComponent* Camera;

	FTimerHandle TH_BoostType;
	FTimerHandle TH_CoolingDelay;

	void CoolingDelaySet();

	void SetBoostType();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int ZoomStatus = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float BoostSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float BoostAcceleration;
	
	float NormalSpeed;
	float NormalAcceleration;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float Heat = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxHeat = 100.f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool IsDodge = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool DoDodge = false;

	float HeatRate = 10.f;
	float BoostHeat = 40.f;
	bool IsHeating = false;
	bool IsCooling = true;

	bool IsJump = true;


	float HorizontalAxisValue = 0.f;
	float VerticalAxisValue = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "True"))
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "True"))
	UCharacterMovementComponent* Movement;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "True"))
	USkeletalMeshComponent* CharacterMesh;

private:

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookRight(float AxisValue);
	void LookUp(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);
	void BoostStart();
	void BoostStop();
	void ZoomIn();
	void ZoomOut();

	UFUNCTION(BlueprintCallable)
	void Fire();

	UPROPERTY(EditAnywhere)
	float RotationRate = 10.f;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> MainGunClass;
};
