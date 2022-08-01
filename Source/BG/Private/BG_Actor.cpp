// Fill out your copyright notice in the Description page of Project Settings.

#include "BG_Actor.h"
#include "..\Public\BG_Actor.h"
#include "Engine/Engine.h"
#include "TimerManager.h"



DEFINE_LOG_CATEGORY_STATIC(Log_BG, All, All)

// Sets default values
ABG_Actor::ABG_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	SetRootComponent(BaseMesh);

}

// Called when the game starts or when spawned
void ABG_Actor::BeginPlay()
{
	Super::BeginPlay();


	InitialLocation = GetActorLocation();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABG_Actor::OnTimerFired, GeometryData.TimerRate, true);


	SetColor(GeometryData.Color);
	// print_string_types();
	// print_transform();
	// print_types();

}

// Called every frame
void ABG_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	HandleMovement();
}

void ABG_Actor::print_types()
{
	UE_LOG(Log_BG, Warning, TEXT("Actor name %s"), *GetName());
	UE_LOG(Log_BG, Warning, TEXT("Weapons num: %d, Kills num: %i"), weapons_num, kills_num);
	UE_LOG(Log_BG, Warning, TEXT("Health: %.f"), health);
	UE_LOG(Log_BG, Warning, TEXT("Is dead: %d"), is_dead);
	UE_LOG(Log_BG, Warning, TEXT("Has weapon: %d"), static_cast<int>(has_weapon));

}

void ABG_Actor::print_string_types()
{
	FString Name = "John Connor";
	UE_LOG(Log_BG, Display, TEXT("Name: %s"), *Name);

	FString WeaponsNumStr = "Weapons num = " + FString::FromInt(weapons_num);
	FString HealthStr = "Health = " + FString::SanitizeFloat(health);
	FString IsDeadStr = "Is dead = " + FString(is_dead ? "true" : "false");

	FString Stat = FString::Printf(TEXT(" \n == All Stat == \n %s \n %s \n %s "), *WeaponsNumStr, *HealthStr, *IsDeadStr);

	UE_LOG(Log_BG, Warning, TEXT("%s"), *Stat);

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, Name);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Stat, true, FVector2D(1.5f, 1.5f));
}

void ABG_Actor::print_transform()
{
	FTransform Transform = GetActorTransform();

	FVector Location = Transform.GetLocation();
	FRotator Rotation = Transform.Rotator();
	FVector Scale = Transform.GetScale3D();

	UE_LOG(Log_BG, Warning, TEXT("Actor name %s"), *GetName());
	UE_LOG(Log_BG, Warning, TEXT("Transform %s"), *Transform.ToString());
	UE_LOG(Log_BG, Warning, TEXT("Location %s"), *Location.ToString());
	UE_LOG(Log_BG, Warning, TEXT("Rotation %s"), *Rotation.ToString());
	UE_LOG(Log_BG, Warning, TEXT("Scale %s"), *Scale.ToString());
	UE_LOG(Log_BG, Error, TEXT("Human transform %s"), *Transform.ToHumanReadableString());
}

void ABG_Actor::HandleMovement()
{
	switch (GeometryData.MoveType)
	{
	case EMovementType::Sin:
	{
		// z = z0 + amplitude * sin(freq * t);
		FVector CurrentLocation = GetActorLocation();
		if (GetWorld())
		{
			float Time = GetWorld()->GetTimeSeconds();
			CurrentLocation.Z = InitialLocation.Z + GeometryData.Amplitude * FMath::Sin(GeometryData.Frequency * Time);

			SetActorLocation(CurrentLocation);
		}
	}
	break;

	case EMovementType::Static: break;
	default: break;
	}
}

void ABG_Actor::SetColor(const FLinearColor& Color)
{
	UMaterialInstanceDynamic* DynMaterial = BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
	if (DynMaterial)
	{
		DynMaterial->SetVectorParameterValue("Color", Color);
	}
}

void ABG_Actor::OnTimerFired()
{

	FLinearColor NewColor = FLinearColor::MakeRandomColor();
	UE_LOG(Log_BG, Display, TEXT("TimerCount: %i, Color to set up: %s"), *NewColor.ToString());
	SetColor(NewColor);

}
