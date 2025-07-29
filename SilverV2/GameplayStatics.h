#pragma once
#include <SDK.h>
using namespace SDK;

class UGameplayStatics : public UObject
{

public:
	static float GetTimeSeconds(const UObject* WorldContextObject);

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("GameplayStatics");
	}

	static UGameplayStatics* GetDefaultObj()
	{
		return reinterpret_cast<UGameplayStatics*>(StaticClass()->GetClassDefaultObject());
	}
};

