// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/EnergyCharacterClassInfo.h"

FCharacterClassDefaultInfo UEnergyCharacterClassInfo::GetClassDefaultInfo(ECharacterClass CharacterClass)
{
	return CharacterClassInfo.FindChecked(CharacterClass);
}
