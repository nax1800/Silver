#include "World.h"
#include "NetDriver.h"

#include "Memory.h"
#include "Globals.h"

#include "KismetStringLibrary.h"

__int64 UWorld::hkGetNetMode(UWorld*)
{
	return 1;
}

bool UWorld::hkListen(FURL& InURL)
{

	return true;
}