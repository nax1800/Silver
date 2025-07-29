#pragma once
#include <SDK.h>
using namespace SDK;

#include "FortItem.h"

enum EFortRarity : uint8
{
	Handmade = 0,
	Ordinary = 1,
	Sturdy = 2,
	Quality = 3,
	Fine = 4,
	Elegant = 5,
	Masterwork = 6,
	Epic = 7,
	Badass = 8,
	Legendary = 9,
	NumRarityValues = 10,
	EFortRarity_MAX = 11,
};

class UFortItemDefinition : public UObject
{
public:
	DEFINE_MEMBER(EFortRarity, UFortItemDefinition, Rarity);
	DEFINE_MEMBER(int, UFortItemDefinition, MaxStackSize);
	DEFINE_BOOL(UFortItemDefinition, bAllowMultipleStacks);

public:
	UFortItem* CreateTemporaryItemInstanceBP(int32 Count, int32 Level);

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("FortItemDefinition");
	}
};

