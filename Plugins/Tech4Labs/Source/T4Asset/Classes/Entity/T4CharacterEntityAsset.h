// Copyright 2019 SoonBo Noh. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "T4EntityAsset.h"
#include "Public/T4AssetDefinitions.h" // #74
#include "T4CharacterEntityAsset.generated.h"

/**
  * #35
 */
struct FT4CharacterEntityCustomVersion
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
	FT4CharacterEntityCustomVersion() {}
};

class USkeleton;
class UPhysicsAsset; // #76
class UMaterialInterface; // #80
class USkeletalMesh;
class UAnimBlueprint;
class UAnimMontage;
class UBlendSpace;
class UT4AnimSetAsset; // #39
class UT4ContiAsset; // #74
class UT4WeaponEntityAsset; // #74
class UT4CostumeEntityAsset;

USTRUCT()
struct T4ASSET_API FT4EntityCharacterPhysicalAttribute : public FT4EntityBasePhysicalAttribute
{
	GENERATED_USTRUCT_BODY()

public:
	FT4EntityCharacterPhysicalAttribute()
		: RunSpeed(600.0f)
		, WalkSpeed(200.0f)
		, LockOnSpeed(300.0f)
		, JumpZVelocity(550.0f) // #46
		, RollZVelocity(250.0f) // #46
		, RotationYawRate(520.0f)
	{
	}

	// CustomizeCharacterEntityDetails

	UPROPERTY(EditAnywhere, Category = Physical, meta = (ClampMin = "10.0", ClampMax = "1000"))
	float RunSpeed;

	UPROPERTY(EditAnywhere, Category = Physical, meta = (ClampMin = "10.0", ClampMax = "500"))
	float WalkSpeed;

	UPROPERTY(EditAnywhere, Category = Physical, meta = (ClampMin = "10.0", ClampMax = "500"))
	float LockOnSpeed;

	UPROPERTY(EditAnywhere, Category = Physical, meta = (ClampMin = "10.0", ClampMax = "1000"))
	float JumpZVelocity;

	UPROPERTY(EditAnywhere, Category = Physical, meta = (ClampMin = "5.0", ClampMax = "500"))
	float RollZVelocity; // #46

	UPROPERTY(EditAnywhere, Category = Physical, meta = (ClampMin = "10.0", ClampMax = "1080"))
	float RotationYawRate;
};

USTRUCT()
struct T4ASSET_API FT4EntityCharacterRenderingAttribute : public FT4EntityBaseRenderingAttribute
{
	GENERATED_USTRUCT_BODY()

public:
	FT4EntityCharacterRenderingAttribute()
	{
	}

	// CustomizeCharacterEntityDetails
};

USTRUCT()
struct T4ASSET_API FT4EntityCharacterFullBodyMeshData
{
	GENERATED_USTRUCT_BODY()

public:
	FT4EntityCharacterFullBodyMeshData()
	{
	}

	UPROPERTY(EditAnywhere, Category = Asset)
	TSoftObjectPtr<USkeletalMesh> SkeletalMeshAsset;

	UPROPERTY(EditAnywhere, Category = Asset)
	FT4EntityOverrideMaterialData OverrideMaterialData; // #80

	UPROPERTY(EditAnywhere, Category = Asset)
	TSoftObjectPtr<UPhysicsAsset> OverridePhysicsAsset; // #76 : Fullbody SK 라면 기본 세팅된 PhsycisAsset 을 그대로 사용하고, Override 할 경우만 재설정한다.
};

// #37
USTRUCT()
struct T4ASSET_API FT4EntityCharacterCompositePartMeshData
{
	GENERATED_USTRUCT_BODY()

public:
	FT4EntityCharacterCompositePartMeshData()
	{
	}

	// EntityCharacterSelectCompositePartByPartName

	UPROPERTY(EditAnywhere, Category = Asset)
	TSoftObjectPtr<UT4CostumeEntityAsset> CostumeEntityAsset;
};

// #37
USTRUCT()
struct T4ASSET_API FT4EntityCharacterCompositeMeshData
{
	GENERATED_USTRUCT_BODY()

public:
	FT4EntityCharacterCompositeMeshData()
		: ModularType(ET4EntityCharacterModularType::MasterPose)
	{
	}

	// CustomizeFullbodyMeshDetails

	UPROPERTY(EditAnywhere, Category = Property)
	ET4EntityCharacterModularType ModularType; // #72

	UPROPERTY(EditAnywhere, Category = Datas)
	TMap<FName, FT4EntityCharacterCompositePartMeshData> DefaultPartsData; // #37
};

// #73
USTRUCT()
struct T4ASSET_API FT4EntityCharacterStanceData
{
	GENERATED_USTRUCT_BODY()

public:
	FT4EntityCharacterStanceData()
		: ActiveLayerTag(NAME_None)
	{
	}

	// EntityCharacterSelectStanceDataByName

	UPROPERTY(EditAnywhere, Category = Asset)
	TSoftObjectPtr<UT4AnimSetAsset> AnimSetAsset; // #39

	UPROPERTY(EditAnywhere, Category = Property)
	FName ActiveLayerTag; // #74, #73
};

// #73
USTRUCT()
struct T4ASSET_API FT4EntityCharacterStanceSetData
{
	GENERATED_USTRUCT_BODY()

public:
	FT4EntityCharacterStanceSetData()
	{
	}

	UPROPERTY(EditAnywhere, Category = Asset)
	TMap<FName, FT4EntityCharacterStanceData> StanceMap; // #39, #73
};

// #76
USTRUCT()
struct T4ASSET_API FT4EntityCharacterReactionPhysicsBlendData
{
	GENERATED_USTRUCT_BODY()

public:
	FT4EntityCharacterReactionPhysicsBlendData()
		: TargetWeight(1.0f)
		, BlendInTimeSec(0.0f)
		, BlendOutTimeSec(0.0f)
	{
	}

	UPROPERTY(EditAnywhere, Category = Property)
	float TargetWeight;

	UPROPERTY(EditAnywhere, Category = Property)
	float BlendInTimeSec;

	UPROPERTY(EditAnywhere, Category = Property)
	float BlendOutTimeSec;
};

// #76
USTRUCT()
struct T4ASSET_API FT4EntityCharacterReactionPhysicsStartData
{
	GENERATED_USTRUCT_BODY()

public:
	FT4EntityCharacterReactionPhysicsStartData()
		: DelayTimeSec(0.0f)
		, ImpulseMainActionPoint(NAME_None)
		, ImpulseSubActionPoint(NAME_None)
		, ImpulsePower(0.0f)
		, CenterOfMass(FVector::ZeroVector)
		, MassOverrideInKg(100.0f)
		, bSimulateBodiesBelow(false)
	{
	}

	// EntityCharacterSelectReactionDataByName
	UPROPERTY(EditAnywhere, Category = Property)
	float DelayTimeSec;

	UPROPERTY(EditAnywhere, Category = Property)
	FName ImpulseMainActionPoint;

	UPROPERTY(EditAnywhere, Category = Property)
	FName ImpulseSubActionPoint;

	UPROPERTY(EditAnywhere, Category = Property)
	float ImpulsePower;

	UPROPERTY(EditAnywhere, Category = Property)
	FVector CenterOfMass;

	UPROPERTY(EditAnywhere, Category = Property)
	float MassOverrideInKg;

	UPROPERTY(EditAnywhere, Category = Property)
	bool bSimulateBodiesBelow;

	UPROPERTY(EditAnywhere, Category = Property)
	FT4EntityCharacterReactionPhysicsBlendData BlendData;
};

// #76
USTRUCT()
struct T4ASSET_API FT4EntityCharacterReactionPhysicsStopData
{
	GENERATED_USTRUCT_BODY()

public:
	FT4EntityCharacterReactionPhysicsStopData()
		: DelayTimeSec(0.0f)
	{
	}

	// EntityCharacterSelectReactionDataByName
	UPROPERTY(EditAnywhere, Category = Property)
	float DelayTimeSec;
};

// #76
USTRUCT()
struct T4ASSET_API FT4EntityCharacterReactionAnimationData
{
	GENERATED_USTRUCT_BODY()

public:
	FT4EntityCharacterReactionAnimationData()
		: DelayTimeSec(0.0f)
		, StartAnimSectionName(NAME_None)
		, LoopAnimSectionName(NAME_None)
		, BlendInTimeSec(T4AnimSetBlendTimeSec)
		, BlendOutTimeSec(T4AnimSetBlendTimeSec)
	{
	}

	// EntityCharacterSelectReactionDataByName
	UPROPERTY(EditAnywhere, Category = Property)
	float DelayTimeSec;

	UPROPERTY(EditAnywhere, Category = Property)
	FName StartAnimSectionName; // only locomotion layer

	UPROPERTY(EditAnywhere, Category = Property)
	FName LoopAnimSectionName; // only locomotion layer

	UPROPERTY(EditAnywhere, Category = Property)
	float BlendInTimeSec;

	UPROPERTY(EditAnywhere, Category = Property)
	float BlendOutTimeSec;
};

// #76
USTRUCT()
struct T4ASSET_API FT4EntityCharacterReactionData
{
	GENERATED_USTRUCT_BODY()

public:
	FT4EntityCharacterReactionData()
		: ReactionType(ET4EntityReactionType::None)
		, MaxPlayTimeSec(0.0f)
		, bUsePhysicsStart(false)
		, bUsePhysicsStop(false)
		, bUseAnimation(false)
	{
	}

	// EntityCharacterSelectReactionDataByName
	UPROPERTY(EditAnywhere, Category = Property)
	ET4EntityReactionType ReactionType;

	UPROPERTY(EditAnywhere, Category = Property)
	float MaxPlayTimeSec;

	UPROPERTY(EditAnywhere, Category = Property)
	bool bUsePhysicsStart;

	UPROPERTY(EditAnywhere, Category = Property, meta = (EditCondition = "bUsePhysicsStart"))
	FT4EntityCharacterReactionPhysicsStartData PhysicsStartData;

	UPROPERTY(EditAnywhere, Category = Property)
	bool bUsePhysicsStop;

	UPROPERTY(EditAnywhere, Category = Property, meta = (EditCondition = "bUsePhysicsStop"))
	FT4EntityCharacterReactionPhysicsStopData PhysicsStopData;

	UPROPERTY(EditAnywhere, Category = Property)
	bool bUseAnimation;

	UPROPERTY(EditAnywhere, Category = Property, meta = (EditCondition = "bUseAnimation"))
	FT4EntityCharacterReactionAnimationData AnimationData;
};

USTRUCT()
struct T4ASSET_API FT4EntityCharacterReactionSetData
{
	GENERATED_USTRUCT_BODY()

public:
	FT4EntityCharacterReactionSetData()
	{
	}

	UPROPERTY(EditAnywhere)
	TMap<FName, FT4EntityCharacterReactionData> ReactionMap;
};

// #74
USTRUCT()
struct T4ASSET_API FT4EntityCharacterEditorTransientData
{
	GENERATED_USTRUCT_BODY()

public:
	FT4EntityCharacterEditorTransientData()
	{
		Reset();
	}

	void Reset()
	{
#if WITH_EDITOR
		// #80
		TransientFullbodyOverrideMaterialSlotName = NAME_None;
		// ~#80

		TransientCompositePartName = NAME_None;

		// #76
		TransientReactionName = NAME_None; 
		TransientReactionType = ET4EntityReactionType::None;
		TransientReactionMaxPlayTimeSec = 0.0f;
		bTransientReactionPhysicsStartUsed = false;
		TransientReactionPhysicsStartData = FT4EntityCharacterReactionPhysicsStartData();
		bTransientReactionPhysicsStopUsed = false;
		TransientReactionPhysicsStopData = FT4EntityCharacterReactionPhysicsStopData();
		bTransientReactionAnimationUsed = false;
		TransientReactionAnimationData = FT4EntityCharacterReactionAnimationData();
		TransientReactionTestShotDirection = FVector::UpVector;
		// ~#76

		TransientStanceName = NAME_None; // #73
		TransientStanceActiveLayerTag = NAME_None; // #73, #74
#endif
	}

	// #80
	UPROPERTY(VisibleAnywhere, Transient, meta = (DisplayName = "Slot Name"))
	FName TransientFullbodyOverrideMaterialSlotName;

	UPROPERTY(EditAnywhere, Transient, meta = (DisplayName = "Material Asset"))
	TSoftObjectPtr<UMaterialInterface> TransientFullbodyOverrideMaterialAsset;
	// ~#80


	UPROPERTY(EditAnywhere, Transient)
	FName TransientCompositePartName;


	UPROPERTY(EditAnywhere, Transient)
	TSoftObjectPtr<UT4CostumeEntityAsset> TransientCompositePartAsset;

	// HandleOnCharacterAddSelectedReaction
	// #76
	UPROPERTY(EditAnywhere, Transient)
	FName TransientReactionName; // #76

	UPROPERTY(EditAnywhere, Transient, meta = (DisplayName = "Reaction Type"))
	ET4EntityReactionType TransientReactionType; // #76

	UPROPERTY(EditAnywhere, Transient, meta = (DisplayName = "Max PlayTime (0 == Looping)"))
	float TransientReactionMaxPlayTimeSec; // #76

	UPROPERTY(EditAnywhere, Transient, meta = (DisplayName = "Use Physics Start"))
	bool bTransientReactionPhysicsStartUsed;

	UPROPERTY(EditAnywhere, Transient, meta = (DisplayName = "Physics Start Data", EditCondition = "bTransientReactionPhysicsStartUsed"))
	FT4EntityCharacterReactionPhysicsStartData TransientReactionPhysicsStartData;

	UPROPERTY(EditAnywhere, Transient, meta = (DisplayName = "Use Physics Stop"))
	bool bTransientReactionPhysicsStopUsed;

	UPROPERTY(EditAnywhere, Transient, meta = (DisplayName = "Physics Stop Data", EditCondition = "bTransientReactionPhysicsStopUsed"))
	FT4EntityCharacterReactionPhysicsStopData TransientReactionPhysicsStopData;

	UPROPERTY(EditAnywhere, Transient, meta = (DisplayName = "Use Animation"))
	bool bTransientReactionAnimationUsed;

	UPROPERTY(EditAnywhere, Transient, meta = (DisplayName = "Animation Data", EditCondition = "bTransientReactionAnimationUsed"))
	FT4EntityCharacterReactionAnimationData TransientReactionAnimationData;

	UPROPERTY(EditAnywhere, Transient, meta = (DisplayName = "Shot Direction"))
	FVector TransientReactionTestShotDirection;
	// ~#76


	UPROPERTY(EditAnywhere, Transient)
	FName TransientStanceName; // #73

	UPROPERTY(EditAnywhere, Transient)
	TSoftObjectPtr<UT4AnimSetAsset> TransientStanceAsset; // #73

	UPROPERTY(EditAnywhere, Transient)
	FName TransientStanceActiveLayerTag; // #73, #74
};

UCLASS(ClassGroup = Tech4Labs, Category = "Tech4Labs")
class T4ASSET_API UT4CharacterEntityAsset : public UT4EntityAsset
{
	GENERATED_UCLASS_BODY()

public:
	//~ Begin UObject interface
	virtual void Serialize(FArchive& Ar) override;
	virtual void PostLoad() override;

	virtual void GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const override;
	//~ End UObject interface

public:
	ET4EntityType GetEntityType() const override { return ET4EntityType::Character; }

#if WITH_EDITOR
	virtual USkeletalMesh* GetPrimarySkeletalMeshAsset() const override // #81
	{
		if (ET4EntityCharacterMeshType::FullBody != MeshType)
		{
			return nullptr;
		}
		if (FullBodyMeshData.SkeletalMeshAsset.IsNull())
		{
			return nullptr;
		}
		return FullBodyMeshData.SkeletalMeshAsset.LoadSynchronous();
	}

	virtual void ResetEditorTransientData() override
	{ 
		UT4EntityAsset::ResetEditorTransientData();
		EditorTransientCharacterData.Reset();
	} // #73
#endif

public:
	UPROPERTY(EditAnywhere, Category=Default, AssetRegistrySearchable)
	TSoftObjectPtr<USkeleton> SkeletonAsset; // #39

	UPROPERTY(EditAnywhere, Category = Default)
	TSoftObjectPtr<UAnimBlueprint> AnimBlueprintAsset;

	UPROPERTY(EditAnywhere, Category= Default)
	ET4EntityCharacterMeshType MeshType;

	UPROPERTY(EditAnywhere, Category=FullbodyMesh)
	FT4EntityCharacterFullBodyMeshData FullBodyMeshData;

	UPROPERTY(EditAnywhere, Category=CompositeMesh)
	FT4EntityCharacterCompositeMeshData CopmpositeMeshData; // #37

	UPROPERTY(EditAnywhere, Category=Stance)
	FT4EntityCharacterStanceSetData StanceSetData; // #73

	UPROPERTY(EditAnywhere, Category=Reaction)
	FT4EntityCharacterReactionSetData ReactionSetData; // #76

	UPROPERTY(EditAnywhere, Category= Physical)
	FT4EntityCharacterPhysicalAttribute Physical;

	UPROPERTY(EditAnywhere, Category= Rendering)
	FT4EntityCharacterRenderingAttribute Rendering;

#if WITH_EDITORONLY_DATA
	// #71 : WARN : CustomizeCharacterEntityDetails 에서 사용하는 임시 프로퍼티! (저장되지 않는다!!)
	// TODO : Transient 설정으로 Editor Dirty 가 발생함으로 다른 방법 고려 필요
	UPROPERTY(EditAnywhere, Transient)
	FT4EntityCharacterEditorTransientData EditorTransientCharacterData;
#endif
};
