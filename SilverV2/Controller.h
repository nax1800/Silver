#pragma once
#include <SDK.h>
using namespace SDK;

#include "Actor.h"
#include "Pawn.h"

class AController : public AActor
{
public:
	DEFINE_PTR(AActor, AController, PlayerState);
	DEFINE_PTR(APawn, AController, Pawn);

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("Controller");
	}
};


