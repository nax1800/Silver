#include "NetDriver.h"

void UNetDriver::hkTickFlush(UNetDriver* NetDriver)
{
	if (NetDriver && NetDriver->GetReplicationDriver() && NetDriver->GetClientConnections().Num() > 0)
		oServerReplicateActors(NetDriver->GetReplicationDriver());

	return oTickFlush(NetDriver);
}