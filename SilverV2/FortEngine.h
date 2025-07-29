#pragma once
#include <SDK.h>
using namespace SDK;

class UFortEngine : public UEngine
{

public:
	static UFortEngine* GetDefaultObj()
	{
		static UFortEngine* DefaultObj = reinterpret_cast<UFortEngine*>(GUObjectArray.FindObject("FortEngine_2147482592"));
		return DefaultObj;
	}

	static UClass* StaticClass()
	{
		return StaticClassImpl("FortEngine");
	}
};

