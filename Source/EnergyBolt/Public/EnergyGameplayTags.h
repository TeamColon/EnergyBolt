// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace EnergyGameplayTags
{
	/** input **/
	ENERGYBOLT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	ENERGYBOLT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);



	/** Enemy **/
	ENERGYBOLT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Attack_Melee);
	ENERGYBOLT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Attack_Ranged);

	/** Damage **/
	ENERGYBOLT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage);

	/** HitReact **/
	ENERGYBOLT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(HitReact);
	
}