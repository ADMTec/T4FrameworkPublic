// Copyright 2019 SoonBo Noh. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "T4FrameGameplayTypes.h"
#include "T4Engine/Public/T4EngineTypes.h" // #63
#include "T4FrameEditorGameplay.generated.h"

/**
  * #60 : Only Editor
 */
enum ET4EditorGameDataType
{
	EdData_PC,
	EdData_NPC,
	EdData_Weapon,
	EdData_Costume,
	EdData_Skill,
	EdData_Effect,
};

UENUM()
enum class ET4EditorPlayRole : uint8
{
	Attacker,
	Defender,

	None UMETA(Hidden),
};

class UT4ContiAsset;
USTRUCT()
struct FT4EditorSkillDataInfo
{
	GENERATED_USTRUCT_BODY()

public:
	// #T4_ADD_SKILL_CONTENT_TAG 

	UPROPERTY(VisibleAnywhere)
	FName Name;

	UPROPERTY(VisibleAnywhere)
	ET4GameAttackType AttackType; // #63

	UPROPERTY(EditAnywhere)
	float HitDelayTimeSec;

	UPROPERTY(EditAnywhere)
	float DurationSec;

	UPROPERTY(EditAnywhere)
	float ProjectileSpeed; // #63

	UPROPERTY(EditAnywhere)
	bool bMoveable;

	UPROPERTY(VisibleAnywhere)
	FName ResultEffectDataID;

	UPROPERTY(VisibleAnywhere)
	TSoftObjectPtr<UT4ContiAsset> ContiAsset;

public:
	FT4EditorSkillDataInfo()
	{
		Reset();
	}

	void Reset()
	{
		Name = NAME_None;
		AttackType = ET4GameAttackType::Melee;
		HitDelayTimeSec = 0.0f;
		DurationSec = 0.0f;;
		ProjectileSpeed = 0.0f; // #63
		bMoveable = false;
		ResultEffectDataID = NAME_None;
	}
};

USTRUCT()
struct FT4EditorEffectDataInfo
{
	GENERATED_USTRUCT_BODY()

public:
	// #T4_ADD_EFFECT_CONTENT_TAG

	UPROPERTY(VisibleAnywhere)
	FName Name;

	UPROPERTY(VisibleAnywhere)
	ET4GameEffectType EffectType;

	UPROPERTY(EditAnywhere)
	float HitDelayTimeSec;

	UPROPERTY(EditAnywhere)
	float AreaRange;

	UPROPERTY(VisibleAnywhere)
	FName DamageEffectDataID;

	UPROPERTY(VisibleAnywhere)
	TSoftObjectPtr<UT4ContiAsset> ContiAsset;

public:
	FT4EditorEffectDataInfo()
	{
		Reset();
	}

	void Reset()
	{
		Name = NAME_None;
		EffectType = ET4GameEffectType::Direct;
		HitDelayTimeSec = 0.0f;
		AreaRange = 0.0f;
		DamageEffectDataID = NAME_None;
	}
};


#if WITH_EDITOR
enum ET4WorldTravelResult // #79
{
	TravelResult_Success,
	TravelResult_ChangeContext,

	TravelResult_Failed,
};

struct FWorldContext;
class FViewport;
class IT4EditorViewportClient
{
public:
	virtual ~IT4EditorViewportClient() {}

	virtual FViewport* GetViewport() const = 0; // #68

	virtual bool IsPreviewMode() const = 0;

	virtual void SetUpdateCameraForPlayer(bool bEnable) = 0; // #79

	virtual void SetMouseLocation(const int InX, const int InY) = 0;
	virtual bool GetMousePosition(float& InLocationX, float& InLocationY) = 0;
	virtual bool GetMousePositionToWorldRay(FVector& OutStartPosition, FVector& OutStartDirection) = 0;

	virtual void ShowMouseCursor(bool InShow) = 0;
	virtual void SetMouseCursorType(EMouseCursor::Type InMouseCursorType) = 0;

	virtual void SetInitialLocationAndRotation(const FVector& InLocation, const FRotator& InRotation) = 0; // #86
};

class T4FRAME_API IT4EditorGameData // #60
{
public:
	virtual ~IT4EditorGameData() {}

	virtual void GetNameIDList(ET4EditorGameDataType InEditorGameDataType, TArray<FName>& OutDataNameIDs) = 0;

	virtual class UT4EntityAsset* GetEntityAsset(
		ET4EditorGameDataType InEditorGameDataType,
		const FName& InDataNameID
	) = 0;

	virtual bool GetSkillDataInfo(const FName& InSkillDataNameID, FT4EditorSkillDataInfo& OutSkillData) = 0;
	virtual bool GetEffectDataInfo(const FName& InEffectDataNameID, FT4EditorEffectDataInfo& OutEffectData) = 0;

	virtual bool DoNPCSpawn(const FName& InNPCDataNameID, const FVector& InSpawnLocation) = 0; // #60 : to player
	virtual bool DoDespawnAll(bool bClearPlayerObject) = 0; // #68

	virtual bool DoEquipWeaponItem(const FName& InWeaponDataNameID, bool bInUnEquip) = 0; // #60 : to player
	virtual bool DoExchangeCostumeItem(const FName& InCostumeDataNameID) = 0; // #60 : to player
};

static const FName EditorSkillDataNameID = TEXT("EditorSkillDataNameID");
static const FName EditorEffectDataNameID = TEXT("EditorEffectDataNameID");

// #60 : 좀 더 일반화 할 것!
class UT4ContiAsset;
class T4FRAME_API IT4EditorGameplayHandler
{
public:
	virtual ~IT4EditorGameplayHandler() {}
	
	virtual bool IsSimulating() const = 0; // #102

	virtual bool IsUsedGameplaySettings() const = 0; // #104 : conti 에서만 true, world 에서는 false, 아래 옵션 사용 여부

	//{ IsUsedGameplaySettings = true
	virtual bool IsAISystemDisabled() const = 0;

	virtual bool IsSandbackAttackable() const = 0;
	virtual bool IsSandbackOneHitDie() const = 0; // #76

	virtual bool IsOverrideSkillData() const = 0; // #63
	virtual bool IsOverrideEffectData() const = 0; // #68

	virtual FName GetOverrideSkillDataNameID() const = 0;
	virtual FName GetOverrideEffectDataNameID() const = 0;
	virtual FName GetOverrideDieReactionNameID() const = 0; // #76 : TODO : 사망 리엑션 값을 테이블에서 가져와야 함!

	virtual const FT4EditorSkillDataInfo& GetOverrideSkillDataInfo() const = 0;
	virtual const FT4EditorEffectDataInfo& GetOverrideEffectDataInfo() const = 0;

	virtual const FSoftObjectPath& GetOverridePlayContiPath() const = 0;
	//}
};
#endif
