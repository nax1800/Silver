#include "GameModeBase.h"

UObject* AGameModeBase::SpawnDefaultPawnAtTransform(UObject* NewPlayer, const FTransform& SpawnTransform)
{
	return CallFunc<UObject*>("GameModeBase", "SpawnDefaultPawnAtTransform", NewPlayer, SpawnTransform);
}

UObject* AGameModeBase::hkSpawnDefaultPawnFor(AGameModeBase* GameMode, UObject* NewPlayer, AActor* StartSpot)
{
	if (!NewPlayer || !StartSpot)
		return nullptr;

	UE_LOG(LogGameModeBase, Log, "SpawnDefaultPawnFor Called.");

	return GameMode->SpawnDefaultPawnAtTransform(NewPlayer, StartSpot->GetTransform());
}

UClass* AGameModeBase::hkGetGameSessionClass(AGameModeBase* GameMode, __int64 a2)
{
	UE_LOG(LogGameModeBase, Log, "GetGameSessionClass Called.");

	static UClass* GameSessionClass = StaticClassImpl("FortGameSessionDedicatedAthena");
	return GameSessionClass;
}