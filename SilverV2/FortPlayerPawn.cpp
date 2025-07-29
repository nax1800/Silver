#include "FortPlayerPawn.h"

void AFortPlayerPawn::OnRep_CosmeticLoadout()
{
	return CallFunc<void>("FortPlayerPawn", "OnRep_CosmeticLoadout");
}