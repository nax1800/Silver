#include "FortInventory.h"

void AFortInventory::HandleInventoryLocalUpdate()
{
	return CallFunc<void>("FortInventory", "HandleInventoryLocalUpdate");
}