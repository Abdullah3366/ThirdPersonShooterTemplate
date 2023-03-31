// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UStaticMeshComponent;
class USceneComponent;
class UProjectileMovementComponent;


UCLASS()
class MINDARK_TEST_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed", meta = (AllowPrivateAccess = "True"))
		float InitialSpeed = 50000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed", meta = (AllowPrivateAccess = "True"))
		float MaxSpeed = 50000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (AllowPrivateAccess = "True"))
		float Lifespan = 3.f;
	UPROPERTY(EditAnywhere)
		USoundBase* BulletSound;

private:

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BulletMesh;
	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* ProjectileComp;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> DamageType;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
