#include "Inventory.h"

#include "FortPlayerController.h"
#include "FortInventory.h"
#include "FortWorldItem.h"

void Inventory::Update(AFortPlayerController* PlayerController)
{
	PlayerController->GetWorldInventory()->HandleInventoryLocalUpdate();
}

FGuid Inventory::AddItem(AFortPlayerController* PlayerController, UFortItemDefinition* ItemDefinition, int Count, int LoadedAmmo, bool bForceNewItem)
{
	bool bAllowMultipleStacks = ItemDefinition->GetbAllowMultipleStacks();
	int MaxStackSize = ItemDefinition->GetMaxStackSize();
	TArray<FFortItemEntry>& ReplicatedEntries = PlayerController->GetWorldInventory()->GetInventory().ReplicatedEntries;

	UFortWorldItem* StackingItemInstance = nullptr;
	int OverStack = 0;

	if (MaxStackSize > 1)
	{
		for (int i = 0; i < ReplicatedEntries.Num(); i++)
		{
			FFortItemEntry& CurrentEntry = ReplicatedEntries.GetData(i, sizeof(FFortItemEntry));
			UFortItemDefinition* CurrentReplicatedEntry = CurrentEntry.ItemDefinition;

			if (CurrentEntry.ItemDefinition == ItemDefinition)
			{
				if (CurrentEntry.Count < MaxStackSize || !bAllowMultipleStacks)
				{
					StackingItemInstance = reinterpret_cast<UFortWorldItem*>(CurrentReplicatedEntry);
					OverStack = CurrentEntry.Count + Count - MaxStackSize;

					if (!bAllowMultipleStacks && !(CurrentEntry.Count < MaxStackSize))
					{
						break;
					}

					int AmountToStack = OverStack > 0 ? Count - OverStack : Count;
				}
			}
		}
	}

	return {-1, -1, -1, -1};
}