#pragma once
#include <SDK.h>
using namespace SDK;

#include "FortItem.h"

struct FFortItemEntry;
class AFortInventory;

class UFortWorldItem : public UFortItem 
{
public:
	DEFINE_BOOL(UFortWorldItem, bIsTemporaryItem);
	DEFINE_BOOL(UFortWorldItem, bNeedsPersistentUpdate);
	DEFINE_BOOL(UFortWorldItem, bPendingPersistentDelete);
	DEFINE_PTR(AFortInventory, UFortWorldItem, OwnerInventory);
	//DEFINE_MEMBER(FFortItemEntry, UFortWorldItem, ItemEntry);

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("FortWorldItem");
	}
};

