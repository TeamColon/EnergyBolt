// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergyGameplayTags.h"

namespace EnergyGameplayTags
{
	/** Input Tags **/
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move,"InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look,"InputTag.Look");

	/** Player Tags **/
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack,"Player.Ability.Attack");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Attack_Left,"Player.Attack.Left");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attack_Right,"Player.Attack.Right");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attack_Up,"Player.Attack.Up");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attack_Down,"Player.Attack.Down");
	
	/** Event Tags **/
	UE_DEFINE_GAMEPLAY_TAG(Event_Montage_EnergyBolt ,"Event.Montage.EnergyBolt");
	
}
