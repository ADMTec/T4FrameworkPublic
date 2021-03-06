// Copyright 2019-2020 SoonBo Noh. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "T4GameTableItemBase.h" // #48
#include "T4GameTableWeapon.generated.h"

/**
  * http://api.unrealengine.com/KOR/Gameplay/DataDriven/
 */
class UT4WeaponEntityAsset;

USTRUCT()
struct FT4GameWeaponEntityData // #108
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, Category = ClientOnly)
	TSoftObjectPtr<UT4WeaponEntityAsset> EntityAsset;

	UPROPERTY(EditAnywhere, Category = ClientOnly)
	FName OverrideEquipPoint;

public:
	FT4GameWeaponEntityData()
		: OverrideEquipPoint(NAME_None)
	{
	}
};

USTRUCT()
struct FT4GameWeaponTableRow : public FT4GameItemTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// FT4DataTableWeaponRowDetails::CustomizeDetails

	UPROPERTY(VisibleAnywhere, Category = Common)
	FGuid Guid;

	UPROPERTY(EditAnywhere, Category = Common)
	float AttackRange; // #50

	UPROPERTY(EditAnywhere, Category = Common)
	FT4GameSkillSetDataID DefaultSkillSetDataID; // #50, #106 : Key = SubStance

	UPROPERTY(EditAnywhere, Category = Common)
	FT4GameSkillSetDataID CombatSkillSetDataID; // #50, #106 : Key = SubStance

	UPROPERTY(EditAnywhere, Category = ServerOnly)
	FT4GameItemStatDataID ItemStatDataID; // #114 : 기본 Stat

	UPROPERTY(EditAnywhere, Category = ClientOnly)
	FT4GameWeaponEntityData MainEntityData;

	UPROPERTY(EditAnywhere, Category = ClientOnly)
	TArray<FT4GameWeaponEntityData> SubEntityDatas;

public:
	FT4GameWeaponTableRow()
		: AttackRange(0.0f)
	{
	}
};
