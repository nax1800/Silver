#pragma once
#include <SDK.h>
using namespace SDK;

#include "GameplayAbility.h"

struct FGameplayAbilitySpecHandle
{
public:
	int32 Handle;

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("GameplayAbilitySpecHandle");
	}
};

struct FGameplayAbilitySpec
{
public:
	FGameplayAbilitySpecHandle             Handle;                                            // 0x000C(0x0004)(NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	UGameplayAbility* Ability;                                           // 0x0010(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32                                         Level;                                             // 0x0018(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32                                         InputID;                                           // 0x001C(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	UObject* SourceObject;                                      // 0x0020(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         ActiveCount;                                       // 0x0028(0x0001)(ZeroConstructor, IsPlainOldData, RepSkip, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         InputPressed : 1;                                  // 0x0029(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (RepSkip, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8                                         RemoveAfterActivation : 1;                         // 0x0029(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (RepSkip, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8                                         PendingRemove : 1;                                 // 0x0029(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (RepSkip, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8                                         Pad_2A[0x6];                                       // 0x002A(0x0006)(Fixing Size After Last Property [ Dumper-7 ])
	char         ActivationInfo[0x20];                                    // 0x0030(0x0020)(RepSkip, NoDestructor, NativeAccessSpecifierPublic)
	TArray<UGameplayAbility*>               NonReplicatedInstances;                            // 0x0050(0x0010)(ZeroConstructor, RepSkip, NativeAccessSpecifierPublic)
	TArray<UGameplayAbility*>               ReplicatedInstances;                               // 0x0060(0x0010)(ZeroConstructor, NativeAccessSpecifierPublic)
	char            GameplayEffectHandle[0x8];                              // 0x0070(0x0008)(RepSkip, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_78[0x50];                                      // 0x0078(0x0050)(Fixing Struct Size After Last Property [ Dumper-7 ])
};

struct FPredictionKey
{
public:
	uint16_t                                         Current;                                           // 0x0000(0x0002)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint16_t                                         Base;                                              // 0x0002(0x0002)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_4[0x4];                                        // 0x0004(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	char PredictiveConnection[0x8];                              // 0x0008(0x0008)(ZeroConstructor, IsPlainOldData, RepSkip, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                          bIsStale;                                          // 0x0010(0x0001)(ZeroConstructor, IsPlainOldData, RepSkip, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                          bIsServerInitiated;                                // 0x0011(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_12[0x6];                                       // 0x0012(0x0006)(Fixing Struct Size After Last Property [ Dumper-7 ])
};

enum EGameplayAbilityActivationMode : uint8
{
	Authority = 0,
	NonAuthority = 1,
	Predicting = 2,
	Confirmed = 3,
	Rejected = 4,
	EGameplayAbilityActivationMode_MAX = 5,
};

struct FGameplayAbilityActivationInfo
{
public:
	EGameplayAbilityActivationMode                ActivationMode;                                    // 0x0000(0x0001)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         bCanBeEndedByOtherInstance : 1;                    // 0x0001(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8                                         Pad_2[0x6];                                        // 0x0002(0x0006)(Fixing Size After Last Property [ Dumper-7 ])
	FPredictionKey                         PredictionKeyWhenActivated;                        // 0x0008(0x0018)(NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
};

struct FGameplayAbilitySpecContainer
{
public:
	DEFINE_MEMBER(TArray<FGameplayAbilitySpec>, FGameplayAbilitySpecContainer, Items);
	DEFINE_PTR(class UAbilitySystemComponent, FGameplayAbilitySpecContainer, Owner);

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("GameplayAbilitySpecContainer");
	}
};

class UAbilitySystemComponent : public UObject
{
public:
	DEFINE_MEMBER(FGameplayAbilitySpecContainer, UAbilitySystemComponent, ActivatableAbilities);

public:
	void ClientActivateAbilityFailed(FGameplayAbilitySpecHandle& AbilityToActivate, uint16_t PredictionKey);
	void ClientCancelAbility(FGameplayAbilitySpecHandle& AbilityToCancel, const FGameplayAbilityActivationInfo& ActivationInfo);
	void ClientEndAbility(FGameplayAbilitySpecHandle& AbilityToEnd, FGameplayAbilityActivationInfo& ActivationInfo);

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("AbilitySystemComponent");
	}
};

