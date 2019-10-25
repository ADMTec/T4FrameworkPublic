// Copyright 2019 SoonBo Noh. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/**
  * #39
 */
#if WITH_EDITOR

class UObject;
class UTexture2D;
class UBlendSpaceBase;
class UAnimSequence;
class UMaterialInterface;
struct FT4EntityOverrideMaterialData; // #81
struct FT4EntityCharacterStanceData;
struct FT4EntityCharacterReactionData; // #76
class UT4AnimSetAsset;
class UT4ContiAsset;
class UT4EntityAsset;
class UT4ItemEntityAsset;
class UT4WeaponEntityAsset;
class UT4CostumeEntityAsset;
class UT4CharacterEntityAsset;
struct FT4WorldSubLevelThumbnail; // #84
class UT4WorldAsset; // #84

namespace T4AssetTool
{
	T4ASSET_API UObject* NewAsset(
		UClass* InAssetClass,
		const FString& InAssetName,
		const FString& InPackagePath
	);

	T4ASSET_API bool IsDirtyAsset(
		UObject* InCheckObject
	); // #56

	T4ASSET_API bool SaveAsset(
		UObject* InSaveObject,
		bool bInCheckDirty
	);

	T4ASSET_API bool SaveThumbnailImage(
		UObject* InSaveObject,
		UTexture2D* InThumbnail
	);

	T4ASSET_API bool SaveThumbnailCameraInfoInEntity(
		UT4EntityAsset* InEntityAsset,
		const FRotator& ThumbnailRotation,
		const FVector& ThumbnailLocation
	);

	// #74, #81
	T4ASSET_API void EntityLayerTagSelectionByIndex(
		UT4EntityAsset* InOutEntityAsset,
		ET4LayerTagType InLayerTagType,
		const int32 InSelectIndex
	);
	T4ASSET_API bool EntityLayerTagAddOrUpdateWeaponData(
		UT4EntityAsset* InOutEntityAsset,
		const int32 InSelectIndex,
		const FName& InLayerTagName,
		const FName& InEquipPointName,
		const TSoftObjectPtr<UT4WeaponEntityAsset>& InWeaponEntityAsset,
		FString& OutErrorMessage
	);
	T4ASSET_API bool EntityLayerTagRemoveWeaponDataByIndex(
		UT4EntityAsset* InOutEntityAsset,
		int32 InRemoveArrayIndex,
		FString& OutErrorMessage
	);

	T4ASSET_API bool EntityLayerTagAddOrUpdateContiData(
		UT4EntityAsset* InOutEntityAsset,
		const int32 InSelectIndex,
		const FName& InLayerTagName,
		const TSoftObjectPtr<UT4ContiAsset>& InContiAsset,
		FString& OutErrorMessage
	);
	T4ASSET_API bool EntityLayerTagRemoveContiDataByIndex(
		UT4EntityAsset* InOutEntityAsset,
		int32 InRemoveArrayIndex,
		FString& OutErrorMessage
	);
	// ~#74, #81

	// #81
	T4ASSET_API bool EntityLayerTagAddOrUpdateMaterialData(
		UT4EntityAsset* InOutEntityAsset,
		const FName& InLayerTagName,
		FString& OutErrorMessage
	);
	T4ASSET_API bool EntityLayerTagRemoveMaterialDataByIndex(
		UT4EntityAsset* InOutEntityAsset,
		int32 InRemoveArrayIndex,
		FString& OutErrorMessage
	);

	T4ASSET_API bool EntityLayerTagGetMeterialSlots(
		UT4EntityAsset* InOutEntityAsset,
		const int32 InSelectIndex,
		const FName& InLayerTagName,
		const FName& InSlotName,
		FString& OutErrorMessage
	);
	T4ASSET_API bool EntityLayerTagClearMeterialSlots(
		UT4EntityAsset* InOutEntityAsset,
		const int32 InSelectIndex,
		const FName& InLayerTagName,
		const FName& InSlotName,
		FString& OutErrorMessage
	);
	T4ASSET_API void EntityLayerTagSelectMaterialBySlotName(
		UT4EntityAsset* InOutEntityAsset,
		const int32 InSelectIndex,
		const FName& InLayerTagName,
		const FName& InSlotName
	);
	T4ASSET_API bool EntityLayerTagUpdatMaterialBySlotName(
		UT4EntityAsset* InOutEntityAsset,
		const int32 InSelectIndex,
		const FName& InLayerTagName,
		const FName& InSlotName,
		const TSoftObjectPtr<UMaterialInterface>& InMaterialAsset,
		FString& OutErrorMessage
	);
	// ~#81

	// #80
	T4ASSET_API bool EntityCharacterGetFullbodyMeterialSlots(
		UT4CharacterEntityAsset* InOutEntityAsset,
		FString& OutErrorMessage
	);
	T4ASSET_API bool EntityCharacterClearFullbodyMeterialSlots(
		UT4CharacterEntityAsset* InOutEntityAsset,
		FString& OutErrorMessage
	);
	T4ASSET_API void EntityCharacterSelectFullbodyOverrideMaterialBySlotName(
		UT4CharacterEntityAsset* InOutEntityAsset,
		const FName& InSlotName
	);
	T4ASSET_API bool EntityCharacterUpdateFullbodyOverrideMaterialBySlotName(
		UT4CharacterEntityAsset* InOutEntityAsset,
		const FName& InSlotName,
		const TSoftObjectPtr<UMaterialInterface>& InMaterialAsset,
		FString& OutErrorMessage
	);

	T4ASSET_API bool EntityItemGetOverrideMeterialSlots(
		UT4ItemEntityAsset* InOutEntityAsset,
		FString& OutErrorMessage
	);
	T4ASSET_API bool EntityItemClearOverrideMeterialSlots(
		UT4ItemEntityAsset* InOutEntityAsset,
		FString& OutErrorMessage
	);
	T4ASSET_API void EntityItemSelectOverrideMaterialBySlotName(
		UT4ItemEntityAsset* InOutEntityAsset,
		const FName& InSlotName
	);
	T4ASSET_API bool EntityItemUpdateOverrideMaterialBySlotName(
		UT4ItemEntityAsset* InOutEntityAsset,
		const FName& InSlotName,
		const TSoftObjectPtr<UMaterialInterface>& InMaterialAsset,
		FString& OutErrorMessage
	);

	T4ASSET_API bool EntityWeaponGetOverrideMeterialSlots(
		UT4WeaponEntityAsset* InOutEntityAsset,
		FString& OutErrorMessage
	);
	T4ASSET_API bool EntityWeaponClearOverrideMeterialSlots(
		UT4WeaponEntityAsset* InOutEntityAsset,
		FString& OutErrorMessage
	);
	T4ASSET_API void EntityWeaponSelectOverrideMaterialBySlotName(
		UT4WeaponEntityAsset* InOutEntityAsset,
		const FName& InSlotName
	);
	T4ASSET_API bool EntityWeaponUpdateOverrideMaterialBySlotName(
		UT4WeaponEntityAsset* InOutEntityAsset,
		const FName& InSlotName,
		const TSoftObjectPtr<UMaterialInterface>& InMaterialAsset,
		FString& OutErrorMessage
	);

	T4ASSET_API bool EntityCostumeGetOverrideMeterialSlots(
		UT4CostumeEntityAsset* InOutEntityAsset,
		FString& OutErrorMessage
	);
	T4ASSET_API bool EntityCostumeClearOverrideMeterialSlots(
		UT4CostumeEntityAsset* InOutEntityAsset,
		FString& OutErrorMessage
	);
	T4ASSET_API void EntityCostumeSelectOverrideMaterialBySlotName(
		UT4CostumeEntityAsset* InOutEntityAsset,
		const FName& InSlotName
	);
	T4ASSET_API bool EntityCostumeUpdateOverrideMaterialBySlotName(
		UT4CostumeEntityAsset* InOutEntityAsset,
		const FName& InSlotName,
		const TSoftObjectPtr<UMaterialInterface>& InMaterialAsset,
		FString& OutErrorMessage
	);
	// ~#80

	// #71
	T4ASSET_API void EntityCharacterSelectCompositePartByPartName(
		UT4CharacterEntityAsset* InOutEntityAsset, 
		const FName& InPartName
	);
	T4ASSET_API bool EntityCharacterAddOrUpdateCompositePartByPartName(
		UT4CharacterEntityAsset* InOutEntityAsset,
		const FName& InPartName,
		const TSoftObjectPtr<UT4CostumeEntityAsset>& InCostumeEntityAsset,
		FString& OutErrorMessage
	); 
	T4ASSET_API bool EntityCharacterRemoveCompositePartByPartName(
		UT4CharacterEntityAsset* InOutEntityAsset,
		const FName& InPartName,
		FString& OutErrorMessage
	); 
	// ~#71

	// #73
	T4ASSET_API void EntityCharacterSelectStanceDataByName(
		UT4CharacterEntityAsset* InOutEntityAsset,
		const FName& InStanceName
	);
	T4ASSET_API bool EntityCharacterAddOrUpdateStanceDataByName(
		UT4CharacterEntityAsset* InOutEntityAsset,
		const FName& InStanceName,
		const FT4EntityCharacterStanceData* InStanceData,
		FString& OutErrorMessage
	);
	T4ASSET_API bool EntityCharacterRemoveStanceDataByName(
		UT4CharacterEntityAsset* InOutEntityAsset,
		const FName& InStanceName,
		FString& OutErrorMessage
	);
	// ~#73

	// #76
	T4ASSET_API void EntityCharacterSelectReactionDataByName(
		UT4CharacterEntityAsset* InOutEntityAsset,
		const FName& InReactionName
	);
	T4ASSET_API bool EntityCharacterAddOrUpdateReactionDataByName(
		UT4CharacterEntityAsset* InOutEntityAsset,
		const FName& InReactionName,
		const FT4EntityCharacterReactionData* InReactionData,
		FString& OutErrorMessage
	);
	T4ASSET_API bool EntityCharacterRemoveReactionDataByName(
		UT4CharacterEntityAsset* InOutEntityAsset,
		const FName& InReactionName,
		FString& OutErrorMessage
	);
	// ~#76

	T4ASSET_API void AnimSetSelectAnimSequenceInfoByName(
		UT4AnimSetAsset* InAnimSetAsset,
		const FName& InAnimMontageName,
		const FName& InSelectedName
	);

	T4ASSET_API void AnimSetSelectBlendSpaceInfoByName(
		UT4AnimSetAsset* InAnimSetAsset,
		const FName& InSelectedName
	);

	T4ASSET_API void AnimSetMoveUpAnimSequenceInfoByName(
		UT4AnimSetAsset* InAnimSetAsset,
		const FName& InAnimMontageName,
		const FName& InSelectedName
	);

	T4ASSET_API void AnimSetMoveUpBlendSpaceInfoByName(
		UT4AnimSetAsset* InAnimSetAsset,
		const FName& InSelectedName
	);

	T4ASSET_API void AnimSetMoveDownAnimSequenceInfoByName(
		UT4AnimSetAsset* InAnimSetAsset,
		const FName& InAnimMontageName,
		const FName& InSelectedName
	);

	T4ASSET_API void AnimSetMoveDownBlendSpaceInfoByName(
		UT4AnimSetAsset* InAnimSetAsset,
		const FName& InSelectedName
	);

	T4ASSET_API bool AnimSetAddOrUpdateAnimSeqeunceInfo(
		UT4AnimSetAsset* InAnimSetAsset,
		const FName& InAnimMontageName,
		const FName& InAnimSequenceName,
		const TSoftObjectPtr<UAnimSequence>& InAnimSequence,
		FString& OutErrorMessage
	);

	T4ASSET_API bool AnimSetRemoveAnimSeqeunceInfo(
		UT4AnimSetAsset* InAnimSetAsset,
		const FName& InAnimMontageName,
		const FName& InAnimSequenceName,
		FString& OutErrorMessage
	);

	T4ASSET_API bool AnimSetAddOrUpdateBlendSpaceInfo(
		UT4AnimSetAsset* InAnimSetAsset,
		const FName& InBlendSpaceName,
		const TSoftObjectPtr<UBlendSpaceBase>& InBlendSpace,
		FString& OutErrorMessage
	);

	T4ASSET_API bool AnimSetRemoveBlendSpaceInfoByName(
		UT4AnimSetAsset* InAnimSetAsset,
		const FName& InBlendSpaceName,
		FString& OutErrorMessage
	);

	T4ASSET_API bool AnimSetUpdateBlendSpaceInfo(
		UT4AnimSetAsset* InAnimSetAsset
	);

	T4ASSET_API bool AnimSetUpdateAll(
		UT4AnimSetAsset* InAnimSetAsset,
		FString& OutErrorMessage
	);

	T4ASSET_API bool AnimSetSaveAll(
		UT4AnimSetAsset* InAnimSetAsset,
		FString& OutErrorMessage
	); // #69

	// #84
	T4ASSET_API const FT4WorldSubLevelThumbnail* WorldGetSubLevelThumbnail(
		UT4WorldAsset* InWorldAsset,
		const FName InLevelAssetName
	); 

	T4ASSET_API bool WorldAddOrUpdateSubLevelThumbnail(
		UT4WorldAsset* InWorldAsset,
		const FName InLevelAssetName,
		FObjectThumbnail* InObjectThumbnail
	);
	// ~#84
}

#endif
