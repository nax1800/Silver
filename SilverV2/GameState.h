#pragma once
#include <SDK.h>
using namespace SDK;

class AGameState : public UObject
{
public:

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("GameState");
	}
};

