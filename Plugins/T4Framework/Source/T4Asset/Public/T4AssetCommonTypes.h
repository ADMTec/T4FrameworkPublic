// Copyright 2019-2020 SoonBo Noh. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "T4AssetCommonTypes.generated.h"

/**
  * 
 */

// #102 : ref EMovieSceneBuiltInEasing
//        https://easings.net/
UENUM()
enum class ET4BuiltInEasing : uint8
{
	Linear UMETA(Grouping = Linear),

	// Sinusoidal easing
	SinIn UMETA(Grouping = Sinusoidal), 
	SinOut UMETA(Grouping = Sinusoidal), 
	SinInOut UMETA(Grouping = Sinusoidal),
	
	// Quadratic easing
	QuadIn UMETA(Grouping = Quadratic), 
	QuadOut UMETA(Grouping = Quadratic), 
	QuadInOut UMETA(Grouping = Quadratic),

	// Cubic easing
	CubicIn UMETA(Grouping = Cubic), 
	CubicOut UMETA(Grouping = Cubic), 
	CubicInOut UMETA(Grouping = Cubic),

	// Quartic easing
	QuartIn UMETA(Grouping = Quartic), 
	QuartOut UMETA(Grouping = Quartic), 
	QuartInOut UMETA(Grouping = Quartic),

	// Quintic easing
	QuintIn UMETA(Grouping = Quintic), 
	QuintOut UMETA(Grouping = Quintic), 
	QuintInOut UMETA(Grouping = Quintic),

	// Exponential easing
	ExpoIn UMETA(Grouping = Exponential), 
	ExpoOut UMETA(Grouping = Exponential), 
	ExpoInOut UMETA(Grouping = Exponential),

	// Circular easing
	CircIn UMETA(Grouping = Circular), 
	CircOut UMETA(Grouping = Circular), 
	CircInOut UMETA(Grouping = Circular),
};
