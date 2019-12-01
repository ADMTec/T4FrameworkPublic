// Copyright 2019 SoonBo Noh. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "T4ActionBase.h"
#include "Public/T4AssetDefinitions.h"
#include "Engine/Scene.h" // #100
#include "T4ActionContis.generated.h"

/**
  *
 */
 // #T4_ADD_ACTION_TAG_CONTI

// ET4ActionType::Branch // #54
// ET4ActionType::SpecialMove
// ET4ActionType::Animation
// ET4ActionType::Particle
// ET4ActionType::Decal // #52
// ET4ActionType::Projectile // #63
// ET4ActionType::Reaction // #76
// ET4ActionType::LayerSet // #81
// ET4ActionType::TimeScale // #52
// ET4ActionType::CameraWork // #52
// ET4ActionType::PostProcess // #100
// ET4ActionType::Environment // #99

class UT4ContiAsset;

USTRUCT()
struct T4ASSET_API FT4ContiBaseAction : public FT4BaseAction
{
	GENERATED_USTRUCT_BODY()

public:
	// #39 : FT4ContiDetailCustomization::CustomizeCommonActionDetails
	// #24 : Composite 일 경우 사용됨!
	// #65 : Property 추가시에는 FT4ActionCompositeData::CloneAndAddAction 에도 반영할 것! (FT4ActionCompositeData::CopyAction)
	UPROPERTY(VisibleAnywhere)
	int32 HeaderKey;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere)
	FName DisplayName;

	UPROPERTY(EditAnywhere)
	FColor DebugColorTint;
#endif

public:
	FT4ContiBaseAction()
		: FT4BaseAction()
		, HeaderKey(INDEX_NONE) // #24
#if WITH_EDITORONLY_DATA
		, DisplayName(NAME_None)
		, DebugColorTint(FColor::Black)
#endif
	{
	}

	FT4ContiBaseAction(ET4ActionType InObjectAction)
		: FT4BaseAction(InObjectAction)
		, HeaderKey(INDEX_NONE) // #24
#if WITH_EDITORONLY_DATA
		, DisplayName(NAME_None)
		, DebugColorTint(FColor::Black)
#endif
	{
	}

	virtual ~FT4ContiBaseAction() {}

	ET4BaseActionType GetBaseActionType() const override { return ET4BaseActionType::Conti; } // #52

	virtual bool Validate(FString& OutMsg)
	{
		return true;
	}

	virtual FString ToString() const
	{
		return FString(TEXT("ContiBaseAction"));
	}

	virtual FString ToDisplayText()
	{
		return FString(TEXT("Untitled")); // #54
	}
};

// #54
USTRUCT()
struct T4ASSET_API FT4BranchAction : public FT4ContiBaseAction
{
	GENERATED_USTRUCT_BODY()

public:
	// #39 : FT4ContiDetailCustomization::CustomizeBranchActionDetails
	UPROPERTY(EditAnywhere)
	ET4BranchCondition Contition;

	UPROPERTY(EditAnywhere)
	FName ConditionName;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UT4ContiAsset> ContiAsset;

	UPROPERTY(EditAnywhere)
	ET4LoadingPolicy LoadingPolicy;

public:
	FT4BranchAction()
		: FT4ContiBaseAction(StaticActionType())
		, Contition(ET4BranchCondition::Default)
		, ConditionName(NAME_None)
		, LoadingPolicy(ET4LoadingPolicy::Default)
	{
	}

	static ET4ActionType StaticActionType() { return ET4ActionType::Branch; }

	FString ToString() const override
	{
		return FString(TEXT("BranchAction"));
	}

	FString ToDisplayText() override
	{
		return FString::Printf(TEXT("Branch '%s'"), *(ContiAsset.GetAssetName())); // #54
	}
};

// #54
USTRUCT()
struct T4ASSET_API FT4SpecialMoveAction : public FT4ContiBaseAction
{
	GENERATED_USTRUCT_BODY()

public:
	// #39 : FT4ContiDetailCustomization::CustomizeSpecialMoveActionDetails

public:
	FT4SpecialMoveAction()
		: FT4ContiBaseAction(StaticActionType())
	{
	}

	static ET4ActionType StaticActionType() { return ET4ActionType::SpecialMove; }

	FString ToString() const override
	{
		return FString(TEXT("SpecialMoveAction"));
	}
};

USTRUCT()
struct T4ASSET_API FT4AnimationAction : public FT4ContiBaseAction
{
	GENERATED_USTRUCT_BODY()

public:
	// #39 : FT4ContiDetailCustomization::CustomizeAnimationActionDetails

	UPROPERTY(EditAnywhere)
	FName SectionName;

	UPROPERTY(EditAnywhere)
	float BlendInTimeSec;

	UPROPERTY(EditAnywhere)
	float BlendOutTimeSec;

	UPROPERTY(EditAnywhere)
	float PlayRate;

	UPROPERTY(EditAnywhere)
	int32 LoopCount;

public:
	FT4AnimationAction()
		: FT4ContiBaseAction(StaticActionType())
		, SectionName(NAME_None)
		, BlendInTimeSec(T4AnimSetBlendTimeSec)
		, BlendOutTimeSec(T4AnimSetBlendTimeSec)
		, PlayRate(1.0f)
		, LoopCount(1)
	{
	}

	static ET4ActionType StaticActionType() { return ET4ActionType::Animation; }

	FString ToString() const override
	{
		return FString(TEXT("AnimationAction"));
	}

	FString ToDisplayText() override
	{
		return FString::Printf(TEXT("Animation '%s'"), *(SectionName.ToString())); // #54
	}
};

class UParticleSystem;

USTRUCT()
struct T4ASSET_API FT4ParticleAction : public FT4ContiBaseAction
{
	GENERATED_USTRUCT_BODY()

public:
	// #39 : FT4ContiDetailCustomization::CustomizeParticleActionDetails
	UPROPERTY(EditAnywhere)
	ET4AttachParent AttachParent;

	UPROPERTY(EditAnywhere)
	bool bParentInheritPoint; // #76 : Parent ActionPoint 가 없다면 본래 세팅을 따르도록...

	UPROPERTY(EditAnywhere)
	FName ActionPoint; // #57

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UParticleSystem> ParticleAsset;

	UPROPERTY(EditAnywhere)
	ET4LoadingPolicy LoadingPolicy;

	UPROPERTY(EditAnywhere)
	FVector Scale; // #54

	UPROPERTY(EditAnywhere)
	float PlayRate;

public:
	FT4ParticleAction()
		: FT4ContiBaseAction(StaticActionType())
		, AttachParent(ET4AttachParent::Default) // #54
		, bParentInheritPoint(false) // #76
		, ActionPoint(T4ContiDefaultActionPontName)
		, LoadingPolicy(ET4LoadingPolicy::Default)
		, Scale(FVector::OneVector) // #54
		, PlayRate(1.0f)
	{
	}

	static ET4ActionType StaticActionType() { return ET4ActionType::Particle; }

	FString ToString() const override
	{
		return FString(TEXT("ParticleAction"));
	}

	FString ToDisplayText() override
	{
		return FString::Printf(TEXT("Particle '%s'"), *(ParticleAsset.GetAssetName())); // #54
	}
};

// #54
class UMaterialInterface;

USTRUCT()
struct T4ASSET_API FT4DecalAction : public FT4ContiBaseAction
{
	GENERATED_USTRUCT_BODY()

public:
	// #39 : FT4ContiDetailCustomization::CustomizeDecalActionDetails
	UPROPERTY(EditAnywhere)
	ET4AttachParent AttachParent;

	UPROPERTY(EditAnywhere)
	bool bParentInheritPoint; // #76 : Parent ActionPoint 가 없다면 본래 세팅을 따르도록...

	UPROPERTY(EditAnywhere)
	FName ActionPoint;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UMaterialInterface> DecalMaterial;

	UPROPERTY(EditAnywhere)
	ET4LoadingPolicy LoadingPolicy;

	UPROPERTY(EditAnywhere)
	FVector Scale; // #54

	UPROPERTY(EditAnywhere)
	int32 DecalSortOrder;

	UPROPERTY(EditAnywhere)
	FVector DecalSize;

	UPROPERTY(EditAnywhere)
	float FadeInTimeSec;

	UPROPERTY(EditAnywhere)
	float FadeOutTimeSec;

public:
	FT4DecalAction()
		: FT4ContiBaseAction(StaticActionType())
		, AttachParent(ET4AttachParent::Default)
		, bParentInheritPoint(false) // #76
		, ActionPoint(T4ContiDefaultActionPontName)
		, LoadingPolicy(ET4LoadingPolicy::Default)
		, Scale(FVector::OneVector)
		, DecalSortOrder(0)
		, DecalSize(128.0f, 256.0f, 256.0f)
		, FadeInTimeSec(0.5f)
		, FadeOutTimeSec(0.5f)
	{
	}

	static ET4ActionType StaticActionType() { return ET4ActionType::Decal; }

	FString ToString() const override
	{
		return FString(TEXT("DecalAction"));
	}

	FString ToDisplayText() override
	{
		return FString::Printf(TEXT("Decal '%s'"), *(DecalMaterial.GetAssetName())); // #54
	}
};

// #63
USTRUCT()
struct T4ASSET_API FT4ProjectileAction : public FT4ContiBaseAction
{
	GENERATED_USTRUCT_BODY()

public:
	// #39 : FT4ContiDetailCustomization::CustomizeProjectileActionDetails
	UPROPERTY(EditAnywhere)
	FName ActionPoint; // 어딘가에 붙어야 할 경우. 예) 오른손...

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UT4ContiAsset> CastingContiAsset;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UT4ContiAsset> HeadContiAsset;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UT4ContiAsset> EndContiAsset;

	UPROPERTY(EditAnywhere)
	ET4LoadingPolicy LoadingPolicy;

	UPROPERTY(EditAnywhere)
	float ThrowDelayTimeSec; // Play 이후 ActionPoint 에서 떨어지는 시간!

	UPROPERTY(EditAnywhere)
	float CastingStopDelayTimeSec; // ThrowDelayTimeSec 이후 Casting Conti 가 삭제될 시간

public:
	FT4ProjectileAction()
		: FT4ContiBaseAction(StaticActionType())
		, ActionPoint(NAME_None)
		, LoadingPolicy(ET4LoadingPolicy::Default)
		, ThrowDelayTimeSec(0.0f)
		, CastingStopDelayTimeSec(0.2f)
	{
	}

	static ET4ActionType StaticActionType() { return ET4ActionType::Projectile; }

	FString ToString() const override
	{
		return FString(TEXT("ProjectileAction"));
	}

	FString ToDisplayText() override
	{
		return FString::Printf(TEXT("Projectile '%s'"), *(HeadContiAsset.GetAssetName()));
	}
};

// #76
USTRUCT()
struct T4ASSET_API FT4ReactionAction : public FT4ContiBaseAction
{
	GENERATED_USTRUCT_BODY()

public:
	// #39 : FT4ContiDetailCustomization::CustomizeReactionActionDetails
	UPROPERTY(EditAnywhere)
	FName ReactionName;

public:
	FT4ReactionAction()
		: FT4ContiBaseAction(StaticActionType())
		, ReactionName(NAME_None)
	{
	}

	static ET4ActionType StaticActionType() { return ET4ActionType::Reaction; }

	FString ToString() const override
	{
		return FString(TEXT("ReactionAction"));
	}

	FString ToDisplayText() override
	{
		return FString::Printf(TEXT("Reaction '%s'"), *(ReactionName.ToString())); // #67
	}
};

// #81
USTRUCT()
struct T4ASSET_API FT4LayerSetAction : public FT4ContiBaseAction
{
	GENERATED_USTRUCT_BODY()

public:
	// #39 : FT4ContiDetailCustomization::CustomizeLayerSetActionDetails
	UPROPERTY(EditAnywhere)
	FName LayerTagName;

	UPROPERTY(EditAnywhere)
	ET4LayerTagType LayerTagType;

public:
	FT4LayerSetAction()
		: FT4ContiBaseAction(StaticActionType())
		, LayerTagName(NAME_None)
		, LayerTagType(ET4LayerTagType::All)
	{
	}

	static ET4ActionType StaticActionType() { return ET4ActionType::LayerSet; }

	FString ToString() const override
	{
		return FString(TEXT("LayerSetAction"));
	}

	FString ToDisplayText() override
	{
		return FString::Printf(TEXT("LayerSet '%s'"), *(LayerTagName.ToString()));
	}
};

// #54
USTRUCT()
struct T4ASSET_API FT4TimeScaleAction : public FT4ContiBaseAction
{
	GENERATED_USTRUCT_BODY()

public:
	// #39 : FT4ContiDetailCustomization::CustomizeTimeScaleActionDetails

public:
	FT4TimeScaleAction()
		: FT4ContiBaseAction(StaticActionType())
	{
	}

	static ET4ActionType StaticActionType() { return ET4ActionType::TimeScale; }

	FString ToString() const override
	{
		return FString(TEXT("TimeScaleAction"));
	}
};

// #54
USTRUCT()
struct T4ASSET_API FT4CameraWorkAction : public FT4ContiBaseAction
{
	GENERATED_USTRUCT_BODY()

public:
	// #39 : FT4ContiDetailCustomization::CustomizeDecalActionDetails

public:
	FT4CameraWorkAction()
		: FT4ContiBaseAction(StaticActionType())
	{
	}

	static ET4ActionType StaticActionType() { return ET4ActionType::CameraWork; }

	FString ToString() const override
	{
		return FString(TEXT("CameraWorkAction"));
	}
};

// #100
USTRUCT()
struct T4ASSET_API FT4PostProcessAction : public FT4ContiBaseAction
{
	GENERATED_USTRUCT_BODY()

public:
	// #39 : FT4ContiDetailCustomization::CustomizePostProcessActionDetails
	UPROPERTY(EditAnywhere)
	ET4PlayTarget PlayTarget; // #100

	UPROPERTY(EditAnywhere)
	float BlendInTimeSec;

	UPROPERTY(EditAnywhere)
	float BlendOutTimeSec;

	UPROPERTY(EditAnywhere)
	FPostProcessSettings PostProcessSettings; // #98 에서는 Zone 처리,

public:
	FT4PostProcessAction()
		: FT4ContiBaseAction(StaticActionType())
		, PlayTarget(ET4PlayTarget::Default)
		, BlendInTimeSec(1.0f)
		, BlendOutTimeSec(1.0f)
	{
	}

	static ET4ActionType StaticActionType() { return ET4ActionType::PostProcess; }

	FString ToString() const override
	{
		return FString(TEXT("PostProcessAction"));
	}

	FString ToDisplayText() override
	{
		return FString::Printf(TEXT("PostProcess"));
	}
};

// #99
class UT4ZoneEntityAsset;
USTRUCT()
struct T4ASSET_API FT4EnvironmentAction : public FT4ContiBaseAction
{
	GENERATED_USTRUCT_BODY()

public:
	// #39 : FT4ContiDetailCustomization::CustomizeEnvironmentActionDetails
	UPROPERTY(EditAnywhere)
	ET4AttachParent AttachParent;

	UPROPERTY(EditAnywhere)
	bool bParentInheritPoint; // #76 : Parent ActionPoint 가 없다면 본래 세팅을 따르도록...

	UPROPERTY(EditAnywhere)
	FName ActionPoint;

	UPROPERTY(EditAnywhere)
	ET4PlayTarget PlayTarget; // #100

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UT4ZoneEntityAsset> ZoneEntityAsset;

	UPROPERTY(EditAnywhere)
	bool bOverrideBlendTime;

	UPROPERTY(EditAnywhere)
	float OverrideBlendInTimeSec;

	UPROPERTY(EditAnywhere)
	float OverrideBlendOutTimeSec;

public:
	FT4EnvironmentAction()
		: FT4ContiBaseAction(StaticActionType())
		, AttachParent(ET4AttachParent::Default)
		, bParentInheritPoint(false) // #76
		, ActionPoint(T4ContiDefaultActionPontName)
		, PlayTarget(ET4PlayTarget::Default)
		, bOverrideBlendTime(false)
		, OverrideBlendInTimeSec(1.0f)
		, OverrideBlendOutTimeSec(1.0f)
	{
	}

	static ET4ActionType StaticActionType() { return ET4ActionType::Environment; }

	FString ToString() const override
	{
		return FString(TEXT("EnvironmentAction"));
	}

	FString ToDisplayText() override
	{
		return FString::Printf(TEXT("Environment '%s'"), *(ZoneEntityAsset.GetAssetName()));
	}
};
