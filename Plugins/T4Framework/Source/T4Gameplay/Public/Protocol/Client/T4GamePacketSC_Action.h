// Copyright 2019-2020 SoonBo Noh. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "T4GamePacketSC.h"
#include "T4GamePacketSC_Action.generated.h"

/**
  *
 */
 // #T4_ADD_PACKET_TAG_SC

// ET4GamePacketSC::AimSet
// ET4GamePacketSC::AimClear
// ET4GamePacketSC::SkillTarget
// ET4GamePacketSC::EffectDirect
// ET4GamePacketSC::EffectArea

// #113, #116
USTRUCT()
struct FT4GamePacketSC_AimSet : public FT4GamePacketSC_Base
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	FT4ObjectID ObjectID;

	UPROPERTY(VisibleAnywhere)
	FT4GameDataID SkillDataID;

	UPROPERTY(VisibleAnywhere)
	bool bAimingStart; // #113 : 첫 호출에서만 true

	UPROPERTY(VisibleAnywhere)
	FVector TargetLocation; // #116

public:
	FT4GamePacketSC_AimSet()
		: FT4GamePacketSC_Base(ET4GamePacketSC::AimSet)
		, bAimingStart(false)
		, TargetLocation(FVector::ZeroVector) // #116
	{
	}

	bool Validate(FString& OutMsg) override
	{
		if (!ObjectID.IsValid())
		{
			OutMsg = TEXT("Invalid ObjectID");
			return false;
		}
		if (!SkillDataID.IsValid())
		{
			OutMsg = TEXT("Invalid SkillDataID!");
			return false;
		}
		if (TargetLocation.IsNearlyZero())
		{
			OutMsg = TEXT("Invalid Target Location");
			return false;
		}
		return true;
	}

	FString ToString() const override
	{
		return FString(TEXT("SC_Packet:Aim"));
	}
};

// #113, #116
USTRUCT()
struct FT4GamePacketSC_AimClear : public FT4GamePacketSC_Base
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	FT4ObjectID ObjectID;

public:
	FT4GamePacketSC_AimClear()
		: FT4GamePacketSC_Base(ET4GamePacketSC::AimClear)
	{
	}

	bool Validate(FString& OutMsg) override
	{
		if (!ObjectID.IsValid())
		{
			OutMsg = TEXT("Invalid ObjectID");
			return false;
		}
		return true;
	}

	FString ToString() const override
	{
		return FString(TEXT("SC_Packet:AimClear"));
	}
};

USTRUCT()
struct FT4GamePacketSC_SkillTarget : public FT4GamePacketSC_Base
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	FT4ObjectID ObjectID;

	UPROPERTY(VisibleAnywhere)
	FT4GameDataID SkillDataID;

	UPROPERTY(VisibleAnywhere)
	ET4GameAttackTarget TargetType; // #112

	UPROPERTY(VisibleAnywhere)
	FT4ObjectID TargetObjectID; // #63 : 타겟이 있으면 먼저 체크! 없으면 Direct 을 사용한다.

	UPROPERTY(VisibleAnywhere)
	FName TargetHitBone; // #112 : TargetActorID Valid 일 경우만, 현재는 순수 비쥬얼 용도

	UPROPERTY(VisibleAnywhere)
	FVector TargetLocationOrDirection; // #49, #68, #112

	UPROPERTY(VisibleAnywhere)
	float ProjectileDurationSec; // #63 : Range Attack 이라면 ProjectileSpeed 로 계산된 Duration 시간이 넘어온다.

public:
	FT4GamePacketSC_SkillTarget()
		: FT4GamePacketSC_Base(ET4GamePacketSC::SkillTarget)
		, TargetType(ET4GameAttackTarget::None) // #112
		, TargetHitBone(NAME_None) // #112
		, TargetLocationOrDirection(FVector::ZeroVector)
		, ProjectileDurationSec(0.0f)
	{
	}

	bool Validate(FString& OutMsg) override
	{
		if (!ObjectID.IsValid())
		{
			OutMsg = TEXT("Invalid ObjectID");
			return false;
		}
		if (!SkillDataID.IsValid())
		{
			OutMsg = TEXT("Invalid SkillDataID!");
			return false;
		}
		if (ET4GameAttackTarget::ObjectID == TargetType ||
			ET4GameAttackTarget::ObjectIDAndLocation == TargetType)
		{
			if (!TargetObjectID.IsValid())
			{
				OutMsg = TEXT("Invalid Target ObjectID");
				return false;
			}
		}
		else if (ET4GameAttackTarget::Location == TargetType)
		{
			if (TargetLocationOrDirection.IsNearlyZero())
			{
				OutMsg = TEXT("Invalid Target Location");
				return false;
			}
		}
		else if (ET4GameAttackTarget::Direction == TargetType)
		{
			if (TargetLocationOrDirection.IsNearlyZero())
			{
				OutMsg = TEXT("Invalid Target Direction");
				return false;
			}
		}
		else
		{
			OutMsg = TEXT("Invalid Target Type");
			return false;
		}
		return true;
	}

	FString ToString() const override
	{
		return FString(TEXT("SC_Packet:Attack"));
	}
};

USTRUCT()
struct FT4GamePacketSC_EffectDirect : public FT4GamePacketSC_Base
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	FT4ObjectID ObjectID;

	UPROPERTY(VisibleAnywhere)
	FT4GameDataID EffectDataID;

	UPROPERTY(VisibleAnywhere)
	FT4ObjectID AttackerObjectID;

public:
	FT4GamePacketSC_EffectDirect()
		: FT4GamePacketSC_Base(ET4GamePacketSC::EffectDirect)
	{
	}

	bool Validate(FString& OutMsg) override
	{
		if (!ObjectID.IsValid())
		{
			OutMsg = TEXT("Invalid ObjectID");
			return false;
		}
		return true;
	}

	FString ToString() const override
	{
		return FString(TEXT("SC_Packet:EffectDirect"));
	}
};

USTRUCT()
struct FT4GamePacketSC_EffectArea : public FT4GamePacketSC_Base
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	FT4GameDataID EffectDataID;

	UPROPERTY(VisibleAnywhere)
	FVector TargetLocation; // #68 : area attack

	UPROPERTY(VisibleAnywhere)
	FT4ObjectID AttackerObjectID;

public:
	FT4GamePacketSC_EffectArea()
		: FT4GamePacketSC_Base(ET4GamePacketSC::EffectArea)
		, TargetLocation(FVector::ZeroVector)
	{
	}

	bool Validate(FString& OutMsg) override
	{
		if (TargetLocation.IsNearlyZero())
		{
			OutMsg = TEXT("Invalid TargetLocation");
			return false;
		}
		return true;
	}

	FString ToString() const override
	{
		return FString(TEXT("SC_Packet:EffectArea"));
	}
};
