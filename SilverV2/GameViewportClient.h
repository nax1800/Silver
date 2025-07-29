#pragma once
#include <SDK.h>
using namespace SDK;

#include "World.h"

class UGameViewportClient : public UObject
{
public:
	DEFINE_PTR(UWorld, UGameViewportClient, World);

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("GameViewportClient");
	}
};

