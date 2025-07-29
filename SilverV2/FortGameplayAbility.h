#pragma once
#include <SDK.h>
using namespace SDK;

#include "GameplayAbility.h"

class UFortGameplayAbility : public UGameplayAbility
{

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("FortGameplayAbility");
	}
};

