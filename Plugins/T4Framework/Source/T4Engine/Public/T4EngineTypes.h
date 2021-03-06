// Copyright 2019-2020 SoonBo Noh. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "T4EngineMacros.h"
#include "T4EngineTypes.generated.h"

/**
  * http://api.unrealengine.com/KOR/Programming/UnrealArchitecture/Reference/Properties/
 */
typedef int32 FT4AnimInstanceID;

UENUM()
enum class ET4LayerType : uint8
{
	Server, // #15
	ServerMax,

	Client,
	ClientMax = Client + 10,

	Preview, // #30
	PreviewMax = Preview + 50,

	LevelEditor, // #17

	Max	UMETA(Hidden)
};

UENUM()
enum class ET4WorldType : uint8
{
	Null,
	Client,
	Server,

	Max	UMETA(Hidden)
};

UENUM()
enum class ET4ActorType : uint8
{
	// entity base
	Character,
	PropStatic,
	PropSkeletal,
	PropParticle,
	ItemStatic,
	ItemSkeletal,
	Zone, // #94

	// code base
	Projectile, // #63
	Indicator, // #117
	Default, // #54

	None UMETA(Hidden)
};

UENUM()
enum class ET4SpawnMode : uint8 // #54
{
	All,
	Client,
	Server,

	Playback, // #68
	Editor,

	Max	UMETA(Hidden)
};

enum ET4InputMode
{
	ThirdPersonMode,
	FirstPersonMode,
};

UENUM()
enum class ET4WorldSource : uint8 // #87
{
	Game,

	Preview, // Only Editor
	LevelEditor,

	None,
};

UENUM()
enum class ET4CameraType : uint8
{
	TPS,
	ShoulderView, // #40
	FPS, // #121

	Editor 	UMETA(Hidden),
	None 	UMETA(Hidden),
};

UENUM()
enum class ET4MoveMode : uint8
{
	Sync,
	Async,

	Current, // #52
	Count,
};

UENUM()
enum class ET4CollisionChannel : uint8
{
	WorldStatic,
	WorldDynamic, // #112
	SpawnObject,
	CollisionVisibility,

	Max	UMETA(Hidden)
};

UENUM()
enum class ET4AnimInstance
{
	Human_Basic, // #38
	Animal_Basic,

	Item_Basic, // #107

	None
};

enum ET4AnimationLayer // #71
{
	AnimLayer_Skill,
	AnimLayer_Overlay,
	AnimLayer_Default,
	AnimLayer_BlendSpace,

	AnimLayer_Nums
};

enum ET4AnimStatePriority
{
	AnimPriority_High,
	AnimPriority_Medium,
	AnimPriority_Low,
};

enum ET4MoveAngle // #38
{
	MoveAngle_Front,
	MoveAngle_Back,
	MoveAngle_Left,
	MoveAngle_Right,

	MoveAngle_Nums,
};

enum ET4TurnAngle // #44
{
	TurnAngle_Left,
	TurnAngle_Right,
	TurnAngle_Back,
	TurnAngle_Same,

	TurnAngle_Nums,
};

UENUM()
enum class ET4TargetType : uint8
{
	TargetLocation,
	TargetDirection,
	TargetActor,

	TargetCustom, // #40, #44

	Default, // Current
};

UENUM()
enum class ET4ZoneType : uint8 // #94
{
	Static,
	Dynamic,

	Default, // Current
};

UENUM()
enum class ET4AnimNotifyType : uint8 // #111
{
	Equipment,
	Footstep,

	None
};

UENUM()
enum class ET4EquipmentType : uint8 // #111
{
	Mount,
	Unmount,

	None
};

UENUM()
enum class ET4FootstepType : uint8 // #111
{
	FootLeftDown,
	FootLeftUp,
	FootRightDown,
	FootRightUp,

	None
};

UENUM()
enum class ET4EditorAction : uint8
{
	ReloadAttributes, // #81

	ReloadAnimSetSkill, // #81
	ReloadAnimSetOverlay, // #81
	ReloadAnimSetDefault, // #81
	ReloadAnimSetBlendSpace, // #81

	ReloadObject, // #37

	RestoreReaction, // #76
	UpdateOverrideMaterials, // #80

	PlayTagSet, // #81
	PlayTagClear, // #81

	None,
};

#if !UE_BUILD_SHIPPING
enum ET4EngineDebugFlag // #76
{
	DebugActor_Bound_Bit = (1 << 0),
};
#endif

static const uint32 T4Const_EmptyActorID = (uint32)-1;

USTRUCT()
struct FT4ActorID
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	uint32 Value;

	UPROPERTY(EditAnywhere)
	ET4SpawnMode SpawnMode; // #54

public:
	FT4ActorID()
		: Value(T4Const_EmptyActorID)
		, SpawnMode(ET4SpawnMode::All)
	{
	}

	FT4ActorID(const uint32& InValue)
		: Value(InValue)
		, SpawnMode(ET4SpawnMode::All)
	{
	}

	FT4ActorID(const uint32& InValue, const ET4SpawnMode InMode)
		: Value(InValue)
		, SpawnMode(InMode)
	{
	}

	FT4ActorID(const FT4ActorID& InValue)
		: Value(InValue.Value)
		, SpawnMode(InValue.SpawnMode)
	{
	}

	FORCEINLINE uint32 operator*() const
	{
		return Value;
	}

	FORCEINLINE FT4ActorID& operator++()
	{
		Value++;
		if (T4Const_EmptyActorID == Value)
		{
			Value = 1; // reserved 0
		}
		return *this;
	}

	FORCEINLINE FT4ActorID& operator++(int)
	{
		Value++;
		if (T4Const_EmptyActorID == Value)
		{
			Value = 1;
		}
		return *this;
	}

	FORCEINLINE bool operator==(const FT4ActorID& InRhs) const
	{
		return (Value == InRhs.Value && SpawnMode == InRhs.SpawnMode) ? true : false;
	}

	FORCEINLINE bool operator!=(const FT4ActorID& InRhs) const
	{
		return (Value != InRhs.Value || SpawnMode != InRhs.SpawnMode) ? true : false;
	}

	FORCEINLINE friend uint32 GetTypeHash(const FT4ActorID& InRhs)
	{
		return HashCombine(GetTypeHash(InRhs.Value), GetTypeHash(InRhs.SpawnMode));
	}

	FORCEINLINE bool IsValid() const
	{
		return (0 != Value && T4Const_EmptyActorID != Value) ? true : false;
	}

	FORCEINLINE void Empty()
	{
		Value = T4Const_EmptyActorID;
	}

	FORCEINLINE const TCHAR* ToModeString() const
	{
		static const TCHAR* WorldSpawneStrings[] =
		{
			TEXT("All"),
			TEXT("Client"),
			TEXT("Server"),
			TEXT("Playback"), // #68
			TEXT("Editor"),
			TEXT("Max"),
		};
		static_assert(UE_ARRAY_COUNT(WorldSpawneStrings) == (uint8)(ET4SpawnMode::Max) + 1, "SpawnMode doesn't match!");
		check(uint8(SpawnMode) < UE_ARRAY_COUNT(WorldSpawneStrings));
		return WorldSpawneStrings[uint8(SpawnMode)];
	}

	FORCEINLINE FString ToString() const
	{
		return FString::Printf(TEXT("FT4ActorID:%u=%s"), Value, ToModeString());
	}
};

static const uint32 T4Const_EmptyObjectID = (uint32)-1;

// #34, #114 : C/S GameObject
USTRUCT()
struct FT4ObjectID
{
public:
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	uint32 Value;

public:
	FT4ObjectID()
		: Value(T4Const_EmptyObjectID)
	{
	}

	FT4ObjectID(const uint32& InValue)
		: Value(InValue)
	{
	}

	FT4ObjectID(const FT4ObjectID& InValue)
		: Value(InValue.Value)
	{
	}

	FORCEINLINE uint32 operator*() const
	{
		return Value;
	}

	FORCEINLINE FT4ObjectID& operator++()
	{
		Value++;
		if (0 == Value || T4Const_EmptyObjectID == Value)
		{
			Value = 1; // reserved 0
		}
		return *this;
	}

	FORCEINLINE FT4ObjectID& operator++(int)
	{
		Value++;
		if (0 == Value || T4Const_EmptyObjectID == Value)
		{
			Value = 1;
		}
		return *this;
	}

	FORCEINLINE FT4ObjectID operator=(const FT4ObjectID& InRhs)
	{
		Value = InRhs.Value;
		return *this;
	}

	FORCEINLINE bool operator==(const FT4ObjectID& InRhs) const
	{
		return (Value == InRhs.Value) ? true : false;
	}

	FORCEINLINE bool operator!=(const FT4ObjectID& InRhs) const
	{
		return (Value != InRhs.Value) ? true : false;
	}

	FORCEINLINE friend uint32 GetTypeHash(const FT4ObjectID& InRhs)
	{
		return InRhs.Value;
	}

	FORCEINLINE void Empty()
	{
		Value = T4Const_EmptyObjectID;
	}

	FORCEINLINE bool IsValid() const
	{
		return (T4Const_EmptyObjectID != Value) ? true : false;
	}

	FORCEINLINE FString ToString() const
	{
		return FString::Printf(TEXT("FT4ObjectID '%u'"), Value);
	}
};
