#pragma once
#include <SDK.h>
using namespace SDK;

#include "PlayerState.h"

#include "FortAbilitySystemComponent.h"

class AFortPlayerState : public APlayerState
{
public:
	DEFINE_PTR(UObject, AFortPlayerState, HeroType);
	DEFINE_PTR(UFortAbilitySystemComponent, AFortPlayerState, AbilitySystemComponent);

public:
	void OnRep_HeroType();
	void OnRep_PlayerTeam();
	void OnRep_PlayerTeamPrivate();

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("FortPlayerState");
	}
};

