#pragma once
#include <SDK.h>
using namespace SDK;

#include "AbilitySystemComponent.h"

class UFortAbilitySystemComponent : public UAbilitySystemComponent
{
public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("FortAbilitySystemComponent");
	}
};

