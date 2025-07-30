#include "FortPlayerController.h"

#include "FortPlayerStateAthena.h"
#include "FortGameStateAthena.h"

#include "Abilities.h"
#include "Globals.h"

void AFortPlayerController::hkServerReadyToStartMatch(AFortPlayerController* PlayerController)
{
	UE_LOG(LogFortPlayerController, Log, "ServerReadyToStartMatch Called.");
	AFortPlayerStateAthena* Casted_PlayerState = reinterpret_cast<AFortPlayerStateAthena*>(PlayerController->GetPlayerState());

	if (Casted_PlayerState)
	{
		// Abilities::ApplyAbilities(Casted_PlayerState);

		Casted_PlayerState->SetSquadId(Casted_PlayerState->GetTeamIndex() - 2);
		Casted_PlayerState->OnRep_PlayerTeam();
		Casted_PlayerState->OnRep_PlayerTeamPrivate();
		Casted_PlayerState->OnRep_TeamIndex(0);
		Casted_PlayerState->OnRep_SquadId();

		FGameMemberInfo MemberInfo{};
		FGameMemberInfo* MemberInfoPtr = reinterpret_cast<FGameMemberInfo*>(Memory::ResizeVirtualMemory(&MemberInfo, sizeof(MemberInfo), FGameMemberInfo::StaticClass()->GetSize()));

		if (!MemberInfoPtr)
			UE_LOG(LogFortSDK, Error, "MemberInfoPtr is invalid");

		MemberInfoPtr->SetTeamIndex(Casted_PlayerState->GetTeamIndex());
		MemberInfoPtr->SetSquadId(Casted_PlayerState->GetSquadId());
		MemberInfoPtr->SetMemberUniqueId(Casted_PlayerState->GetUniqueId());

		FGameMemberInfoArray& GameMemberInfoArray = GetGameState()->GetGameMemberInfoArray();

		GameMemberInfoArray.GetMembers().Add(*MemberInfoPtr, sizeof(*MemberInfoPtr));

		for (int i = 0; i < GameMemberInfoArray.GetMembers().Num(); i++)
		{
			FGameMemberInfo& Member = GameMemberInfoArray.GetMembers().GetData(i, sizeof(MemberInfoPtr));
			UE_LOG(LogFortSDK, Log, "Member.GetSquadId(): %i", Member.GetSquadId());
			UE_LOG(LogFortSDK, Log, "Member.GetTeamIndex(): %i", Member.GetTeamIndex()); // both 0...
		}
	}

	return oServerReadyToStartMatch(PlayerController);
}