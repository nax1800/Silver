#include "framework.h"

#include "PlayerController.h"
#include "FortPlayerController.h"
#include "FortGameModeAthena.h"
#include "World.h"

#include "KismetSystemLibrary.h"
#include "NetDriver.h"

#include "Globals.h"

#include "Memory.h"

#include "Abilities.h"

char hkKickPlayer(__int64, __int64, __int64)
{
    return 1;
}

static bool hkNoMCP() 
{ 
    return g_bNoMCP; 
}

static __int64 (*oDispatchRequest)(__int64 a1, __int64* a2, int a3);
static __int64 hkDispatchRequest(__int64 a1, __int64* a2, int a3)
{
    if (g_bNoMCP)
        return oDispatchRequest(a1, a2, a3);

    return oDispatchRequest(a1, a2, 3);
}

BYTE* __fastcall hkChangeGameSessionId(UObject* a1)
{
    UE_LOG(LogFortSDK, Log, "hkChangeGameSessionId: a1: %s", a1->GetFName().ToString().ToString().c_str());
    return nullptr;
}

void CollectGarbage()
{
    return;
}

DWORD Main(LPVOID)
{
    AllocConsole();
    FILE* File;
    freopen_s(&File, "CONOUT$", "w+", stdout);

    if (!Init())
    {
        UE_LOG(LogFortSDK, Error, "Failed to initialize.");
        exit(1);
    }

    if (MH_Initialize() != MH_OK)
    {
        SILVER_LOG("MinHook", "Failed to initialize.");
        exit(1);
    }

    *(bool*)(Memory::GetImageBase() + 0x5940A13) = false;
    *(bool*)(Memory::GetImageBase() + 0x5940A14) = true;

    auto ByteToPatch = (uint8_t*)(uint8_t*)(Memory::GetImageBase() + 0xff343c);
    DWORD dwProtection;
    VirtualProtect((PVOID)ByteToPatch, 1, PAGE_EXECUTE_READWRITE, &dwProtection);
    *ByteToPatch = 0x85;
    DWORD dwTemp;
    VirtualProtect((PVOID)ByteToPatch, 1, dwProtection, &dwTemp);

    for (uintptr_t FuncToNull : vector<uintptr_t>{ 0x2815170, 0x12e7410, 0x1704270 })
    {
        uintptr_t func = Memory::GetImageBase() + FuncToNull;
        DWORD dwProtection;
        VirtualProtect((PVOID)func, 1, PAGE_EXECUTE_READWRITE, &dwProtection);
        *(uint8_t*)func = 0xC3;
        DWORD dwTemp;
        VirtualProtect((PVOID)func, 1, dwProtection, &dwTemp);
    }

    UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), L"open Athena_Terrain", nullptr);
    GetWorld()->GetOwningGameInstance()->GetLocalPlayers().Remove(0);

    HookingManager::CreateHook("AGameMode::ReadyToStartMatch", 0x307C130, AGameMode::hkReadyToStartMatch, (void**)&AGameMode::oReadyToStartMatch);
    HookingManager::CreateHook("AGameModeBase::SpawnDefaultPawnFor", 0xFB4A00, AGameModeBase::hkSpawnDefaultPawnFor);
   //  HookingManager::CreateHook("AGameModeBase::GetGameSessionClass", 0xFA0B10, AGameModeBase::hkGetGameSessionClass);
    HookingManager::CreateHook("AFortGameModeAthena::PickTeam", 0xFA9B20, AFortGameModeAthena::hkPickTeam);

    HookingManager::CreateHook("UNetDriver:TickFlush", 0x2D39300, UNetDriver::hkTickFlush, (void**)&UNetDriver::oTickFlush);
    HookingManager::CreateHook("AGameSession::KickPlayer", 0x2C03D20, hkKickPlayer);
    HookingManager::CreateHook("CollectGarbage", 0x1E054E0, CollectGarbage);
    HookingManager::CreateHook("NoMCP", 0x13876d0, hkNoMCP);
    HookingManager::CreateHook("DispatchRequest", 0xcf2e80, hkDispatchRequest, (void**)&oDispatchRequest);

    HookingManager::CreateHook("ChangeGameSessionId", 0x12E7410, hkChangeGameSessionId);
    HookingManager::CreateHook("UWorld::GetNetMode", 0x30100A0, UWorld::hkGetNetMode);
    HookingManager::CreateHook("AActor::GetNetMode", 0x29A40F0, AActor::hkGetNetMode);

    UObject* PlayerControllerDefaultObj = GUObjectArray.FindObject("Default__Athena_PlayerController_C");
    HookingManager::VirtualHook(PlayerControllerDefaultObj, 0x108, APlayerController::hkServerAcknowledgePossession);
    HookingManager::VirtualHook(PlayerControllerDefaultObj, 0x25F, AFortPlayerController::hkServerReadyToStartMatch, (void**)&AFortPlayerController::oServerReadyToStartMatch);

    UObject* FortAbilitySystemComponentAthenDefaultObj = GUObjectArray.FindObject("Default__FortAbilitySystemComponentAthena");
    HookingManager::VirtualHook(FortAbilitySystemComponentAthenDefaultObj, 0xF4, Abilities::hkInternalServerTryActivateAbility);

    return 1;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ulReason, LPVOID lpReserved)
{
    if (ulReason == 1)
        CreateThread(0, 0, Main, 0, 0, 0);

    return TRUE;
}

