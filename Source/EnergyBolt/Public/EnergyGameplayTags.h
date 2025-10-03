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
	
	ENERGYBOLT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Left_Attack);
	ENERGYBOLT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Right_Attack);
	ENERGYBOLT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Up_Attack);
	ENERGYBOLT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Down_Attack);

	/** Event **/
	ENERGYBOLT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Montage_EnergyBolt);
	
}