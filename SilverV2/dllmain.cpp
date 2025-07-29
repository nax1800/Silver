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

BYTE* __fastcall hkChangeGameSessionId()
{
    return nullptr;
}

void CollectGarbage()
{
    return;
}

__int64 UWorldGetNetMode(UWorld*)
{
    return 1;
}

__int64 AActorGetNetMode(AActor*)
{
    return 1;
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

    HookingManager::CreateHook("ReadyToStartMatch", 0x307C130, AGameMode::hkReadyToStartMatch, (void**)&AGameMode::oReadyToStartMatch);
    HookingManager::CreateHook("SpawnDefaultPawnFor", 0xFB4A00, AGameModeBase::hkSpawnDefaultPawnFor);
    HookingManager::CreateHook("TickFlush", 0x2D39300, UNetDriver::hkTickFlush, (void**)&UNetDriver::oTickFlush);
    HookingManager::CreateHook("KickPlayer", 0x2C03D20, hkKickPlayer);
    HookingManager::CreateHook("CollectGarbage", 0x1E054E0, CollectGarbage);

    HookingManager::CreateHook("ChangeGameSessionId", 0x12E7410, hkChangeGameSessionId);
    HookingManager::CreateHook("UWorldGetNetMode", 0x30100A0, UWorldGetNetMode);
    HookingManager::CreateHook("AActorGetNetMode", 0x29A40F0, AActorGetNetMode);

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

