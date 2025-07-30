#pragma once
#include <SDK.h>
using namespace SDK;

#include "Controller.h"

DEFINE_LOG_CATEGORY(LogPlayerController);

class AFortPlayerController;
class AFortPlayerPawn;
class AFortPlayerState;

class APlayerController : public AController
{
public:
	DEFINE_PTR(AActor, APlayerController, AcknowledgedPawn);

public:
	static void hkServerAcknowledgePossession(APlayerController* PlayerController, AActor* P);

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("PlayerController");
	}
};


