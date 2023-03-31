// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "MindArk_Test/Weapons/Gun.h"
#include "MindArk_Test/GameModes/SurvivalGameMode.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Movement = GetCharacterMovement();

}
// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APlayerCharacter::LookRight);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &APlayerCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &APlayerCharacter::LookRightRate);
	PlayerInputComponent->BindAction(TEXT("Boost"), IE_Pressed, this, &APlayerCharacter::BoostStart);
	PlayerInputComponent->BindAction(TEXT("Boost"), IE_Released, this, &APlayerCharacter::BoostStop);
	PlayerInputComponent->BindAction(TEXT("ZoomIn"), IE_Pressed, this, &APlayerCharacter::ZoomIn);
	PlayerInputComponent->BindAction(TEXT("ZoomOut"), IE_Pressed, this, &APlayerCharacter::ZoomOut);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &APlayerCharacter::Fire);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	CharacterMesh = this->GetMesh();
	CharacterMesh->SetupAttachment(RootComponent);
	NormalSpeed = Movement->MaxWalkSpeed;
	NormalAcceleration = Movement->MaxAcceleration;

	if (MainGunClass)
	{
		PrimaryWeapon = GetWorld()->SpawnActor<AGun>(MainGunClass);
		PrimaryWeapon->AttachToComponent(CharacterMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("Gun_Socket"));
		PrimaryWeapon->SetOwner(this);
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Health <= 0.f)
	{
		if (this->IsPlayerControlled())
		{
			Cast<ASurvivalGameMode>(GetWorld()->GetAuthGameMode())->GameOver = true;
			Cast<ASurvivalGameMode>(GetWorld()->GetAuthGameMode())->Reason = "Player was killed by enemies";
		}

		this->Destroy();
		PrimaryWeapon->Destroy();
	}

	if (IsHeating)
	{
		Heat = Heat + DeltaTime * HeatRate;
	}

	if (IsCooling && Heat > 0)
	{
		Heat = Heat - DeltaTime * HeatRate;
	}

	if (Heat > MaxHeat)
	{
		BoostStop();
		Heat--;
	}

}


void APlayerCharacter::MoveForward(float Axisvalue)
{
	AddMovementInput(GetActorForwardVector() * Axisvalue);
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void APlayerCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
	VerticalAxisValue = AxisValue;
}

void APlayerCharacter::LookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue);
	HorizontalAxisValue = AxisValue;
}

void APlayerCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->DeltaTimeSeconds);
}

void APlayerCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->DeltaTimeSeconds);
}


void APlayerCharacter::BoostStart()
{
	Movement->MaxWalkSpeed = BoostSpeed;
	Movement->MaxAcceleration = BoostAcceleration;
	IsDodge = true;
	IsHeating = true;
	IsCooling = false;
	GetWorldTimerManager().SetTimer(TH_BoostType, this, &APlayerCharacter::SetBoostType, 1.f, false, 0.200);
}

void APlayerCharacter::BoostStop()
{
	Movement->MaxWalkSpeed = NormalSpeed;
	Movement->MaxAcceleration = NormalAcceleration;
	if (IsDodge == true && (Heat + BoostHeat) < MaxHeat)
	{
		Heat = Heat + BoostHeat;
		DoDodge = true;
		LaunchCharacter(GetLastMovementInputVector() * 2000.f, false, false);
	}
	else
	{
		DoDodge = false;
	}

	IsHeating = false;

	if (Heat > 90)
	{
		GetWorldTimerManager().SetTimer(TH_CoolingDelay, this, &APlayerCharacter::CoolingDelaySet, 1.f, false, 2);    
	}
	else
	{
		IsCooling = true;
		IsHeating = false;
	}
}


void APlayerCharacter::ZoomIn()
{
	if (ZoomStatus == 0)
	{
		Camera->FieldOfView = Camera->FieldOfView - 50.f;
	}
	if (ZoomStatus == -1)
	{
		Camera->FieldOfView = Camera->FieldOfView - 10.f;
	}
	if (ZoomStatus < 1)
	{
		ZoomStatus++;
		SpringArm->TargetArmLength = SpringArm->TargetArmLength - 50.f;
	}
}

void APlayerCharacter::ZoomOut()
{
	if (ZoomStatus == 1)
	{
		Camera->FieldOfView = Camera->FieldOfView + 50.f;
	}
	if (ZoomStatus == 0)
	{
		Camera->FieldOfView = Camera->FieldOfView + 10.f;
	}
	if (ZoomStatus > -1)
	{
		ZoomStatus--;
		SpringArm->TargetArmLength = SpringArm->TargetArmLength + 50.f;
	}
}

void APlayerCharacter::SetBoostType()
{
	IsDodge = false;
	DoDodge = false;
	GetWorldTimerManager().ClearTimer(TH_BoostType);
}


void APlayerCharacter::CoolingDelaySet()
{
	IsCooling = true;
	GetWorldTimerManager().ClearTimer(TH_CoolingDelay);
}

void APlayerCharacter::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire"));
	PrimaryWeapon->Fire();
}

