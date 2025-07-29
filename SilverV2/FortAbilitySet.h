#pragma once
#include <SDK.h>
using namespace SDK;

#include "FortGameplayAbility.h"


class UFortAbilitySet : public UObject
{
public: 
	DEFINE_MEMBER(TArray<UClass*>, UFortAbilitySet, GameplayAbilities);

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("FortAbilitySet");
	}
};

