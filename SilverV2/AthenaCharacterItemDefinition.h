#pragma once
#include <SDK.h>
using namespace SDK;

class UAthenaCharacterItemDefinition : public UObject
{
public:
	DEFINE_PTR(UObject, UAthenaCharacterItemDefinition, HeroDefinition);

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("AthenaCharacterItemDefinition");
	}
};

