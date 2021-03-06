// Copyright 2019-2020 SoonBo Noh. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/**
  * #39
 */
#if WITH_EDITOR

class UObject;
class UTexture2D;
class UT4EntityAsset;

struct FT4EditorTestAutomationData; // #103
struct FT4EditorPointOfInterestData; // #103

namespace T4AssetUtil
{
	T4ASSET_API UObject* NewAsset(
		UClass* InAssetClass,
		const FString& InAssetName,
		const FString& InPackagePath
	);

	T4ASSET_API bool HasDirtyAsset(
		UObject* InCheckObject
	); // #56

	T4ASSET_API void SetDirtyAsset(
		UObject* InCheckObject,
		bool bDirtyFlag
	); // #56, #88

	T4ASSET_API bool SaveAsset(
		UObject* InSaveObject,
		bool bInCheckDirty
	);

	T4ASSET_API bool PointOfInterestGet(
		FT4EditorTestAutomationData* InTestAutomation,
		int32 InSelectIndex,
		FT4EditorPointOfInterestData* OutData
	); // #103

	T4ASSET_API bool PointOfInterestUpdate(
		UObject* InSaveObject,
		FT4EditorTestAutomationData* InTestAutomation,
		int32 InSelectIndex,
		FT4EditorPointOfInterestData* InUpdateData
	); // #103

	T4ASSET_API bool PointOfInterestAdd(
		UObject* InSaveObject,
		FT4EditorTestAutomationData* InTestAutomation,
		FT4EditorPointOfInterestData* InNewData
	); // #103

	T4ASSET_API bool PointOfInterestRemove(
		UObject* InSaveObject,
		FT4EditorTestAutomationData* InTestAutomation,
		int32 InRemoveIndex
	); // #103

}

// #88 : 호출 시점에 Asset 이 Dirty 가 아니라면 수정후 다시 DirtyFlag 를 돌려준다. (즉, 에디터용 수정)
class FT4ScopedTransientTransaction
{
public:
	FT4ScopedTransientTransaction(UObject* InObject)
	{
		bAlreadyDirty = T4AssetUtil::HasDirtyAsset(InObject); // #88
		OwnerObjectPtr = InObject;
	}
	~FT4ScopedTransientTransaction()
	{
		if (OwnerObjectPtr.IsValid())
		{
			if (!bAlreadyDirty)
			{
				T4AssetUtil::SetDirtyAsset(OwnerObjectPtr.Get(), bAlreadyDirty); // #88
			}
			OwnerObjectPtr.Reset();
		}
	}

private:
	bool bAlreadyDirty;
	TWeakObjectPtr<UObject> OwnerObjectPtr;
};

#endif
