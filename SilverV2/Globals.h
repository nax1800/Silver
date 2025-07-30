#pragma once
#include <SDK.h>
using namespace SDK;

#include "World.h"
#include "GameViewportClient.h"
#include "FortEngine.h"

#include "FortGameStateAthena.h"
#include "FortGameModeAthena.h"

inline bool g_bIsPlaylistLoaded = false;
inline bool g_bIsListening = false;
inline bool g_bNoMCP = true;

inline UFortEngine* GetEngine()
{
	return UFortEngine::GetDefaultObj();
}

inline UWorld* GetWorld()
{
	return reinterpret_cast<UGameViewportClient*>(UEngine::GetEngine()->GetGameViewport())->GetWorld();
}

inline AFortGameStateAthena* GetGameState()
{
	return reinterpret_cast<AFortGameStateAthena*>(GetWorld()->GetGameState());
}

inline AFortGameModeAthena* GetGameMode()
{
	return reinterpret_cast<AFortGameModeAthena*>(GetWorld()->GetAuthorityGameMode());
}

