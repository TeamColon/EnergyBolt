// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergyGameplayTags.h"

namespace EnergyGameplayTags
{
	/** Input Tags **/
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move,"InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look,"InputTag.Look");

	/** Player Tags **/
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack,"Player.Ability.Attack");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Left_Attack,"Player.Left.Attack");
	UE_DEFINE_GAMEPLAY_TAG(Player_Right_Attack,"Player.Right.Attack");
	UE_DEFINE_GAMEPLAY_TAG(Player_Up_Attack,"Player.Up.Attack");
	UE_DEFINE_GAMEPLAY_TAG(Player_Down_Attack,"Player.Down.Attack");
	
	/** Event Tags **/
	UE_DEFINE_GAMEPLAY_TAG(Event_Montage_EnergyBolt ,"Event.Montage.EnergyBolt");
	
}
