#pragma once
#include <SDK.h>
using namespace SDK;

#include "Actor.h"
#include "FortItemDefinition.h"
#include "FortWorldItem.h"

struct FGuid
{
public:
	int32                                         A;                                                 // 0x0000(0x0004)(Edit, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32                                         B;                                                 // 0x0004(0x0004)(Edit, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32                                         C;                                                 // 0x0008(0x0004)(Edit, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32                                         D;                                                 // 0x000C(0x0004)(Edit, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

struct FFortItemEntry
{
public:
	int32                                         Count;                                             // 0x000C(0x0004)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
	int32                                         PreviousCount;                                     // 0x0010(0x0004)(ZeroConstructor, Transient, IsPlainOldData, RepSkip, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
	uint8                                         Pad_14[0x4];                                       // 0x0014(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	UFortItemDefinition* ItemDefinition;                                    // 0x0018(0x0008)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
	float                                         Durability;                                        // 0x0020(0x0004)(ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	int32                                         Level;                                             // 0x0024(0x0004)(ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	int32                                         LoadedAmmo;                                        // 0x0028(0x0004)(ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	uint8                                         Pad_2C[0x4];                                       // 0x002C(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	TArray<FString>                         AlterationDefinitions;                             // 0x0030(0x0010)(ZeroConstructor, SaveGame, RepSkip, NativeAccessSpecifierPrivate)
	FString                                 ItemSource;                                        // 0x0040(0x0010)(ZeroConstructor, SaveGame, RepSkip, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	FGuid                                  ItemGuid;                                          // 0x0050(0x0010)(ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	bool                                          inventory_overflow_date;                           // 0x0060(0x0001)(ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	bool                                          bWasGifted;                                        // 0x0061(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	bool                                          bIsReplicatedCopy;                                 // 0x0062(0x0001)(ZeroConstructor, Transient, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	bool                                          bIsDirty;                                          // 0x0063(0x0001)(ZeroConstructor, Transient, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	bool                                          bUpdateStatsOnCollection;                          // 0x0064(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	uint8                                         Pad_65[0x3];                                       // 0x0065(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	char                       GiftingInfo[0x28];                                       // 0x0068(0x0028)(RepSkip, NativeAccessSpecifierPrivate)
	char       StateValues[0x10];                                       // 0x0090(0x0010)(ZeroConstructor, Transient, NativeAccessSpecifierPrivate)
	class AFortInventory*          ParentInventory;                                   // 0x00A0(0x0008)(ZeroConstructor, Transient, IsPlainOldData, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	char             GameplayAbilitySpecHandle[0x4];                         // 0x00A8(0x0004)(Transient, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	uint8                                         Pad_AC[0x4];                                       // 0x00AC(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	TArray<UObject*>  AlterationInstances;                               // 0x00B0(0x0010)(ZeroConstructor, Transient, NativeAccessSpecifierPrivate)
	TArray<float>                                 GenericAttributeValues;                            // 0x00C0(0x0010)(ZeroConstructor, Transient, NativeAccessSpecifierPrivate)
	uint8                                         Pad_D0[0x50];                                      // 0x00D0(0x0050)(Fixing Struct Size After Last Property [ Dumper-7 ])
};

struct FFortItemList
{
public:
	TArray<FFortItemEntry>                 ReplicatedEntries;                                 // 0x0108(0x0010)(ZeroConstructor, SaveGame, NativeAccessSpecifierPublic)
	uint8                                         Pad_118[0x50];                                     // 0x0118(0x0050)(Fixing Size After Last Property [ Dumper-7 ])
	TArray<class UFortWorldItem*>                 ItemInstances;                                     // 0x0168(0x0010)(ZeroConstructor, NativeAccessSpecifierPublic)
	uint8                                         Pad_178[0x50];                                     // 0x0178(0x0050)(Fixing Struct Size After Last Property [ Dumper-7 ])
};

class AFortInventory : public AActor
{
public:
	DEFINE_MEMBER(FFortItemList, AFortInventory, Inventory);

public:
	void HandleInventoryLocalUpdate();

public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("FortInventory");
	}
};

