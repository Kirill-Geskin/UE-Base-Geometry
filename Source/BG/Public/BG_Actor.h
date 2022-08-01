// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BG_Actor.generated.h"

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	Sin,
	Static
};

USTRUCT(BlueprintType)
struct FGeometryData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Amplitude = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Frequency = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	EMovementType MoveType = EMovementType::Static;
};

UCLASS()
class BG_API ABG_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABG_Actor();


	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geometry Data")
		FGeometryData GeometryData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float Amplitude = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float Frequency = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Weapon")
		int32 weapons_num = 4;

	UPROPERTY(EditDefaultsOnly, Category = "Stat")
		int32 kills_num = 7;

	UPROPERTY(EditInstanceOnly, Category = "Health")
		float health = 34.435235f;

	UPROPERTY(EditAnywhere, Category = "Health")
		bool is_dead = false;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
		bool has_weapon = true;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FVector	InitialLocation;
	void print_types();
	void print_string_types();
	void print_transform();
	void HandleMovement();


};
