#pragma once
#include <SDK.h>
using namespace SDK;

#include "Actor.h"

class AGameStateBase : public AActor
{
public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("GameStateBase");
	}
};

