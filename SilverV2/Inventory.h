#pragma once
#include "framework.h"

class AFortPlayerController;
class UFortItemDefinition;

struct FGuid;

namespace Inventory
{
	void Update(AFortPlayerController* PlayerController);
	FGuid AddItem(AFortPlayerController* PlayerController, UFortItemDefinition* ItemDefinition, int Count = 1, int LoadedAmmo = 0, bool bForceNewItem = false);
}