// Copyright 2019 SoonBo Noh. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "T4PacketCS.h"
#include "T4PacketCS_Command.generated.h"

/**
  *
 */
 // #T4_ADD_PACKET_TAG_CS

// ET4PacketCtoS::CmdWorldTravel
// ET4PacketCtoS::CmdChangePlayer // #11, #52

// ET4PacketCtoS::CmdPCEnter
// ET4PacketCtoS::CmdNPCEnter // #31
// ET4PacketCtoS::CmdFOEnter // #31
// ET4PacketCtoS::CmdItemEnter // #41

// ET4PacketCtoS::CmdLeave, // #68

// ET4PacketCtoS::CmdTeleport

USTRUCT()
struct FT4PacketCmdWorldTravelCS : public FT4PacketCtoS
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	FT4GameDataID WorldDataID;

public:
	FT4PacketCmdWorldTravelCS()
		: FT4PacketCtoS(ET4PacketCtoS::CmdWorldTravel)
	{
	}

	FString ToString() const override
	{
		return FString(TEXT("CS_Packet:CmdWorldTravel"));
	}
};

// #11, #52
USTRUCT()
struct FT4PacketCmdChangePlayerCS : public FT4PacketCtoS
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	FT4ObjectID NewPlayerObjectID;

public:
	FT4PacketCmdChangePlayerCS()
		: FT4PacketCtoS(ET4PacketCtoS::CmdChangePlayer)
	{
	}

	FString ToString() const override
	{
		return FString(TEXT("CS_Packet:CmdChangePlayer"));
	}
};

USTRUCT()
struct FT4PacketCmdPCEnterCS : public FT4PacketCtoS
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	FT4GameDataID PlayerDataID;

	UPROPERTY(VisibleAnywhere)
	FVector SpawnLocation;

	UPROPERTY(VisibleAnywhere)
	FRotator SpawnRotation;

	UPROPERTY(VisibleAnywhere)
	bool bSetViewTarget;

public:
	FT4PacketCmdPCEnterCS()
		: FT4PacketCtoS(ET4PacketCtoS::CmdPCEnter)
		, SpawnLocation(FVector::ZeroVector)
		, SpawnRotation(FRotator::ZeroRotator)
		, bSetViewTarget(false)
	{
	}

	FString ToString() const override
	{
		return FString(TEXT("CS_Packet:CmdPCEnter"));
	}
};

// #31
USTRUCT()
struct FT4PacketCmdNPCEnterCS : public FT4PacketCtoS
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	FT4GameDataID NPCDataID;

	UPROPERTY(VisibleAnywhere)
	FVector SpawnLocation;

	UPROPERTY(VisibleAnywhere)
	FRotator SpawnRotation;

public:
	FT4PacketCmdNPCEnterCS()
		: FT4PacketCtoS(ET4PacketCtoS::CmdNPCEnter)
		, SpawnLocation(FVector::ZeroVector)
		, SpawnRotation(FRotator::ZeroRotator)
	{
	}

	FString ToString() const override
	{
		return FString(TEXT("CS_Packet:CmdNPCEnter"));
	}
};

// #31
USTRUCT()
struct FT4PacketCmdFOEnterCS : public FT4PacketCtoS
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	FT4GameDataID FODataID;

	UPROPERTY(VisibleAnywhere)
	FVector SpawnLocation;

	UPROPERTY(VisibleAnywhere)
	FRotator SpawnRotation;

public:
	FT4PacketCmdFOEnterCS()
		: FT4PacketCtoS(ET4PacketCtoS::CmdFOEnter)
		, SpawnLocation(FVector::ZeroVector)
		, SpawnRotation(FRotator::ZeroRotator)
	{
	}

	FString ToString() const override
	{
		return FString(TEXT("CS_Packet:CmdFOEnter"));
	}
};

// #41
USTRUCT()
struct FT4PacketCmdItemEnterCS : public FT4PacketCtoS
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	FT4GameDataID ItemDataID;

	UPROPERTY(VisibleAnywhere)
	FVector SpawnLocation;

	UPROPERTY(VisibleAnywhere)
	FRotator SpawnRotation;

public:
	FT4PacketCmdItemEnterCS()
		: FT4PacketCtoS(ET4PacketCtoS::CmdItemEnter)
		, SpawnLocation(FVector::ZeroVector)
		, SpawnRotation(FRotator::ZeroRotator)
	{
	}

	FString ToString() const override
	{
		return FString(TEXT("CS_Packet:CmdItemEnter"));
	}
};

// #68
USTRUCT()
struct FT4PacketCmdLeaveCS : public FT4PacketCtoS
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	FT4ObjectID LeaveObjectID;

public:
	FT4PacketCmdLeaveCS()
		: FT4PacketCtoS(ET4PacketCtoS::CmdLeave)
	{
	}

	bool Validate(FString& OutMsg) override
	{
		if (!LeaveObjectID.IsValid())
		{
			OutMsg = TEXT("Invalid Leave ObjectID!");
			return false;
		}
		return true;
	}

	FString ToString() const override
	{
		return FString(TEXT("CS_Packet:CmdLeave"));
	}
};

USTRUCT()
struct FT4PacketCmdTeleportCS : public FT4PacketCtoS
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	FT4ObjectID SenderID;

	UPROPERTY(VisibleAnywhere)
	FVector TargetLocation;

public:
	FT4PacketCmdTeleportCS()
		: FT4PacketCtoS(ET4PacketCtoS::CmdTeleport)
		, TargetLocation(FVector::ZeroVector)
	{
	}

	bool Validate(FString& OutMsg) override
	{
		if (!SenderID.IsValid())
		{
			OutMsg = TEXT("Invalid Send ObjectID!");
			return false;
		}
		if (TargetLocation.IsNearlyZero())
		{
			OutMsg = TEXT("Invalid TargetLocation!");
			return false;
		}
		return true;
	}

	FString ToString() const override
	{
		return FString(TEXT("CS_Packet:CmdTeleport"));
	}
};