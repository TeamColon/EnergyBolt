// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/AttributeInfo.h"

FEnergyAttributeInfoRow UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag,
                                                       bool bLogNotFound) const
{
	for (const FEnergyAttributeInfoRow& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))	// 정확히 매칭된 태그라면
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find Info for AttributeTag [%s] on AttributeInfo [%s]."), *AttributeTag.ToString(),*GetNameSafe(this));
	}

	return FEnergyAttributeInfoRow();
}
