// Copyright 2019-2020 SoonBo Noh. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Classes/Datatable/T4GameTableBase.h"

#include "T4GameTableMaster.generated.h"

/**
  * http://api.unrealengine.com/KOR/Gameplay/DataDriven/
 */
USTRUCT()
struct FT4GameMasterTableRow : public FT4GameTableBase
{
	GENERATED_USTRUCT_BODY()

public:
	// FT4DataTableMasterRowDetails::CustomizeDetails

	UPROPERTY(EditAnywhere, Category = Common)
	ET4GameDataType Type;

	UPROPERTY(EditAnywhere, Category = Common)
	TSoftObjectPtr<UDataTable> Table;

	UPROPERTY(Transient)
	FGuid Guid; // #118 : Master 는 필요없다.

public:
	FT4GameMasterTableRow()
		: Type(ET4GameDataType::Master)
	{
	}
};
