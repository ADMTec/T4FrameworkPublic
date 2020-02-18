// Copyright 2019-2020 SoonBo Noh. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "T4Engine/Public/T4EngineTypes.h"
#include "GameFramework/Pawn.h"
#include "T4GameAIDefaultPawn.generated.h"

/**
  *
 */
UCLASS()
class T4FRAMEWORK_API AT4GameAIDefaultPawn : public APawn
{
	GENERATED_UCLASS_BODY()

public:
	void Tick(float InDeltaTime) override;

	/** If true, actor is ticked even if TickType==LEVELTICK_ViewportsOnly	 */
	bool ShouldTickIfViewportsOnly() const override; // #17

	void EndPlay(const EEndPlayReason::Type InEndPlayReason) override;

protected:
	void BeginPlay() override;

protected:
	ET4LayerType LayerType;
};
