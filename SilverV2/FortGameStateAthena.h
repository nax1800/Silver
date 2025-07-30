#pragma once
#include <SDK.h>
using namespace SDK;

#include "GameState.h"

#include "FortPlaylistAthena.h"

struct FPlaylistPropertyArray
{
public:
	DEFINE_PTR(UFortPlaylistAthena, FPlaylistPropertyArray, BasePlaylist);
	DEFINE_PTR(UFortPlaylistAthena, FPlaylistPropertyArray, OverridePlaylist);
	DEFINE_MEMBER(int, FPlaylistPropertyArray, PlaylistReplicationKey);

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("PlaylistPropertyArray");
	}
};

struct FUniqueNetIdRepl
{
public:
	DEFINE_MEMBER(TArray<uint8>, FUniqueNetIdRepl, ReplicationBytes);

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("UniqueNetIdRepl");
	}
};

struct FGameMemberInfo
{
public:
	DEFINE_MEMBER(uint8, FGameMemberInfo, SquadId);
	DEFINE_MEMBER(uint8, FGameMemberInfo, TeamIndex);
	DEFINE_MEMBER(FUniqueNetIdRepl, FGameMemberInfo, MemberUniqueId);

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("GameMemberInfo");
	}
};

struct FGameMemberInfoArray
{
public:
	DEFINE_MEMBER(TArray<FGameMemberInfo>, FGameMemberInfoArray, Members);
	DEFINE_PTR(class AFortGameStateAthena, FGameMemberInfoArray, OwningGameState);

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("GameMemberInfoArray");
	}
};

class AFortGameStateAthena : public AGameState
{
public:
	DEFINE_MEMBER(FPlaylistPropertyArray, AFortGameStateAthena, CurrentPlaylistInfo);
	DEFINE_MEMBER(int, AFortGameStateAthena, CurrentPlaylistId);
	DEFINE_MEMBER(float, AFortGameStateAthena, WarmupCountdownEndTime);
	DEFINE_MEMBER(float, AFortGameStateAthena, WarmupCountdownStartTime);
	DEFINE_MEMBER(FGameMemberInfoArray, AFortGameStateAthena, GameMemberInfoArray);

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

