#include "PlayerController.h"

#include "Memory.h"

#include "FortPlayerController.h"
#include "FortPlayerPawn.h"
#include "FortPlayerState.h"

void APlayerController::hkServerAcknowledgePossession(APlayerController* PlayerController, AActor* P)
{
	UE_LOG(LogPlayerController, Log, "ServerAcknowledgePossession Called.");
	AFortPlayerController* Casted_PlayerController = reinterpret_cast<AFortPlayerController*>(PlayerController);
	AFortPlayerPawn* Casted_Pawn = reinterpret_cast<AFortPlayerPawn*>(Casted_PlayerController->GetPawn());
	AFortPlayerState* Casted_PlayerState = reinterpret_cast<AFortPlayerState*>(Casted_PlayerController->GetPlayerState());

	Casted_PlayerController->SetAcknowledgedPawn(Casted_Pawn);

	if (!Casted_PlayerState || !Casted_Pawn)
		return;

	FFortAthenaLoadout& CosmeticLoadout = Casted_PlayerController->GetCosmeticLoadoutPC();
	if (!CosmeticLoadout.GetCharacter())
		UE_LOG(LogPlayerController, Error, "CosmeticLoadout.Character null");

	if (CosmeticLoadout.GetCharacter())
	{
		UE_LOG(LogPlayerController, Log, "CosmeticLoadout.Character ok");
		UE_LOG(LogPlayerController, Log, "CosmeticLoadout.Character: %s", CosmeticLoadout.GetCharacter()->GetFName().ToString().ToString().c_str());
		Casted_Pawn->SetCosmeticLoadout(CosmeticLoadout);
		Casted_Pawn->OnRep_CosmeticLoadout();

		Casted_PlayerState->SetHeroType(CosmeticLoadout.GetCharacter()->GetHeroDefinition());
		UE_LOG(LogPlayerController, Log, "CosmeticLoadout.GetCharacter()->GetHeroDefinition(): %s", CosmeticLoadout.GetCharacter()->GetHeroDefinition()->GetFName().ToString().ToString().c_str());

		Casted_PlayerState->OnRep_HeroType();

		reinterpret_cast<void* (*)(void*, void*)>(Memory::GetImageBase() + 0x175FE30)(Casted_PlayerState, Casted_Pawn); // ApplyCharacterCustomization
	}
}