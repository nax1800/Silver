#pragma once
#include <SDK.h>
using namespace SDK;

#include "GameInstance.h"

class UNetDriver;

DEFINE_LOG_CATEGORY(World);

struct FURL
{
public:
	FString Protocol;
	FString Host;
	int32 Port;
	int32 Valid;  
	FString Map;
	FString RedirectUrl;
	TArray<FString> Op; 
	FString Portal;
};

struct FLevelCollection
{
public:
	uint8                                         Pad_0[0x8];                                        // 0x0000(0x0008)(Fixing Size After Last Property [ Dumper-7 ])
	UObject* GameState;                                         // 0x0008(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	UNetDriver* NetDriver;                                         // 0x0010(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	UObject* DemoNetDriver;                                     // 0x0018(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	UObject* PersistentLevel;                                   // 0x0020(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	TSet<UObject*>                           Levels;                                            // 0x0028(0x0050)(ZeroConstructor, NativeAccessSpecifierPrivate)
};

class UWorld : public UObject
{
public:
	DEFINE_PTR(UGameInstance, UWorld, OwningGameInstance);
	DEFINE_PTR(UNetDriver, UWorld, NetDriver);

	DEFINE_MEMBER(TArray<FLevelCollection>, UWorld, LevelCollections);

public:
	static bool hkListen(FURL& InURL);

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("World");
	}
};

