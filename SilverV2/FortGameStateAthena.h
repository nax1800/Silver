#pragma once
#include <SDK.h>
using namespace SDK;

#include "GameState.h"

#include "FortPlaylistAthena.h"

struct FPlaylistPropertyArray
{
public:
	DEFINE_MEMBER(UFortPlaylistAthena*, FPlaylistPropertyArray, BasePlaylist);
	DEFINE_MEMBER(UFortPlaylistAthena*, FPlaylistPropertyArray, OverridePlaylist);
	DEFINE_MEMBER(int, FPlaylistPropertyArray, PlaylistReplicationKey);

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("PlaylistPropertyArray");
	}
};

class AFortGameStateAthena : public AGameState
{
public:
	DEFINE_MEMBER(FPlaylistPropertyArray, AFortGameStateAthena, CurrentPlaylistInfo);
	DEFINE_MEMBER(int, AFortGameStateAthena, CurrentPlaylistId);
	DEFINE_MEMBER(float, AFortGameStateAthena, WarmupCountdownEndTime);
	DEFINE_MEMBER(float, AFortGameStateAthena, WarmupCountdownStartTime);

	DEFINE_PTR(UObject, AFortGameStateAthena, MapInfo);

public:
	void OnRep_CurrentPlaylistInfo();
	void OnRep_CurrentPlaylistId();

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("FortGameStateAthena");
	}
};

