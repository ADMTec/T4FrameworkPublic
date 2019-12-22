// Copyright 2019 SoonBo Noh. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "T4GameplayTypes.generated.h"

/**
  * #40
 */
UENUM()
enum class ET4GameplayGameModeType : uint8
{
	TPS,
	ShoulderView, // #40

	None UMETA(Hidden),
};

enum ET4ComboAttackSeqeunce
{
	Ready, // #48
	Primary,
	Secondary,
	Tertiary,
	Finish, // #48

	Nums,
};
