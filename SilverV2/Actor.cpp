#include "Actor.h"

FTransform AActor::GetTransform()
{
	return CallFunc<FTransform>("Actor", "GetTransform");
}