#pragma once
#include <SDK.h>
using namespace SDK;

#include "Actor.h"

class APawn : public AActor
{

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("Pawn");
	}
};

