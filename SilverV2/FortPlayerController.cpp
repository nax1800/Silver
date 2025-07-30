#include "FortPlayerController.h"

#include "FortPlayerStateAthena.h"

#include "Abilities.h"

void AFortPlayerController::hkServerReadyToStartMatch(AFortPlayerController* PlayerController)
{
	UE_LOG(LogFortPlayerController, Log, "ServerReadyToStartMatch Called.");
	AFortPlayerStateAthena* Casted_PlayerState = reinterpret_cast<AFortPlayerStateAthena*>(PlayerController->GetPlayerState());

	if (Casted_PlayerState)
	{
		//Abilities::ApplyAbilities(Casted_PlayerState);

		Casted_PlayerState->SetTeamIndex(5);
		Casted_PlayerState->OnRep_TeamIndex(0);

		Casted_PlayerState->SetSquadId(Casted_PlayerState->GetTeamIndex() - 2);
		Casted_PlayerState->OnRep_PlayerTeam();
		Casted_PlayerState->OnRep_PlayerTeamPrivate();
		Casted_PlayerState->OnRep_TeamIndex(5);
		Casted_PlayerState->OnRep_SquadId();
	}

	return oServerReadyToStartMatch(PlayerController);
}