// Copyright 2019 SoonBo Noh. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "T4WorldAsset.generated.h"

/**
  * #83
 */
struct FT4WorldCustomVersion
{
	enum Type
	{
		InitializeVer = 0,

		// -----<new versions can be added above this line>-------------------------------------------------
		VersionPlusOne,
		LatestVersion = VersionPlusOne - 1,
	};

	T4ASSET_API const static FGuid GUID;

private:
	FT4WorldCustomVersion() {}
};

USTRUCT()
struct T4ASSET_API FT4WorldEditorTransientActorData
{
	GENERATED_USTRUCT_BODY()

public:
	FT4WorldEditorTransientActorData()
		: SubLevelPackageName(NAME_None)
	{
		
	}

	UPROPERTY(EditAnywhere, Transient)
	FName SubLevelPackageName; // #85
};

USTRUCT()
struct T4ASSET_API FT4WorldEditorTransientData
{
	GENERATED_USTRUCT_BODY()

public:
	FT4WorldEditorTransientData()
	{
		Reset();
	}

	void Reset()
	{
#if WITH_EDITOR
		SubLevel = NAME_None;
		PackageName = NAME_None;
		ParentPackageName = NAME_None;
		LayerName = NAME_None;
		StreamingDistance = 0.0f;
		DistanceStreamingEnabled = true;
		Actors = 0;
		BoundExtent = FVector2D::ZeroVector;
		Position = FIntVector::ZeroValue;
		AbsolutePosition = FIntVector::ZeroValue;
		ZOrder = 0;
		LODNums = 0;
		LODIndex = 0;
#endif
	}

	// Tile long package name (readonly)	
	UPROPERTY(VisibleAnywhere, Transient)
	FName							SubLevel;

	// Tile long package name (readonly)	
	UPROPERTY(VisibleAnywhere, Transient)
	FName							PackageName;
	
	// Parent tile long package name	
	UPROPERTY(VisibleAnywhere, Transient)
	FName							ParentPackageName;

	UPROPERTY(VisibleAnywhere, Transient)
	FName							LayerName;

	UPROPERTY(VisibleAnywhere, Transient)
	float							StreamingDistance;

	UPROPERTY(VisibleAnywhere, Transient)
	bool							DistanceStreamingEnabled;

	UPROPERTY(VisibleAnywhere, Transient)
	int32							Actors;

	UPROPERTY(VisibleAnywhere, Transient)
	FVector2D						BoundExtent;

	// Tile position in the world, relative to parent 
	UPROPERTY(VisibleAnywhere, Transient)
	FIntVector						Position;

	UPROPERTY(VisibleAnywhere, Transient)
	FIntVector						AbsolutePosition;

	UPROPERTY(VisibleAnywhere, Transient, meta=(ClampMin = "-1000", ClampMax = "1000", UIMin = "-1000", UIMax = "1000"))
	int32							ZOrder;

	UPROPERTY(VisibleAnywhere, Transient)
	int32							LODNums;

	UPROPERTY(VisibleAnywhere, Transient)
	int32							LODIndex;
};

class UTexture2D;
class UT4EntityAsset;

UCLASS(ClassGroup = Tech4Labs, Category = "Tech4Labs")
class T4ASSET_API UT4WorldAsset : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	//~ Begin UObject interface
	void Serialize(FArchive& Ar) override;
	virtual void PostLoad() override;
#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	void GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const override;
	//~ End UObject interface

#if WITH_EDITOR
	virtual void ResetEditorTransientData()
	{
		EditorTransientData.Reset();
	}

	DECLARE_MULTICAST_DELEGATE(FT4OnPropertiesChanged);
	FT4OnPropertiesChanged& OnPropertiesChanged() { return OnPropertiesChangedDelegate; }
#endif // WITH_EDITOR

public:
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Level Asset"))
	TSoftObjectPtr<UWorld> LevelAsset;

#if WITH_EDITORONLY_DATA
	UPROPERTY()
	UTexture2D* ThumbnailImage; // Internal: The thumbnail image

	// #71 : WARN : CustomizeCharacterEntityDetails 에서 사용하는 임시 프로퍼티! (저장되지 않는다!!)
	// TODO : Transient 설정으로 Editor Dirty 가 발생함으로 다른 방법 고려 필요
	UPROPERTY(EditAnywhere, Transient)
	FT4WorldEditorTransientData EditorTransientData;
#endif

private:
#if WITH_EDITOR
	FT4OnPropertiesChanged OnPropertiesChangedDelegate;
#endif
};
