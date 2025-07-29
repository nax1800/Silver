#include "FortPlayerState.h"

void AFortPlayerState::OnRep_HeroType()
{
	return CallFunc<void>("FortPlayerState", "OnRep_HeroType");
}

void AFortPlayerState::OnRep_PlayerTeam()
{
	return CallFunc<void>("FortPlayerState", "OnRep_PlayerTeam");
}

void AFortPlayerState::OnRep_PlayerTeamPrivate()
{
	return CallFunc<void>("FortPlayerState", "OnRep_PlayerTeamPrivate");
}