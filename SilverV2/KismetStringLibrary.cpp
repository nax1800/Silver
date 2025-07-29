#include "KismetStringLibrary.h"

FName UKismetStringLibrary::Conv_StringToName(const FString& inString) 
{
	return GetDefaultObj()->CallFunc<FName>("KismetStringLibrary", "Conv_StringToName", inString);
}