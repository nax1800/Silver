#pragma once
#include <SDK.h>
using namespace SDK;

class UGameInstance
{
public:
	DEFINE_MEMBER(TArray<UObject*>, UGameInstance, LocalPlayers);

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("GameInstance");
	}
};

