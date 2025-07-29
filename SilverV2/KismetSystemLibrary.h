#pragma once
#include <SDK.h>
using namespace SDK;

class UKismetSystemLibrary : public UObject
{
public:

public:
	static void ExecuteConsoleCommand(UObject* WorldContextObject, const FString& Command, UObject* SpecificPlayer);

public:
	static UKismetSystemLibrary* GetDefaultObj()
	{
		static UKismetSystemLibrary* DefaultObj = reinterpret_cast<UKismetSystemLibrary*>(GUObjectArray.FindObject("Default__KismetSystemLibrary"));
		return DefaultObj;
	}

	static UClass* StaticClass()
	{
		return StaticClassImpl("KismetSystemLibrary");
	}
};

