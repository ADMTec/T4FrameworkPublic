// Copyright 2019 SoonBo Noh. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "T4GameplayTypes.h"

#include "Classes/Controller/Player/T4GameplayPlayerController.h" // #42

/**
  * #48
 */
class IT4GameObject;
class IT4GameFrame;
class IT4PlayerController;
class IT4PacketHandlerCS;
class FT4GameplayModeBase;
class FT4ActionTask
{
public:
	explicit FT4ActionTask(FT4GameplayModeBase* InGameplayMode);
	virtual ~FT4ActionTask();

	void OnReset();

	void OnProcess(float InDeltaTime);

	bool OnPressed(FString& OutErrorMsg);
	void OnReleased();

	bool OnStart(const float InParam, FString& OutErrorMsg);
	bool OnEnd(const float InParam, FString& OutErrorMsg);

	bool IsPressed() const { return bPressed; }
	bool IsStarted() const { return bStarted; }
	bool IsMovementLocked() const { return bMovementLcoked; }

protected:
	virtual void Reset() {}
	virtual void Process(float InDeltaTime) {}

	virtual bool Pressed(FString& OutErrorMsg) { return false; }
	virtual void Released() {}

	virtual bool Start(const float InParam, FString& OutErrorMsg) { return false; }
	virtual bool End(const float InParam, FString& OutErrorMsg) { return false; }

	ET4GameplayGameModeType GetModeType() const;

	FT4GameplayModeBase* GetGameplayMode() const { return GameplayMode; }
	IT4GameFrame* GetGameFrame() const;
	IT4GameObject* GetPlayerObject() const;
	IT4PlayerController* GetPlayerController() const;
	IT4PacketHandlerCS* GetPacketHandlerCS() const;

protected:
	FT4GameplayModeBase* GameplayMode;
	bool bPressed;
	bool bStarted;
	bool bMovementLcoked;
};
