#pragma once
#include <SDK.h>
using namespace SDK;

#include "GameMode.h"

class AFortGameMode : public AGameMode
{
public:
	DEFINE_BOOL(AFortGameMode, bWorldIsReady);
	DEFINE_MEMBER(int, AFortGameMode, CurrentPlaylistId);
	DEFINE_MEMBER(FName, AFortGameMode, CurrentPlaylistName);

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("FortGameMode");
	}
};

