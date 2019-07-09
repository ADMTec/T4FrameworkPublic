// Copyright 2019 Tech4 Labs, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "T4Framework/Public/T4FrameworkNet.h" // #42
#include "T4GameplayPacketTypes.generated.h"

/**
  *
 */

// WARN : Packet 추가 시는 아래 테그를 찾아 추가된 패킷을 모두 구현해주어야 함!!
// #T4_ADD_PACKET_TAG_CS

UENUM()
enum class ET4PacketCtoS : uint32
{
	Move,
	Jump,
	Roll, // #46
	Turn, // #40

	LockOn, // #40
	LockOff, // #40

	Equip, // #22
	UnEquip, // #22

	Exchange, // #37

	Attack,

	// Test
	CmdChangeWorld,
	CmdChangePlayer, // #11, #52

	CmdPCEnter,
	CmdPCLeave,

	CmdNPCEnter, // #31
	CmdNPCLeave, // #31

	CmdFOEnter, // #31
	CmdFOLeave, // #31

	CmdItemEnter, // #41
	CmdItemLeave, // #41

	CmdTeleport,

	None,
};

// #T4_ADD_PACKET_TAG_SC
UENUM()
enum class ET4PacketStoC : uint32
{
	ChangeWorld,

	MyPCEnter,
	MyPCChange, // #11, #52

	PCEnter,
	PCLeave,

	NPCEnter, // #31
	NPCLeave, // #31

	FOEnter, // #31
	FOLeave, // #31

	ItemEnter, // #41
	ItemLeave, // #41

	MoveTo,
	JumpTo,
	RollTo, // #46
	TurnTo, // #40
	TeleportTo,

	MoveStop, // #52
	MoveSpeedSync, // #52

	LockOn, // #40
	LockOff, // #40

	Equip,
	UnEquip,

	Exchange, // #37

	Attack,
	Effect,

	None,
};