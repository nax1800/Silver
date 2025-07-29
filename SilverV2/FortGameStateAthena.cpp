#include "FortGameStateAthena.h"

void AFortGameStateAthena::OnRep_CurrentPlaylistInfo()
{
	this->CallFunc<void>("FortGameStateAthena", "OnRep_CurrentPlaylistInfo");
}

void AFortGameStateAthena::OnRep_CurrentPlaylistId()
{
	this->CallFunc<void>("FortGameStateAthena", "OnRep_CurrentPlaylistId");
}