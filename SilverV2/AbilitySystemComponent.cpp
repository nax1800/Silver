#include "AbilitySystemComponent.h"

void UAbilitySystemComponent::ClientActivateAbilityFailed(FGameplayAbilitySpecHandle& AbilityToActivate, uint16_t PredictionKey)
{
	return CallFunc<void>("AbilitySystemComponent", "ClientActivateAbilityFailed", AbilityToActivate, PredictionKey);
}

void UAbilitySystemComponent::ClientCancelAbility(FGameplayAbilitySpecHandle& AbilityToCancel, const FGameplayAbilityActivationInfo& ActivationInfo)
{
	return CallFunc<void>("AbilitySystemComponent", "ClientCancelAbility", AbilityToCancel, ActivationInfo);
}

void UAbilitySystemComponent::ClientEndAbility(FGameplayAbilitySpecHandle& AbilityToEnd, FGameplayAbilityActivationInfo& ActivationInfo)
{
	return CallFunc<void>("AbilitySystemComponent", "ClientEndAbility", AbilityToEnd, ActivationInfo);
}