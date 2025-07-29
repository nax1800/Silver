#pragma once
#include <SDK.h>
using namespace SDK;

#include "Memory.h"

#include "GameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "Actor.h"
#include "FortPlayerStateAthena.h"
#include "FortAbilitySet.h"

namespace Abilities
{
	struct FGameplayEventData
	{
	public:
		char                           EventTag[0x8];                                          // 0x0000(0x0008)(Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		AActor* Instigator;                                        // 0x0008(0x0008)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		AActor* Target;                                            // 0x0010(0x0008)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		UObject* OptionalObject;                                    // 0x0018(0x0008)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		UObject* OptionalObject2;                                   // 0x0020(0x0008)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		char           ContextHandle[0x18];                                     // 0x0028(0x0018)(Edit, BlueprintVisible, NativeAccessSpecifierPublic)
		char                  InstigatorTags[0x20];                                    // 0x0040(0x0020)(Edit, BlueprintVisible, NativeAccessSpecifierPublic)
		char                  TargetTags[0x20];                                        // 0x0060(0x0020)(Edit, BlueprintVisible, NativeAccessSpecifierPublic)
		float                                         EventMagnitude;                                    // 0x0080(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		uint8                                         Pad_84[0x4];                                       // 0x0084(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
		char       TargetData[0x28];                                        // 0x0088(0x0028)(Edit, BlueprintVisible, NativeAccessSpecifierPublic)
	};

  //  static inline FGameplayAbilitySpecHandle* (*GiveAbility)(UAbilitySystemComponent* _this, FGameplayAbilitySpecHandle* outHandle, FGameplayAbilitySpec inSpec) = decltype(GiveAbility)(Memory::GetImageBase() + 0x843df0);
    static inline __int64 (*oGiveAbilityAndActivateOnce)(void*, FGameplayAbilitySpecHandle*, FGameplayAbilitySpec) = decltype(oGiveAbilityAndActivateOnce)(Memory::GetImageBase() + 0x843f10);
    static inline bool (*InternalTryActivateAbility)(UAbilitySystemComponent* _this, FGameplayAbilitySpecHandle Handle, FPredictionKey InPredictionKey, UGameplayAbility** OutInstancedAbility, void* OnGameplayAbilityEndedDelegate, FGameplayEventData* TriggerEventData) = decltype(InternalTryActivateAbility)(Memory::GetImageBase() + 0x8455d0);
    static inline __int64 (*SpecConstructor)(FGameplayAbilitySpec* spec, UObject* Ability, int Level, int InputID, UObject* SourceObject) = decltype(SpecConstructor)(Memory::GetImageBase() + 0x868290);

    inline FGameplayAbilitySpec* FindAbilitySpecFromHandle(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAbilitySpecHandle Handle)
    {
        for (int i = 0; i < AbilitySystemComponent->GetActivatableAbilities().GetItems().Num(); i++)
        {
            if (AbilitySystemComponent->GetActivatableAbilities().GetItems().GetData(i).Handle.Handle == Handle.Handle)
            {
                UE_LOG(LogFortSDK, Log, "OKKKK");
                return &AbilitySystemComponent->GetActivatableAbilities().GetItems().GetData(i);
            }
        }

        return nullptr;
    }

    inline void hkInternalServerTryActivateAbility(UAbilitySystemComponent* ASc, FGameplayAbilitySpecHandle Handle, bool InputPressed, const FPredictionKey& PredictionKey, FGameplayEventData* TriggerEventData)
    {
        UE_LOG(LogFortSDK, Log, "wow");
        FGameplayAbilitySpec* Spec = FindAbilitySpecFromHandle(ASc, Handle);
        if (!Spec)
        {
            ASc->ClientActivateAbilityFailed(Handle, PredictionKey.Current);
            return;
        }

        const UGameplayAbility* AbilityToActivate = Spec->Ability;

        UGameplayAbility* InstancedAbility = nullptr;
        Spec->InputPressed = true;

        if (InternalTryActivateAbility(ASc, Handle, PredictionKey, &InstancedAbility, nullptr, TriggerEventData))
        {
        }
        else
        {
            ASc->ClientActivateAbilityFailed(Handle, PredictionKey.Current);
            Spec->InputPressed = false;
        }
    }

    inline FGameplayAbilitySpec* FindGameplayAbility(AFortPlayerStateAthena* PlayerState, UGameplayAbility* GameplayAbility)
    {
        UFortAbilitySystemComponent* AbilitySystemComponent = PlayerState->GetAbilitySystemComponent();
        if (!AbilitySystemComponent)
            return nullptr;

        for (int i = 0; i < AbilitySystemComponent->GetActivatableAbilities().GetItems().Num(); i++)
        {
            FGameplayAbilitySpec& Spec = AbilitySystemComponent->GetActivatableAbilities().GetItems().GetData(i);
            if (!Spec.Ability)
                continue;

            if (Spec.Ability == GameplayAbility)
                return &Spec;
        }

        return nullptr;
    }
    inline void RemoveGameplayAbility(AFortPlayerStateAthena* PlayerState, UGameplayAbility* GameplayAbility)
    {
        if (!GameplayAbility)
            return;

        UFortAbilitySystemComponent* AbilitySystemComponent = PlayerState->GetAbilitySystemComponent();
        if (!AbilitySystemComponent)
            return;

        FGameplayAbilitySpec* AbilitySpec = FindGameplayAbility(PlayerState, GameplayAbility);

        if (!AbilitySpec)
            return;

     //   AbilitySystemComponent->ClientCancelAbility(AbilitySpec->Handle, AbilitySpec->ActivationInfo);
   //     AbilitySystemComponent->ClientEndAbility(AbilitySpec->Handle, AbilitySpec->ActivationInfo);
     //   AbilitySystemComponent->ServerEndAbility(AbilitySpec->Handle, AbilitySpec->ActivationInfo, {}); // ClearAbility ???
    }

    inline void GrantGameplayAbility(AFortPlayerStateAthena* PlayerState, UClass* GameplayAbilityClass)
    {
        UFortAbilitySystemComponent* AbilitySystemComponent = PlayerState->GetAbilitySystemComponent();

        if (!AbilitySystemComponent)
            return;

        FGameplayAbilitySpec NewSpec{};
        NewSpec.Handle.Handle = rand(); // proper!
        NewSpec.Ability = reinterpret_cast<UGameplayAbility*>(GameplayAbilityClass->GetClassDefaultObject());
        NewSpec.Level = 1;
        NewSpec.InputID = -1;
        NewSpec.SourceObject = nullptr;

        reinterpret_cast<FGameplayAbilitySpecHandle* (*)(UAbilitySystemComponent * _this, FGameplayAbilitySpecHandle * outHandle, FGameplayAbilitySpec inSpec)>(Memory::GetImageBase() + 0x843df0)(AbilitySystemComponent, &NewSpec.Handle, NewSpec);
    }

    inline void ApplyAbilities(AFortPlayerStateAthena* PlayerState)
    {
        static UFortAbilitySet* AbilitySet = reinterpret_cast<UFortAbilitySet*>(GUObjectArray.FindObject("GAS_DefaultPlayer"));
        auto GameplayAbilities = AbilitySet->GetGameplayAbilities(); // crash here or sum
        for (int i = 0; i < GameplayAbilities.Num(); i++)
        {
            GrantGameplayAbility(PlayerState, GameplayAbilities.GetData(i));
        }
    }
}
