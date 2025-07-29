#pragma once
#include <SDK.h>
using namespace SDK;

class UWorld;

class UNetDriver : public UObject
{
public: 
	DEFINE_PTR(UWorld, UNetDriver, World);
	DEFINE_PTR(UObject, UNetDriver, ReplicationDriver);
	DEFINE_MEMBER(FName, UNetDriver, NetDriverName);
	DEFINE_MEMBER(TArray<UObject*>, UNetDriver, ClientConnections);

public:
	static inline int32 (*oServerReplicateActors)(UObject*);
	static inline void (*oTickFlush)(UNetDriver*);
	static void hkTickFlush(UNetDriver* NetDriver);

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("NetDriver");
	}
};

