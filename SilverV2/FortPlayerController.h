#pragma once
#include <SDK.h>
using namespace SDK;

#include "PlayerController.h"

#include "AthenaCharacterItemDefinition.h"

DEFINE_LOG_CATEGORY(LogFortPlayerController);

class AFortInventory;

struct FFortAthenaLoadout
{
public:
	DEFINE_MEMBER(FString, FFortAthenaLoadout, BannerIconId);
	DEFINE_MEMBER(FString, FFortAthenaLoadout, BannerColorId);
	DEFINE_PTR(UObject, FFortAthenaLoadout, SkyDiveContrail);
	DEFINE_PTR(UObject, FFortAthenaLoadout, Glider);
	DEFINE_PTR(UObject, FFortAthenaLoadout, Pickaxe);
	DEFINE_BOOL(FFortAthenaLoadout, bIsDefaultCharacter);
	DEFINE_PTR(UAthenaCharacterItemDefinition, FFortAthenaLoadout, Character);
	DEFINE_BOOL(FFortAthenaLoadout, bForceUpdateVariants);
	DEFINE_PTR(UObject, FFortAthenaLoadout, Hat);
	DEFINE_PTR(UObject, FFortAthenaLoadout, Backpack);
	DEFINE_PTR(UObject, FFortAthenaLoadout, LoadingScreen);
	DEFINE_PTR(UObject, FFortAthenaLoadout, BattleBus);
	DEFINE_PTR(UObject, FFortAthenaLoadout, VehicleDecoration);
	DEFINE_PTR(UObject, FFortAthenaLoadout, CallingCard);
	DEFINE_PTR(UObject, FFortAthenaLoadout, MapMarker);
	DEFINE_MEMBER(TArray<UObject*>, FFortAthenaLoadout, Dances);
	DEFINE_PTR(UObject, FFortAthenaLoadout, VictoryPose);
	DEFINE_PTR(UObject, FFortAthenaLoadout, MusicPack);
	DEFINE_PTR(UObject, FFortAthenaLoadout, ItemWrapOverride);
	DEFINE_MEMBER(TArray<UObject*>, FFortAthenaLoadout, ItemWraps);
	DEFINE_PTR(UObject, FFortAthenaLoadout, PetSkin);

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("FortAthenaLoadout");
	}
};

class AFortPlayerController : public APlayerController
{
public:
	DEFINE_MEMBER(FFortAthenaLoadout, AFortPlayerController, CosmeticLoadoutPC);
	DEFINE_PTR(AFortInventory, AFortPlayerController, WorldInventory);

public:
	static inline void (*oServerReadyToStartMatch)(AFortPlayerController*);
	static void hkServerReadyToStartMatch(AFortPlayerController* PlayerController);
public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("FortPlayerController");
	}
};

