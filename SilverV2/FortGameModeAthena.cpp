#include "FortGameModeAthena.h"

#include "FortPlayerController.h"
#include "FortGameStateAthena.h"

uint8 AFortGameModeAthena::hkPickTeam(AFortGameModeAthena* GameMode, uint8 PreferredTeam, AFortPlayerController* NewPlayer)
{
	if (!GameMode || !NewPlayer || !NewPlayer->GetPlayerState())
		return 3;

	static int TeamIndex = 0;
	static int MaxTeamSize = 0;
	static int CurrentTeamMembers = 0;

	static bool bFirstCall = true;
	if (bFirstCall)
	{
		bFirstCall = false;
		UFortPlaylistAthena* Playlist = reinterpret_cast<AFortGameStateAthena*>(GameMode->GetGameState())->GetCurrentPlaylistInfo().GetBasePlaylist();
		if (Playlist)
		{
			TeamIndex = Playlist->GetDefaultFirstTeam();
			MaxTeamSize = Playlist->GetMaxTeamSize();
		}
		else
		{
			TeamIndex = 3;
			MaxTeamSize = 1;
		}

		UE_LOG(LogFortGameModeAthena, Log, "TeamIndex: %i | MaxTeamSize: %i", TeamIndex, MaxTeamSize);
	}

	CurrentTeamMembers++;
	if (CurrentTeamMembers > MaxTeamSize)
	{
		CurrentTeamMembers = CurrentTeamMembers - MaxTeamSize;
		TeamIndex++;
	}

	return TeamIndex;
}