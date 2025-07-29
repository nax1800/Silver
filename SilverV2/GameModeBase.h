#pragma once
#include <SDK.h>
using namespace SDK;

#include "GameState.h"
#include "Actor.h"

DEFINE_LOG_CATEGORY(LogGameModeBase);

class AGameModeBase : public UObject
{
public:
	DEFINE_PTR(AGameState, AGameModeBase, GameState);
	DEFINE_PTR(UObject, AGameModeBase, GameSession);

public:
	UObject* SpawnDefaultPawnAtTransform(UObject* NewPlayer, const FTransform& SpawnTransform);
	static UObject* hkSpawnDefaultPawnFor(AGameModeBase* GameMode, UObject* NewPlayer, AActor* StartSpot);

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("GameModeBase");
	}
};


