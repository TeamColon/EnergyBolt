// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace EnergyGameplayTags
{
	/** input **/
	ENERGYBOLT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	ENERGYBOLT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);


	/** Player **/
	ENERGYBOLT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack);
	
	ENERGYBOLT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Attack_Up);
	ENERGYBOLT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Attack_Down);
	ENERGYBOLT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Attack_Left);
	ENERGYBOLT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Attack_Right);

	/** Event **/
	ENERGYBOLT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Montage_EnergyBolt);
	
}