#pragma once
#include <SDK.h>
using namespace SDK;

class UGameplayAbility : public UObject
{
public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("GameplayAbility");
	}
};

