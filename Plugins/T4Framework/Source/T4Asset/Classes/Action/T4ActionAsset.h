// Copyright 2019-2020 SoonBo Noh. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Classes/Common/T4CommonAssetStructs.h" // #100
#include "Public/Action/T4ActionDataCommands.h"
#include "T4ActionAsset.generated.h"

/**
  * #24
 */
struct FT4ActionCustomVersion
{
	enum Type
	{
		InitializeVer = 0,

		CommonPropertyNameChanged, // #102

		// -----<new versions can be added above this line>-------------------------------------------------
		VersionPlusOne,
		LatestVersion = VersionPlusOne - 1,
	};

	T4ASSET_API const static FGuid GUID;

private:
	FT4ActionCustomVersion() {}
};

// #24
USTRUCT()
struct T4ASSET_API FT4ActionHeaderInfo
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	ET4ActionType ActionType;

	UPROPERTY(VisibleAnywhere)
	int32 ActionArrayIndex;

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleAnywhere)
	FName FolderName; // #56
#endif

public:
	FT4ActionHeaderInfo()
		: ActionType(ET4ActionType::None)
		, ActionArrayIndex(INDEX_NONE)
#if WITH_EDITORONLY_DATA
		, FolderName(NAME_None) // #56
#endif
	{
	}
};

// #56
USTRUCT()
struct T4ASSET_API FT4ActionFolderInfo
{
	GENERATED_USTRUCT_BODY()

public:
#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleAnywhere)
	FName ParentFolderName; // #56 : lower win

	UPROPERTY(VisibleAnywhere)
	int32 SortOrder; // #56 : lower win
#endif

public:
	FT4ActionFolderInfo()
#if WITH_EDITOR
		: ParentFolderName(NAME_None)
		, SortOrder(TNumericLimits<int32>::Max())
#endif
	{
	}
};

// #54
USTRUCT()
struct T4ASSET_API FT4ActionCompositeData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	TMap<uint32, FT4ActionHeaderInfo> HeaderInfoMap;

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleAnywhere)
	TMap<FName, FT4ActionFolderInfo> FolderInfoMap; // #56 : value = sortorder
#endif

	// #T4_ADD_ACTION_TAG_DATA

	UPROPERTY(EditAnywhere)
	TArray<FT4BranchAction> BranchActions; // #54

	UPROPERTY(EditAnywhere)
	TArray<FT4SpecialMoveAction> SpecialMoveActions; // #54

	UPROPERTY(EditAnywhere)
	TArray<FT4AnimationAction> AnimationActions;

	UPROPERTY(EditAnywhere)
	TArray<FT4MeshAction> MeshActions; // #108

	UPROPERTY(EditAnywhere)
	TArray<FT4ParticleAction> ParticleActions;

	UPROPERTY(EditAnywhere)
	TArray<FT4DecalAction> DecalActions; // #54

	UPROPERTY(EditAnywhere)
	TArray<FT4ProjectileAction> ProjectileActions; // #63

	UPROPERTY(EditAnywhere)
	TArray<FT4ReactionAction> ReactionActions; // #76

	UPROPERTY(EditAnywhere)
	TArray<FT4PlayTagAction> PlayTagActions; // #81

	UPROPERTY(EditAnywhere)
	TArray<FT4TimeScaleAction> TimeScaleActions; // ##102

	UPROPERTY(EditAnywhere)
	TArray<FT4CameraWorkAction> CameraWorkActions; // #58

	UPROPERTY(EditAnywhere)
	TArray<FT4CameraShakeAction> CameraShakeActions; // #101

	UPROPERTY(EditAnywhere)
	TArray<FT4PostProcessAction> PostProcessActions; // #100

	UPROPERTY(EditAnywhere)
	TArray<FT4EnvironmentAction> EnvironmentActions; // #99

public:
	void Reset();

#if WITH_EDITOR
	// #24
	template <class T>
	T* AddChild()
	{
		return static_cast<T*>(NewAndAddAction(
			T::StaticActionType()
		));
	}

	template <class T>
	void CopyAction(
		const FT4ActionDataCommand* InSourceAction,
		T* InOutTargetAction
	); // #65

	FT4ActionDataCommand* NewAndAddAction(
		ET4ActionType InNewActionType
	); // #24, #65

	FT4ActionDataCommand* CloneAndAddAction(
		uint32 InSourceHeaderKey
	); // #65
#endif

	FT4ActionDataCommand* GetActionStruct(
		uint32 InActionHeaderKey
	); // #65

private:
#if WITH_EDITOR
	uint32 GetNewHeaderKey() const;
#endif
};

// #60
USTRUCT()
struct T4ASSET_API FT4ActionTestSettings
{
	GENERATED_USTRUCT_BODY()

public:
	
#if WITH_EDITORONLY_DATA
	
	// #T4_ADD_EDITOR_PLAY_TAG
	UPROPERTY(EditAnywhere, Category = Editor)
	FName MapEntitySelected; // #87

	UPROPERTY(EditAnywhere, Category = Editor)
	FName StanceSelected; // #73

	UPROPERTY(EditAnywhere, Category = Editor)
	FName SubStanceSelected; // #106

	UPROPERTY(EditAnywhere, Category = Editor)
	FName WeaponNameID; // #60

	UPROPERTY(EditAnywhere, Category = Editor)
	FName SandbagNameID; // #60

	UPROPERTY(EditAnywhere, Category = Editor)
	bool bAISystemDisabled; // #60

	UPROPERTY(EditAnywhere, Category = Editor)
	bool bSandbagRoleAttacker; // #63

	UPROPERTY(EditAnywhere, Category = Editor)
	bool bSandbagOneHitDie; // #76

	UPROPERTY(EditAnywhere, Category = Editor)
	bool bOverrideSkillData; // #63

	UPROPERTY(EditAnywhere, Category = Editor)
	bool bOverrideEffectData; // #68

	UPROPERTY(EditAnywhere, Category = Editor)
	FName SkillDataNameID; // #60

	UPROPERTY(EditAnywhere, Category = Editor)
	FName EffectDataNameID; // #60

	UPROPERTY(EditAnywhere, Category = Editor)
	FName DieReactionNameID; // #76

#endif

public:
	FT4ActionTestSettings()
#if WITH_EDITOR
		: MapEntitySelected(NAME_None) // #87
		, StanceSelected(NAME_None) // #73
		, SubStanceSelected(NAME_None) // #106
		, WeaponNameID(NAME_None) // #60
		, SandbagNameID(NAME_None) // #60
		, bAISystemDisabled(true) // #60
		, bSandbagRoleAttacker(false) // #63
		, bSandbagOneHitDie(false) // #76
		, bOverrideSkillData(false) // #63
		, bOverrideEffectData(false) // #68
		, SkillDataNameID(NAME_None) // #60
		, EffectDataNameID(NAME_None) // #60
		, DieReactionNameID(NAME_None) // #76
#endif
	{
	}
};

class UTexture2D;
class UT4EntityAsset;

UCLASS(ClassGroup = T4Framework, Category = "T4Framework")
class T4ASSET_API UT4ActionAsset : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	//~ Begin UObject interface
	void Serialize(FArchive& Ar) override;
	void PostLoad() override;
#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	void GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const override;
	//~ End UObject interface

#if WITH_EDITOR
	DECLARE_MULTICAST_DELEGATE(FT4OnPropertiesChanged);
	FT4OnPropertiesChanged& OnPropertiesChanged() { return OnPropertiesChangedDelegate; }
#endif // WITH_EDITOR

public:
	UPROPERTY(EditAnywhere)
	FT4ActionCompositeData CompositeData;

	UPROPERTY(EditAnywhere, Category = Default)
	float TotalPlayTimeSec; // #56

	UPROPERTY()
	float MaxPlayTimeSec_DEPRECATED; // #56

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = Editor, AssetRegistrySearchable)
	TSoftObjectPtr<UT4EntityAsset> PreviewEntityAsset;

	UPROPERTY(EditAnywhere, Category = Editor)
	FT4ActionTestSettings TestSettings; // #60

	UPROPERTY(EditAnywhere, Category = Editor)
	FT4EditorTestAutomationData TestAutomation; // #100

	UPROPERTY()
	UTexture2D* ThumbnailImage; // Internal: The thumbnail image
#endif

private:
#if WITH_EDITOR
	FT4OnPropertiesChanged OnPropertiesChangedDelegate;
#endif
};
