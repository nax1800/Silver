#pragma once
#include <SDK.h>
using namespace SDK;

#include "Pawn.h"

#include "FortPlayerController.h"

class AFortPlayerPawn : public APawn
{
public:
	DEFINE_MEMBER(FFortAthenaLoadout, AFortPlayerPawn, CosmeticLoadout);

public:
	void OnRep_CosmeticLoadout();

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("FortPlayerPawn");
	}
};

