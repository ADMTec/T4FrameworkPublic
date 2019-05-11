// Copyright 2019 Tech4 Labs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Classes/Engine/DataTable.h"
#include "T4ContentTable_FO.generated.h"

/**
  * http://api.unrealengine.com/KOR/Gameplay/DataDriven/
 */
class UT4PropEntityAsset;

USTRUCT()
struct FT4ContentFOTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Attribute)
	int32 UID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Attribute)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Attribute)
	FGuid Guid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Asset)
	TSoftObjectPtr<UT4PropEntityAsset> EntityAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Asset)
	TSoftObjectPtr<UBlackboardData> BlackboardDataPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Asset)
	TSoftObjectPtr<UBehaviorTree> BehaviorTreePath;
};
