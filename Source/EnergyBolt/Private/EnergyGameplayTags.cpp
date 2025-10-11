// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergyGameplayTags.h"

namespace EnergyGameplayTags
{
	/** Input Tags **/
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move,"InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look,"InputTag.Look");


	/** Enemy Tags **/
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee,"Enemy.Ability.Attack.Melee");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Ranged,"Enemy.Ability.Attack.Ranged");

	/** Damage Tags**/
	UE_DEFINE_GAMEPLAY_TAG(Damage,"Damage");

	/** HitReact Tags**/
	UE_DEFINE_GAMEPLAY_TAG(HitReact,"HitReact");

	
	UE_DEFINE_GAMEPLAY_TAG(Event_Montage_Attack_Melee,"Event.Montage.Attack.Melee");
	
}
