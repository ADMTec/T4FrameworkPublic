// Copyright 2019 SoonBo Noh. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "T4CommonAssetStructs.generated.h"

/**
  * #100
 */
USTRUCT()
struct T4ASSET_API FT4EditorPointOfInterest
{
	GENERATED_USTRUCT_BODY()

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = Editor)
	FName MapEntityName;

	UPROPERTY(EditAnywhere, Category = Editor)
	FVector SpawnLocation;

	UPROPERTY(EditAnywhere, Category = Editor)
	FRotator SpawnRotation;
#endif

public:
	FT4EditorPointOfInterest()
#if WITH_EDITORONLY_DATA
		: MapEntityName(NAME_None)
		, SpawnLocation(FVector::ZeroVector)
		, SpawnRotation(FRotator::ZeroRotator)
#endif
	{
	}
};

USTRUCT()
struct T4ASSET_API FT4EditorTestAutomation
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Editor)
	TArray<FT4EditorPointOfInterest> PointOfInterests;
};