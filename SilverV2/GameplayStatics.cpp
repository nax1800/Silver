#include "GameplayStatics.h"

float UGameplayStatics::GetTimeSeconds(const UObject* WorldContextObject)
{
	return GetDefaultObj()->CallFunc<float>("GameplayStatics", "GetTimeSeconds", WorldContextObject);
}