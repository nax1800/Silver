#include "FortPlayerStateAthena.h"

void AFortPlayerStateAthena::OnRep_TeamIndex(uint8 OldVal)
{
	return CallFunc<void>("FortPlayerStateAthena", "OnRep_TeamIndex", OldVal);
}

void AFortPlayerStateAthena::OnRep_SquadId()
{
	return CallFunc<void>("FortPlayerStateAthena", "OnRep_SquadId");
}