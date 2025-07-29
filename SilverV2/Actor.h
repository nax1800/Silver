#pragma once
#include <SDK.h>
using namespace SDK;

struct FQuat
{
public:
	float                                         X;                                                 // 0x0000(0x0004)(Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         Y;                                                 // 0x0004(0x0004)(Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         Z;                                                 // 0x0008(0x0004)(Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         W;                                                 // 0x000C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

struct FVector
{
public:
	using UnderlayingType = float;

	float                                         X;                                                 // 0x0000(0x0004)(Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         Y;                                                 // 0x0004(0x0004)(Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         Z;                                                 // 0x0008(0x0004)(Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)

public:
	FVector& Normalize()
	{
		*this /= Magnitude();
		return *this;
	}
	FVector& operator*=(const FVector& Other)
	{
		*this = *this * Other;
		return *this;
	}
	FVector& operator*=(float Scalar)
	{
		*this = *this * Scalar;
		return *this;
	}
	FVector& operator+=(const FVector& Other)
	{
		*this = *this + Other;
		return *this;
	}
	FVector& operator-=(const FVector& Other)
	{
		*this = *this - Other;
		return *this;
	}
	FVector& operator/=(const FVector& Other)
	{
		*this = *this / Other;
		return *this;
	}
	FVector& operator/=(float Scalar)
	{
		*this = *this / Scalar;
		return *this;
	}

	UnderlayingType Dot(const FVector& Other) const
	{
		return (X * Other.X) + (Y * Other.Y) + (Z * Other.Z);
	}
	UnderlayingType GetDistanceTo(const FVector& Other) const
	{
		FVector DiffVector = Other - *this;
		return DiffVector.Magnitude();
	}
	UnderlayingType GetDistanceToInMeters(const FVector& Other) const
	{
		return GetDistanceTo(Other) * static_cast<UnderlayingType>(0.01);
	}
	FVector GetNormalized() const
	{
		return *this / Magnitude();
	}
	bool IsZero() const
	{
		return X == 0.0 && Y == 0.0 && Z == 0.0;
	}
	UnderlayingType Magnitude() const
	{
		return std::sqrt((X * X) + (Y * Y) + (Z * Z));
	}
	bool operator!=(const FVector& Other) const
	{
		return X != Other.X || Y != Other.Y || Z != Other.Z;
	}
	FVector operator*(const FVector& Other) const
	{
		return { X * Other.X, Y * Other.Y, Z * Other.Z };
	}
	FVector operator*(float Scalar) const
	{
		return { X * Scalar, Y * Scalar, Z * Scalar };
	}
	FVector operator+(const FVector& Other) const
	{
		return { X + Other.X, Y + Other.Y, Z + Other.Z };
	}
	FVector operator-(const FVector& Other) const
	{
		return { X - Other.X, Y - Other.Y, Z - Other.Z };
	}
	FVector operator/(const FVector& Other) const
	{
		if (Other.X == 0.0f || Other.Y == 0.0f || Other.Z == 0.0f)
			return *this;

		return { X / Other.X, Y / Other.Y, Z / Other.Z };
	}
	FVector operator/(float Scalar) const
	{
		if (Scalar == 0.0f)
			return *this;

		return { X / Scalar, Y / Scalar, Z / Scalar };
	}
	bool operator==(const FVector& Other) const
	{
		return X == Other.X && Y == Other.Y && Z == Other.Z;
	}
};

struct FTransform
{
public:
	FQuat                                  Rotation;                                          // 0x0000(0x0010)(Edit, BlueprintVisible, SaveGame, IsPlainOldData, NoDestructor, NativeAccessSpecifierPublic)
	FVector                                Translation;                                       // 0x0010(0x000C)(Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_1C[0x4];                                       // 0x001C(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	FVector                                Scale3D;                                           // 0x0020(0x000C)(Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_2C[0x4];                                       // 0x002C(0x0004)(Fixing Struct Size After Last Property [ Dumper-7 ])
};

class AActor : public UObject
{
public:
	FTransform GetTransform();
public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("Actor");
	}
};

