// Copyright 2019-2020 SoonBo Noh. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "T4ActionKey.h"
#include "Public/T4EngineTypes.h"
#include "T4Asset/Public/Action/T4ActionTypes.h"
#include "T4ActionParameters.generated.h"

/**
  * http://api.unrealengine.com/KOR/Programming/UnrealArchitecture/Reference/Properties/
 */
// #28
#define BIT_LEFTSHIFT(x) (1 << (uint32)(x)) // #30

UENUM(Meta = (Bitflags))
enum class ET4DefaultParamBits
{
	ActionKeyBit,
	ContidionNameBit, // #54
};

UENUM(Meta = (Bitflags))
enum class ET4TargetParamBits
{
	ActorIDBit,
	LocationBit,
	DirectionBit,
};

UENUM(Meta = (Bitflags))
enum class ET4OverrideParamBits // #112
{
	DurationBit,
	OffsetTimeBit, // #56

	ProjectileSpeedBit, // #63
	ProjectileDurationBit, // #63

	MaxPlayTimeBit, // #58 : 코드 호출 또는 툴에서 최대 시간 제한에 사용

	TargetBoneBit, // #112 : TargetActor 가 있을 경우 Attacker 가 선택한(또는 서버가 지정한) 연출용 HitBone 위치
	ActionPointBit, // #112 : 설정된 ActionPoint 를 Override 한다.
	ProjectileAttachTransformRuleBit, // #112 : Projectile 용 AttachTransformRuleBit 사용
	LocalOrWorldLocationBit, // #112 : 설정된 RelativeRotation 을 Override 한다. (아직 Particle Action 에는 값은 없음)
	LocalOrWorldRotationBit, // #112 : 설정된 RelativeRotation 을 Override 한다. (아직 Particle Action 에는 값은 없음)
};

UENUM(Meta = (Bitflags))
enum class ET4AnimationParamBits
{
	NoBlendInTimeWithOffsetPlayBit, // #54 : 애니 BlendIn Time 을 없앤다. (현재는 툴용)
};

USTRUCT()
struct FT4ActionDefaultParameters
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, Meta=(Bitmask, BitmaskEnum="ET4DefaultParamBits"))
	uint32 SetBits; // ET4DefaultParamBits

	UPROPERTY(EditAnywhere)
	FT4ActionKey ActionKey; // #32

	UPROPERTY(EditAnywhere)
	FName ActiveConditionName; // #54

public:
	FT4ActionDefaultParameters()
		: SetBits(0)
		, ActiveConditionName(NAME_None)
	{
	}
};

USTRUCT()
struct FT4ActionTargetParameters
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, Meta=(Bitmask, BitmaskEnum="ET4TargetParamBits"))
	uint32 SetBits; // ET4TargetParamBits

	UPROPERTY(EditAnywhere)
	FT4ActorID TargetActorID;

	UPROPERTY(EditAnywhere)
	FVector TargetLocation;

	UPROPERTY(EditAnywhere)
	FVector TargetDirection;

public:
	FT4ActionTargetParameters()
		: SetBits(0)
		, TargetLocation(FVector::ZeroVector)
		, TargetDirection(FVector::ZeroVector)
	{
	}
};

USTRUCT()
struct FT4ActionOverrideParameters // #112
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, Meta = (Bitmask, BitmaskEnum = "ET4OverrideParamBits"))
	uint32 SetBits; // ET4OverrideParamBits

	UPROPERTY(EditAnywhere)
	float DurectionSec;

	UPROPERTY(EditAnywhere)
	float OffsetTimeSec; // #56

	UPROPERTY(EditAnywhere)
	float ProjectileSpeed; // #63

	UPROPERTY(EditAnywhere)
	float ProjectileDurationSec; // #63

	UPROPERTY(EditAnywhere)
	float MaxPlayTimeSec; // #58 : 코드 호출 또는 툴에서 최대 시간 제한에 사용

	UPROPERTY(EditAnywhere)
	FName TargetBoneName; // #112 : Attacker 가 설정한 TargetActor HitBone (또는 서버에서 전달해준...)

	UPROPERTY(EditAnywhere)
	FName ActionPoint; // #112 : 설정된 ActionPoint 를 Override 한다.

	UPROPERTY(EditAnywhere)
	FVector LocalOrWorldLocation; // #112 : 설정된 RelativeRotation 을 Override 한다. (아직 Particle Action 에는 값은 없음)

	UPROPERTY(EditAnywhere)
	FRotator LocalOrWorldRotation; // #112 : 설정된 RelativeRotation 을 Override 한다. (아직 Particle Action 에는 값은 없음)

public:
	FT4ActionOverrideParameters()
		: SetBits(0)
		, DurectionSec(0.0f)
		, OffsetTimeSec(0.0f) // #56
		, ProjectileSpeed(0.0f) // #63
		, ProjectileDurationSec(0.0f) // #63
		, MaxPlayTimeSec(0.0f) // #58
		, TargetBoneName(NAME_None) // #112
		, ActionPoint(NAME_None)
		, LocalOrWorldLocation(FVector::ZeroVector)
		, LocalOrWorldRotation(FRotator::ZeroRotator)
	{
	}
};

USTRUCT()
struct FT4ActionAnimationParameters
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, Meta=(Bitmask, BitmaskEnum="ET4AnimationParamBits"))
	uint32 SetBits; // ET4AnimationParamBits

public:
	FT4ActionAnimationParameters()
		: SetBits(0)
	{
	}
};

USTRUCT()
struct FT4EditorParameters
{
	GENERATED_USTRUCT_BODY()

public:
#if WITH_EDITOR
	bool bDebugPlay; // #58 : 테스트 옵션 활성!

	TSet<uint32> InvisibleActionSet; // #56 : Action Editor 에서 Invisible or Isolate 로 출력을 제어한다.
	TSet<uint32> IsolationActionSet; // #56 : Action Editor 에서 Invisible or Isolate 로 출력을 제어한다.
#endif

public:
	FT4EditorParameters()
#if WITH_EDITOR
		: bDebugPlay(false) // #58 : 테스트 옵션 활성!
#endif
	{
	}
};

class IT4WorldActor;

USTRUCT()
struct FT4ActionParameters
{
	GENERATED_USTRUCT_BODY()

public:
	bool bDirty; // #68

	UPROPERTY(Transient)
	FT4EditorParameters EditorParams; // #56 : Only Editor, Action Editor 에서 Invisible or Isolate 로 출력을 제어할 때 더미용으로 사용(delay, duration 동작 보장)

private:
	UPROPERTY(EditAnywhere)
	FT4ActionDefaultParameters DefaultParams;

	UPROPERTY(EditAnywhere)
	FT4ActionTargetParameters TargetParams;

	UPROPERTY(EditAnywhere)
	FT4ActionOverrideParameters OverrideParams; // #116

	UPROPERTY(EditAnywhere)
	FT4ActionAnimationParameters AnimationParams; // #54

public:
	FT4ActionParameters()
		: bDirty(false)
	{
	}

	FT4ActionParameters(const FT4ActionParameters& InParameters)
	{
		*this = InParameters;
	}

	FORCEINLINE const FT4ActionDefaultParameters& GetDefaultParams() const
	{
		return DefaultParams;
	}

	FORCEINLINE const FT4ActionTargetParameters& GetTargetParams() const
	{
		return TargetParams;
	}

	FORCEINLINE const FT4ActionOverrideParameters& GetOverrideParams() const // #112
	{
		return OverrideParams;
	}

	FORCEINLINE const FT4ActionAnimationParameters& GetAnimationParams() const
	{
		return AnimationParams;
	}

	FORCEINLINE bool CheckBits(ET4DefaultParamBits InCheckBit) const
	{
		return (DefaultParams.SetBits & BIT_LEFTSHIFT(InCheckBit)) ? true : false;
	}

	FORCEINLINE bool CheckBits(ET4TargetParamBits InCheckBit) const
	{
		return (TargetParams.SetBits & BIT_LEFTSHIFT(InCheckBit)) ? true : false;
	}

	FORCEINLINE bool CheckBits(ET4OverrideParamBits InCheckBit) const // #112
	{
		return (OverrideParams.SetBits & BIT_LEFTSHIFT(InCheckBit)) ? true : false;
	}

	FORCEINLINE bool CheckBits(ET4AnimationParamBits InCheckBit) const
	{
		return (AnimationParams.SetBits & BIT_LEFTSHIFT(InCheckBit)) ? true : false;
	}

	FORCEINLINE void SetActionKey(const FT4ActionKey& InActionKey)
	{
		DefaultParams.ActionKey = InActionKey;
		DefaultParams.SetBits |= BIT_LEFTSHIFT(ET4DefaultParamBits::ActionKeyBit);
		bDirty = true; // #68
	}

	FORCEINLINE void SetConditionName(const FName& InConditionName)
	{
		DefaultParams.ActiveConditionName = InConditionName;
		DefaultParams.SetBits |= BIT_LEFTSHIFT(ET4DefaultParamBits::ContidionNameBit);
		bDirty = true; // #68
	}

	FORCEINLINE void SetTargetActorID(const FT4ActorID& InTargetActorID)
	{
		TargetParams.TargetActorID = InTargetActorID;
		TargetParams.SetBits |= BIT_LEFTSHIFT(ET4TargetParamBits::ActorIDBit);
		bDirty = true; // #68
	}

	FORCEINLINE void SetTargetLocation(const FVector& InTargetLocation)
	{
		TargetParams.TargetLocation = InTargetLocation;
		TargetParams.SetBits |= BIT_LEFTSHIFT(ET4TargetParamBits::LocationBit);
		bDirty = true; // #68
	}

	FORCEINLINE void SetTargetDirection(const FVector& InTargetDirection)
	{
		TargetParams.TargetDirection = InTargetDirection;
		TargetParams.SetBits |= BIT_LEFTSHIFT(ET4TargetParamBits::DirectionBit);
		bDirty = true; // #68
	}

	FORCEINLINE void SetOverrideDurationSec(float InDurationSec)
	{
		OverrideParams.DurectionSec = InDurationSec;
		OverrideParams.SetBits |= BIT_LEFTSHIFT(ET4OverrideParamBits::DurationBit);
		bDirty = true; // #68
	}

	FORCEINLINE void SetOverrideOffsetTimeSec(float InOffsetTimeSec)
	{
		OverrideParams.OffsetTimeSec = InOffsetTimeSec;
		OverrideParams.SetBits |= BIT_LEFTSHIFT(ET4OverrideParamBits::OffsetTimeBit); // #56
		bDirty = true; // #68
	}

	FORCEINLINE void SetOverrideProjectileSpeed(const float& InProjectileSpeed) // #63
	{
		OverrideParams.ProjectileSpeed = InProjectileSpeed;
		OverrideParams.SetBits |= BIT_LEFTSHIFT(ET4OverrideParamBits::ProjectileSpeedBit);
		bDirty = true; // #68
	}

	FORCEINLINE void SetOverrideProjectileDurationSec(const float& InProjectileDurationSec) // #63
	{
		OverrideParams.ProjectileDurationSec = InProjectileDurationSec;
		OverrideParams.SetBits |= BIT_LEFTSHIFT(ET4OverrideParamBits::ProjectileDurationBit);
		bDirty = true; // #68
	}

	FORCEINLINE void SetOverrideMaxPlayTimSec(float InOverrideMaxPlayTimSec)
	{
		// #58 : 코드 호출 또는 툴에서 최대 시간 제한에 사용
		OverrideParams.MaxPlayTimeSec = InOverrideMaxPlayTimSec;
		OverrideParams.SetBits |= BIT_LEFTSHIFT(ET4OverrideParamBits::MaxPlayTimeBit);
		bDirty = true; // #68
	}

	FORCEINLINE void SetOverrideTargetBoneName(FName InOverrideTargetBoneName) // #112
	{
		OverrideParams.TargetBoneName = InOverrideTargetBoneName;
		OverrideParams.SetBits |= BIT_LEFTSHIFT(ET4OverrideParamBits::TargetBoneBit);
		bDirty = true;
	}

	FORCEINLINE void SetOverrideActionPoint(FName InOverrideActionPoint) // #112
	{
		OverrideParams.ActionPoint = InOverrideActionPoint;
		OverrideParams.SetBits |= BIT_LEFTSHIFT(ET4OverrideParamBits::ActionPointBit);
		bDirty = true;
	}

	FORCEINLINE void SetOverrideProjectileAttachTransformRule() // #112
	{
		OverrideParams.SetBits |= BIT_LEFTSHIFT(ET4OverrideParamBits::ProjectileAttachTransformRuleBit);
		bDirty = true; // #68
	}

	FORCEINLINE void SetOverrideLocalOrWorldLocation(const FVector& InOverrideLocalOrWorldLocation) // #112
	{
		OverrideParams.LocalOrWorldLocation = InOverrideLocalOrWorldLocation;
		OverrideParams.SetBits |= BIT_LEFTSHIFT(ET4OverrideParamBits::LocalOrWorldLocationBit);
		bDirty = true;
	}

	FORCEINLINE void SetOverrideLocalOrWorldRotation(const FRotator& InOverrideLocalOrWorldRotation) // #112
	{
		OverrideParams.LocalOrWorldRotation = InOverrideLocalOrWorldRotation;
		OverrideParams.SetBits |= BIT_LEFTSHIFT(ET4OverrideParamBits::LocalOrWorldRotationBit);
		bDirty = true;
	}

	FORCEINLINE void SetAnimationNoBlendInTimeWithOffsetPlay() // #54 : 애니 BlendIn Time 을 없앤다. (현재는 툴용)
	{
		AnimationParams.SetBits |= BIT_LEFTSHIFT(ET4AnimationParamBits::NoBlendInTimeWithOffsetPlayBit);
		bDirty = true; // #68
	}

	bool T4ENGINE_API GetTargetActor(ET4LayerType InLayerType, IT4WorldActor** OutTargetActor, const TCHAR* InDebugString = nullptr) const; // #28
	bool T4ENGINE_API GetTargetLocation(FVector& OutTargetLocation, const TCHAR* InDebugString = nullptr) const; // #28
	bool T4ENGINE_API GetTargetDirection(FVector& OutTargetDirection, const TCHAR* InDebugString = nullptr) const; // #28

	static T4ENGINE_API const FT4ActionParameters DefaultActionParameter; // #32
};
