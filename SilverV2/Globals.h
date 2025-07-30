#pragma once
#include <SDK.h>
using namespace SDK;

#include "World.h"
#include "GameViewportClient.h"
#include "FortEngine.h"

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