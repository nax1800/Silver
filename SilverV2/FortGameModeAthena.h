#pragma once
#include <SDK.h>
using namespace SDK;

#include "FortGameMode.h"

DEFINE_LOG_CATEGORY(LogFortGameModeAthena);

class AFortPlayerController;

class AFortGameModeAthena : public AFortGameMode
{
public:
	DEFINE_MEMBER(float, AFortGameModeAthena, WarmupCountdownDuration);
	DEFINE_MEMBER(float, AFortGameModeAthena, WarmupEarlyCountdownDuration);
	DEFINE_MEMBER(int, AFortGameModeAthena, WarmupRequiredPlayerCount);

public:
	static uint8 hkPickTeam(AFortGameModeAthena* GameMode, uint8 PreferredTeam, AFortPlayerController* NewPlayer);

public:
	static UClass* StaticClass() 
	{
		return StaticClassImpl("FortGameModeAthena");
	}
};