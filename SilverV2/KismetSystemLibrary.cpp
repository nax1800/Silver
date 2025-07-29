#include "KismetSystemLibrary.h"

void UKismetSystemLibrary::ExecuteConsoleCommand(UObject* WorldContextObject, const FString& Command, UObject* SpecificPlayer) 
{
	return GetDefaultObj()->CallFunc<void>("KismetSystemLibrary", "ExecuteConsoleCommand", WorldContextObject, Command, SpecificPlayer);
}