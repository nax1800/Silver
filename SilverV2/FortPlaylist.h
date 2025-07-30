#pragma once
#include <SDK.h>
using namespace SDK;

class UFortPlaylist : public UObject
{
public:
	DEFINE_MEMBER(int, UFortPlaylist, LootLevel);
	DEFINE_MEMBER(int, UFortPlaylist, MaxTeamSize);
	DEFINE_MEMBER(int, UFortPlaylist, MaxTeamCount);
	DEFINE_MEMBER(int, UFortPlaylist, MaxPlayers);
	DEFINE_MEMBER(int, UFortPlaylist, MinPlayers);
	DEFINE_MEMBER(FName, UFortPlaylist, PlaylistName);
	DEFINE_MEMBER(int, UFortPlaylist, PlaylistId);
	DEFINE_BOOL(bool, UFortPlaylist, bAllowJoinInProgress);
	DEFINE_MEMBER(uint8, UFortPlaylist, DefaultFirstTeam);

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("FortPlaylist");
	}
};

