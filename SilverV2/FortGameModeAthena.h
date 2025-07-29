#pragma once
#include <SDK.h>
using namespace SDK;

#include "FortGameMode.h"

class AFortGameModeAthena : public AFortGameMode
{
public:
	DEFINE_MEMBER(float, AFortGameModeAthena, WarmupCountdownDuration);
	DEFINE_MEMBER(float, AFortGameModeAthena, WarmupEarlyCountdownDuration);
	DEFINE_MEMBER(int, AFortGameModeAthena, WarmupRequiredPlayerCount);

public:
	static UClass* StaticClass() 
	{
		return StaticClassImpl("FortGameModeAthena");
	}
};