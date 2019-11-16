// Copyright 2019 SoonBo Noh. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Public/T4EngineTypes.h"
#include "Public/T4EngineLayer.h"
#include "Public/T4EngineStructs.h"
#include "Public/Action/T4ActionKey.h"

#include "T4Asset/Public/Action/T4ActionTypes.h"
#include "T4Asset/Public/Entity/T4EntityKey.h"

#include "Components/SceneComponent.h"
#include "CollisionQueryParams.h"

/**
  * http://api.unrealengine.com/KOR/Gameplay/Networking/Travelling/
 */
class IT4GameWorld;
class IT4GameObject;

struct FT4BaseAction;
struct FT4StopAction;
struct FT4SpawnObjectAction;
struct FT4ActionParameters; // #28

struct FT4PacketCtoS;
struct FT4PacketStoC;

class UT4EntityAsset;

struct FWorldContext;
class UAnimSequence;
class AController;
class APlayerController; // #42

class T4ENGINE_API IT4AnimState
{
public:
	virtual ~IT4AnimState() {}

	virtual FName GetName() const = 0;
	virtual ET4AnimStatePriority GetPriority() const = 0;

	virtual void OnEnter() = 0;
	virtual void OnUpdate(float InDeltaTime) = 0;
	virtual void OnLeave() = 0;
};

class T4ENGINE_API IT4AnimControl
{
public:
	virtual ~IT4AnimControl() {}

	// #47
	virtual const IT4AnimState* GetActiveAnimState() const = 0;
	virtual const IT4AnimState* GetPendingAnimState() const = 0;

	virtual bool TryChangeAnimState(
		const FName& InAnimStateName,
		bool bInCheckPriorityActiveState,
		bool bInCheckPriorityPendingActiveState
	) = 0;

	virtual void RegisterAnimState(const FName& InAnimStateName, IT4AnimState* InAnimState) = 0;
	virtual void UnregisterAnimState(const FName& InAnimStateName) = 0;
	// ~#47

	virtual bool IsValidSection(const FName& InAnimMontageName, const FName& InSectionName) = 0;
	virtual float GetDurationSec(const FName& InAnimMontageName, const FName& InSectionName) = 0;

	virtual bool IsPlayingAnimation(FT4AnimInstanceID InPlayInstanceID) = 0;
	virtual bool IsPlayingAndBlendOutStarted(FT4AnimInstanceID InPlayInstanceID) = 0; // #44

	virtual FT4AnimInstanceID PlayAnimation(const FT4AnimParameters& InAnimParameters) = 0; // #38

	virtual bool StopAnimation(const FName& InAnimMontageName, float InBlendOutTimeSec) = 0; // #38
	virtual bool StopAnimation(FT4AnimInstanceID InPlayInstanceID, float InBlendOutTimeSec) = 0; // #47

	virtual void PauseAnimation(FT4AnimInstanceID InPlayInstanceID, bool bPause) = 0; // #54

#if WITH_EDITOR
	virtual bool EditorPlayAnimation(
		UAnimSequence* InPlayAnimSequence,
		float InPlayRate = 1.0f,
		float InBlendInTimeSec = T4AnimSetBlendTimeSec,
		float InBlendOutTimeSec = T4AnimSetBlendTimeSec
	) = 0;
#endif
};

class T4ENGINE_API IT4ActionNode // #23
{
public:
	virtual ~IT4ActionNode() {}

	virtual bool IsPlaying() const = 0;
	virtual bool IsLooping() const = 0;
	virtual bool IsPaused() const = 0; // #56

	virtual IT4ActionNode* GetParentNode() const = 0;
	virtual const FName GetActionPoint() const = 0; // #63

	virtual IT4ActionNode* AddChildNode(const FT4BaseAction* InAction, float InOffsetTimeSec) = 0; // #23, #54
	virtual bool RemoveChildNode(const FT4StopAction* InAction) = 0;

	virtual uint32 NumChildActions() const = 0;
};

class T4ENGINE_API IT4ActionControl // #23
{
public:
	virtual ~IT4ActionControl() {}

	virtual bool IsPlaying(const FT4ActionKey& InActionKey) const = 0;
	virtual bool IsLooping(const FT4ActionKey& InActionKey) const = 0;
	virtual bool IsPaused(const FT4ActionKey& InActionKey) const = 0; // #54

	virtual void SetPaused(const FT4ActionKey& InActionKey, bool bPause) = 0; // #54
	virtual void SetPaused(bool bPause) = 0; // #63

	virtual IT4ActionNode* GetChildNodeByPrimary(const FT4ActionKey& InPrimaryActionKey) const = 0;
	virtual bool GetChildNodes(const FT4ActionKey& InSameActionKey, TArray<IT4ActionNode*>& OutNodes) const = 0;

	virtual uint32 NumChildActions() const = 0;
	virtual uint32 NumChildActions(const FT4ActionKey& InActionKey) const = 0; // #54
};

// #34, #63
class T4ENGINE_API IT4GameplayControl
{
public:
	virtual ~IT4GameplayControl() {}

	virtual ET4LayerType GetLayerType() const = 0;

#if (WITH_EDITOR || WITH_SERVER_CODE)
	virtual void OnNotifyAIEvent(const FName& InEventName) = 0; // #63
#endif

	virtual bool SetGameObject(const FT4ObjectID& InNewTargetID) = 0;
	virtual void ClearGameObject(bool bInSetDefaultPawn) = 0;

	virtual bool HasGameObject() const = 0;
	virtual const FT4ObjectID& GetGameObjectID() const = 0;
	virtual IT4GameObject* GetGameObject() const = 0;

	virtual bool HasObserverObject() const = 0; // #52
	virtual bool SetObserverObject(const FT4ObjectID& InNewObserverID) = 0; // #52
	virtual void ClearObserverObject() = 0; // #52

	virtual IT4GameWorld* GetGameWorld() const = 0; // #52

	virtual bool HasPlayingPublicAction(const FT4ActionKey& InActionKey) const = 0; // #20

	virtual AController* GetAController() = 0;
	virtual class IT4GameplayController* GetGameplayController() = 0; // #63 : T4Engine 에서 호출 금지!!! (WARNING)
};

class T4ENGINE_API IT4GameObject
{
public:
	virtual ~IT4GameObject() {}

	virtual ET4LayerType GetLayerType() const = 0;
	virtual ET4ObjectType GetObjectType() const = 0;

	virtual const FT4ObjectID& GetObjectID() const = 0;

	virtual const FName& GetName() const = 0;

	virtual const FT4EntityKey& GetEntityKey() const = 0; // #35
	virtual const UT4EntityAsset* GetEntityAsset() = 0; // #39

	virtual const FName GetStanceName() const = 0; // #73
	virtual const FName& GetGameDataIDName() const = 0;

	virtual bool IsLoaded() const = 0; // #57 : 모든 로딩이 완료 된 상태
	virtual bool IsPlayer() const = 0;

	virtual APawn* GetPawn() = 0;

	// #76 : Only Public Action, Playback used
	virtual bool DoExecuteAction(const FT4BaseAction* InAction, const FT4ActionParameters* InParam = nullptr) = 0;

	// #34 : for Server All or Client Only Player
	virtual IT4GameplayControl* GetGameplayControl() = 0; // #34, #42, #36
	virtual void SetGameplayControl(IT4GameplayControl* InControl) = 0; // #34, #42, #36

	virtual IT4AnimControl* GetAnimControl() const = 0; // #14
	virtual IT4ActionControl* GetActionControl() = 0; // #20, #76 : Action Public Manager
	virtual const FT4GameObjectProperty& GetPropertyConst() const = 0; // #34

#if (WITH_EDITOR || WITH_SERVER_CODE)
	virtual FT4ServerGameObjectAttribute& GetServerAttribute() = 0; // #46 : TODO : Gameplay 테이블에서 읽어서 채울 것!
	virtual FT4ServerGameObjectDelegates& GetServerDelegates() = 0; // #49

	virtual bool IsWeaponHitOverlapEventEnabled() const = 0; // #49
	virtual void BeginWeaponHitOverlapEvent(const FName& InHitOverlapEventName) = 0; // $49
	virtual void EndWeaponHitOverlapEvent() = 0; // #49
#endif

	virtual bool IsLockOn() const = 0; // #33
	virtual bool IsFalling() const = 0;
	virtual bool IsFlying() const = 0;
	virtual bool IsRolling() const = 0; // #46
	virtual bool IsTurning() const = 0; // #46

	virtual bool HasPlayingAnimState(const FName& InAnimStateName) const = 0; // #47
	virtual bool HasPlayingPublicAction(const FT4ActionKey& InActionKey) const = 0; // #76 : Action Public Manager

	virtual const FVector GetCOMLocation() const = 0; // #18 : WARN : Center of mass 캐릭터의 경우 Coll Capsule 의 중점이다.
	virtual const FVector GetRootLocation() const = 0;
	virtual const FVector GetNavPoint() const = 0; // #52

	virtual const FRotator GetRotation() const = 0;
	virtual const FVector GetFrontVector() const = 0; // #38
	virtual const FVector GetRightVector() const = 0; // #38

	virtual const FVector GetMovementVelocity() const = 0;
	virtual const float GetMovementSpeed() const = 0;

	virtual const float GetOpacity() const = 0; // #78

	virtual bool HasReaction(const FName& InReactionName) const = 0; // #73
	virtual bool HasLayerTag(const FName& InLayerTagName, ET4LayerTagType InLayerTagType) const = 0; // #81
	virtual bool HasActionPoint(const FName& InActionPoint) const = 0; // #57 : ActionPoint = Socket or Bone or VirtualBone

	virtual bool GetSocketLocation(const FName& InSocketName, FVector& OutLocation) const = 0; // #18
	virtual bool GetSocketRotation(const FName& InSocketName, ERelativeTransformSpace InTransformSpace, FRotator& OutRotation) const = 0; // #18
	virtual bool GetSocketScale(const FName& InSocketName, ERelativeTransformSpace InTransformSpace, FVector& OutScale) const = 0; // #54

	virtual void SetHeightOffset(float InOffset) = 0; // #18

#if !UE_BUILD_SHIPPING
	virtual FT4GameObjectDebugInfo& GetDebugInfo() = 0; // #76
#endif
};

class T4ENGINE_API IT4ActionPlaybackPlayer // #68
{
public:
	virtual ~IT4ActionPlaybackPlayer() {}

	virtual bool IsPaused() const = 0;
	virtual void SetPause(bool bPause) = 0;

	virtual const TCHAR* GetPlayFile() const = 0;

	virtual float GetPlayTimeSec() const = 0;
	virtual float GetMaxPlayTimeSec() const = 0;
};

class T4ENGINE_API IT4ActionPlaybackRecorder // #68
{
public:
	virtual ~IT4ActionPlaybackRecorder() {}

	virtual bool IsRecording() const = 0;

	virtual const TCHAR* GetRecFile() const = 0;

	virtual float GetRecTimeSec() const = 0;

	virtual bool RecWorldAction(const FT4BaseAction* InAction, const FT4ActionParameters* InActionParam) = 0;
	virtual bool RecObjectAction(
		const FT4ObjectID& InObjectID,
		const FT4BaseAction* InAction,
		const FT4ActionParameters* InActionParam
	) = 0;
};

class T4ENGINE_API IT4ActionPlaybackController // #68
{
public:
	virtual ~IT4ActionPlaybackController() {}

	virtual bool IsPlaying() const = 0;
	virtual bool IsRecording() const = 0;

	virtual IT4ActionPlaybackPlayer* GetPlayer() const = 0;
	virtual IT4ActionPlaybackRecorder* GetRecorder() const = 0;

	virtual bool DoPlay(const FSoftObjectPath& InPlayPath) = 0;
	virtual bool DoPlay(const FString& InPlayAssetName, const FString& InFolderName) = 0; // /Tech4Labs/Editor/ActionPlayback/<InFolderName>/<InPlayAssetName>.uasset
	virtual void DoStopPlaying() = 0;

	virtual bool IsPlayRepeat() const = 0;
	virtual void SetPlayRepeat(bool bEnable) = 0;

	virtual bool IsPlayerPossessed() const = 0;
	virtual void SetPlayerPossessed(bool bPossess) = 0;

	virtual bool DoRec(const FSoftObjectPath& InRecPath) = 0;
	virtual bool DoRec(const FString& InRecAssetName, const FString& InFolderName) = 0; // /Tech4Labs/Editor/ActionPlayback/<InFolderName>/<InRecAssetName>.uasset
	virtual void DoStopRecording() = 0;
};

class T4ENGINE_API IT4WorldContainer // #87
{
public:
	virtual ~IT4WorldContainer() {}

	virtual uint32 GetNumGameObjects() const = 0;
	virtual bool GetGameObjects(ET4SpawnMode InSpawnType, TArray<IT4GameObject*>& OutGameObjects) = 0; // #68

	virtual bool HasGameObject(const FT4ObjectID& InObjectID) const = 0;;
	virtual IT4GameObject* FindGameObject(const FT4ObjectID& InObjectID) const = 0;

	virtual bool QueryNearestGameObjects(
		const FVector& InOriginLocation,
		const float InMaxDistance,
		TArray<IT4GameObject*>& OutObjects
	) = 0; // #34

	// #54 : 현재는 ClientOnly
	virtual IT4GameObject* PlayClientObject(
		ET4ObjectType InWorldObjectType,
		const FName& InName,
		const FVector& InLocation,
		const FRotator& InRotation,
		const FVector& InScale
	) = 0; // #68 : 소멸 조건이 되면 스스로 소멸한다.

	virtual IT4GameObject* CreateClientObject(
		ET4ObjectType InWorldObjectType, // #63 : Only World Object
		const FName& InName,
		const FVector& InLocation,
		const FRotator& InRotation,
		const FVector& InScale
	) = 0;
	virtual bool DestroyClientObject(const FT4ObjectID& InObjectID) = 0;
	// ~#54 : 현재는 ClientOnly
};

class T4ENGINE_API IT4WorldCollision // #87
{
public:
	virtual ~IT4WorldCollision() {}

	virtual bool QueryLineTraceSingle(
		ET4CollisionChannel InCollisionChannel,
		const FVector& InStartLocation,
		const FVector& InEndLocation,
		const FCollisionQueryParams& InCollisionQueryParams,
		FT4HitSingleResult& OutHitResult
	) = 0;

	virtual bool QueryLineTraceSingle(
		ET4CollisionChannel InCollisionChannel,
		const FVector& InStartLocation,
		const FVector& InStartDirection,
		const float InMaxDistance,
		const FCollisionQueryParams& InCollisionQueryParams,
		FT4HitSingleResult& OutHitResult
	) = 0;
};

class T4ENGINE_API IT4WorldNavigation // #87
{
public:
	virtual ~IT4WorldNavigation() {}

	virtual bool ProjectPoint(const FVector& InGoal, const FVector& InExtent, FVector& OutLocation) = 0; // #31 // INVALID_NAVEXTENT, FVector::ZeroVector

	virtual bool HasReached(const FVector& InStartLocation, const FVector& InEndLocation) = 0; // #52

	virtual bool GetRandomLocation(FVector& OutLocation) = 0; // #87
	virtual bool GetRandomLocation(const FVector& InOrigin, float InMaxRadius, FVector& OutLocation) = 0; // #31
};

class T4ENGINE_API IT4WorldController // #87
{
public:
	virtual ~IT4WorldController() {}

	virtual ET4GameWorldType GetGameWorldType() const = 0; // #87

	virtual bool CheckLevelLoadComplated() = 0; // #87

	virtual UWorld* GetWorld() const = 0;

	// #93
	virtual FName GetGameTimeTagName() const = 0;
	virtual FString GetGameTimeString() = 0;

	virtual void SetGameTimeHour(float InHour) = 0;
	virtual float GetGameTimeHour() const = 0;

	virtual void SetGameTimeScale(float InScale) = 0;
	virtual float GetGameTimeScale() const = 0;
	// ~#93

#if WITH_EDITOR
	virtual bool IsPreviewScene() const = 0; // #87
#endif
};

class T4ENGINE_API IT4GameWorld
{
public:
	virtual ~IT4GameWorld() {}

	virtual ET4LayerType GetLayerType() const = 0;
	virtual ET4WorldType GetType() const = 0;

	virtual void OnReset() = 0;

	virtual void OnProcessPre(float InDeltaTime) = 0; // #34 : OnWorldPreActorTick
	virtual void OnProcessPost(float InDeltaTime) = 0; // #34 : OnWorldPostActorTick

	virtual bool DoExecuteAction(const FT4BaseAction* InAction, const FT4ActionParameters* InActionParam = nullptr) = 0;

	virtual ET4GameWorldType GetGameWorldType() const = 0; // #87

	virtual UWorld* GetWorld() const = 0;

	virtual IT4WorldController* GetController() = 0; // #87
	virtual IT4WorldContainer* GetContainer() = 0; // #87
	virtual IT4WorldCollision* GetCollision() = 0; // #87
	virtual IT4WorldNavigation* GetNavigation() = 0; // #87

	// Client Only
	virtual FVector GetCameraLocation() const = 0;
	virtual FRotator GetCameraRotation() const = 0;

	virtual IT4GameplayControl* GetPlayerControl() = 0;
	virtual bool SetPlayerControl(IT4GameplayControl* InPlayerControl) = 0;

	virtual bool HasPlayerObject() const = 0;
	virtual bool IsPlayerObject(const FT4ObjectID& InObjectID) const = 0;
	virtual bool IsPlayerObject(IT4GameObject* InGameObject) const = 0;
	virtual IT4GameObject* GetPlayerObject() const = 0;

#if !UE_BUILD_SHIPPING
	virtual IT4ActionPlaybackPlayer* GetActionPlaybackPlayer() const = 0; // #68
	virtual IT4ActionPlaybackRecorder* GetActionPlaybackRecorder() const = 0;
	virtual IT4ActionPlaybackController* GetActionPlaybackController() = 0;
#endif

#if WITH_EDITOR
	virtual void SetDisableLevelStreaming(bool bInDisable) = 0; // #86 : World 의 UpdateStreamingState 를 제어하기 위한 옵션 처리
	virtual void SetDisableEnvironmentUpdating(bool bInDisable) = 0; // #92 : Map Environemnt Update 제어 옵션 처리
	virtual void SetDisableTimelapse(bool bInDisable) = 0; // #93 : 시간 경과 옵션 처리
#endif
};

// #87
DECLARE_MULTICAST_DELEGATE_OneParam(FT4OnGameWorldTravel, IT4GameWorld*);
DECLARE_MULTICAST_DELEGATE_TwoParams(FT4OnGameWorldTimeTransition, IT4GameWorld*, const FName); // #93
class T4ENGINE_API FT4EngineDelegates
{
public:
	static FT4OnGameWorldTravel OnGameWorldTravelPre; // #87 : 월드 이동 playback 지원
	static FT4OnGameWorldTravel OnGameWorldTravelPost; // #87 : 월드 이동 playback 지원

	static FT4OnGameWorldTimeTransition OnGameWorldTimeTransition; // #93 : 월드 TimeName 변경 알림

private:
	FT4EngineDelegates() {}
};

T4ENGINE_API IT4GameWorld* T4EngineWorldCreate(
	ET4WorldType InWorldType,
	const FT4WorldConstructionValues& InWorldConstructionValues // #87
);
T4ENGINE_API void T4EngineWorldDestroy(IT4GameWorld* InGameWorld);

T4ENGINE_API IT4GameWorld* T4EngineWorldGet(ET4LayerType InSceneWorld);
