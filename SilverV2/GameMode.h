#pragma once
#include <SDK.h>
using namespace SDK;

DEFINE_LOG_CATEGORY(LogGameMode);

#include "GameModeBase.h"

class AGameMode : public AGameModeBase
{
public:

public:
	static inline bool (*oReadyToStartMatch)(AGameMode*);
	static bool hkReadyToStartMatch(AGameMode* GameMode);

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("GameMode");
	}
};

