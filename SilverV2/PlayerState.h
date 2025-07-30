#pragma once
#include <SDK.h>
using namespace SDK;

#include "Actor.h"

#include "FortGameStateAthena.h"

class APlayerState : public AActor
{
public:
	DEFINE_MEMBER(FUniqueNetIdRepl, APlayerState, UniqueId);

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("PlayerState");
	}
};

