#include "GameMode.h"

#include "Memory.h"

#include "FortGameModeAthena.h"
#include "FortGameStateAthena.h"
#include "FortPlaylistAthena.h"

#include "KismetStringLibrary.h"
#include "NetDriver.h"

#include "GameplayStatics.h"

#include "Globals.h"

bool AGameMode::hkReadyToStartMatch(AGameMode* GameMode)
{
	AFortGameModeAthena* Casted_GameMode = reinterpret_cast<AFortGameModeAthena*>(GameMode);
	AFortGameStateAthena* Casted_GameState = reinterpret_cast<AFortGameStateAthena*>(GameMode->GetGameState());

	if (!g_bIsPlaylistLoaded)
	{
		static UFortPlaylistAthena* PlaylistToUse = reinterpret_cast<UFortPlaylistAthena*>(GUObjectArray.FindObject("Playlist_DefaultSolo"));
		if (PlaylistToUse)
		{
			FPlaylistPropertyArray& CurrentPlaylistInfo = Casted_GameState->GetCurrentPlaylistInfo();
			static int Size = CurrentPlaylistInfo.StaticClass()->GetSize();
			FPlaylistPropertyArray* CurrentPlaylistInfoPtr = reinterpret_cast<FPlaylistPropertyArray*>(Memory::ResizeVirtualMemory(&CurrentPlaylistInfo, sizeof(CurrentPlaylistInfo), Size));

			CurrentPlaylistInfo.SetBasePlaylist(PlaylistToUse);
			CurrentPlaylistInfo.SetOverridePlaylist(PlaylistToUse);

			// *(UFortPlaylistAthena**)(__int64(Casted_GameState) + 0x1C98) = PlaylistToUse;
			// *(UFortPlaylistAthena**)(__int64(Casted_GameState) + 0x1C90) = PlaylistToUse;

			CurrentPlaylistInfo.GetPlaylistReplicationKey()++;

			Casted_GameState->SetCurrentPlaylistId(PlaylistToUse->GetPlaylistId());
			Casted_GameMode->SetCurrentPlaylistId(PlaylistToUse->GetPlaylistId());
			Casted_GameMode->SetCurrentPlaylistName(PlaylistToUse->GetPlaylistName());
			Casted_GameState->OnRep_CurrentPlaylistId();
			Casted_GameState->OnRep_CurrentPlaylistInfo();

			UE_LOG(LogGameMode, Log, "Playlist Loaded.");

			g_bIsPlaylistLoaded = true;
		}
	}

	if (!Casted_GameState->GetMapInfo())
		return false;
	
	if (!g_bIsListening)
	{
		Casted_GameState->OnRep_CurrentPlaylistInfo();

		static bool (*o_InitListen)(UNetDriver*, void*, FURL&, bool, FString&) = decltype(o_InitListen)(Memory::GetImageBase() + 0x634C10);
		static void (*o_SetWorld)(UNetDriver*, UWorld*) = decltype(o_SetWorld)(Memory::GetImageBase() + 0x2D38590);
		static UNetDriver* (*o_CreateNetDriver)(UObject*, UWorld*, FName) = decltype(o_CreateNetDriver)(Memory::GetImageBase() + 0x2FBED30);

		UWorld* GWorld = GetWorld();

		if (GWorld->GetFName().ToString().ToString() == "Frontend")
			return false;

		FName NetDriverName = UKismetStringLibrary::Conv_StringToName(L"GameNetDriver");
		UE_LOG(LogGameMode, Log, "NetDriverName: %s", NetDriverName.ToString().ToString().c_str());
		UE_LOG(LogGameMode, Log, "GWorld: %s", GWorld->GetFName().ToString().ToString().c_str());
		UE_LOG(LogGameMode, Log, "GetEngine(): %s", GetEngine()->GetFName().ToString().ToString().c_str());

		UNetDriver* NetDriver = o_CreateNetDriver(GetEngine(), GWorld, NetDriverName);
		if (!NetDriver)
		{
			UE_LOG(LogGameMode, Error, "Failed to create NetDriver.");
		}
		else
			UE_LOG(LogGameMode, Log, "NetDriver: (%s).", NetDriver->GetFName().ToString().ToString().c_str());

		GWorld->SetNetDriver(NetDriver);
		NetDriver->SetWorld(GWorld);
		NetDriver->SetNetDriverName(NetDriverName);

		FString Error;
		FURL URL = FURL();
		URL.Port = 7777;

		o_InitListen(NetDriver, GWorld, URL, false, Error);
		o_SetWorld(NetDriver, GWorld);

		GWorld->GetLevelCollections().GetData(0, sizeof(FLevelCollection)).NetDriver = NetDriver;
		GWorld->GetLevelCollections().GetData(0, sizeof(FLevelCollection)).NetDriver = NetDriver;

		void** ReplicationDriverVFT = *(void***)NetDriver->GetReplicationDriver();
		UNetDriver::oServerReplicateActors = decltype(UNetDriver::oServerReplicateActors)(ReplicationDriverVFT[0x56]);

		Casted_GameMode->SetWarmupRequiredPlayerCount(1);
		Casted_GameMode->SetbWorldIsReady(true);

		float TimeSeconds = UGameplayStatics::GetTimeSeconds(GetWorld());
		Casted_GameState->SetWarmupCountdownEndTime(TimeSeconds + 9999.f);
		Casted_GameMode->SetWarmupCountdownDuration(9999.f);
		Casted_GameState->SetWarmupCountdownStartTime(TimeSeconds);
		Casted_GameMode->SetWarmupEarlyCountdownDuration(9999.f);

		g_bIsListening = true;
	}

	bool Ret = false;
	Ret = oReadyToStartMatch(GameMode);
	return Ret;
}