#pragma once
#include <SDK.h>
using namespace SDK;

class UKismetStringLibrary : public UObject
{
public:
	static FName Conv_StringToName(const FString& inString);

public:
	static UKismetStringLibrary* GetDefaultObj()
	{
		static UKismetStringLibrary* DefaultObj = reinterpret_cast<UKismetStringLibrary*>(GUObjectArray.FindObject("Default__KismetStringLibrary"));
		return DefaultObj;
	}

	static UClass* StaticClass()
	{
		return StaticClassImpl("KismetStringLibrary");
	}
};

