#pragma once
#include <SDK.h>
using namespace SDK;

#include "FortPlayerState.h"

struct FUniqueNetIdRepl;

class AFortPlayerStateAthena : public AFortPlayerState
{
public:
	DEFINE_MEMBER(uint8, AFortPlayerStateAthena, SquadId);
	DEFINE_MEMBER(uint8, AFortPlayerStateAthena, TeamIndex);

public:
	void OnRep_TeamIndex(uint8 OldVal);
	void OnRep_SquadId();

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("FortPlayerStateAthena");
	}
};