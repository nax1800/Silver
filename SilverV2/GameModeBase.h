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
	static UObject* hkSpawnDefaultPawnFor(AGameModeBase* GameMode, UObject* NewPlayer, AActor* StartSpot);
	static UClass* hkGetGameSessionClass(AGameModeBase* GameMode, __int64 a2);

	UObject* SpawnDefaultPawnAtTransform(UObject* NewPlayer, const FTransform& SpawnTransform);

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("GameModeBase");
	}
};


