#pragma once
#include <SDK.h>
using namespace SDK;

#include "GameStateBase.h"

class AGameState : public AGameStateBase
{
public:

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("GameState");
	}
};

