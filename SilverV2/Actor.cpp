#include "Actor.h"

FTransform AActor::GetTransform()
{
	return CallFunc<FTransform>("Actor", "GetTransform");
}

__int64 AActor::hkGetNetMode(AActor*)
{
	return 1;
}