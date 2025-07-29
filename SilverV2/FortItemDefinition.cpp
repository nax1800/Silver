#include "FortItemDefinition.h"

UFortItem* UFortItemDefinition::CreateTemporaryItemInstanceBP(int32 Count, int32 Level)
{
	return CallFunc<UFortItem*>("FortItemDefinition", "CreateTemporaryItemInstanceBP", Count, Level);
}