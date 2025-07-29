#pragma once
#include <SDK.h>
using namespace SDK;

class UFortItem : public UObject
{
public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("FortItem");
	}
};

