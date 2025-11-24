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
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_MultiRanged,"Enemy.Ability.Attack.MultiRanged");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Summon,"Enemy.Ability.Attack.Summon");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_HomingAttack,"Enemy.Ability.Attack.HomingAttack");

	/** Damage Tags**/
	UE_DEFINE_GAMEPLAY_TAG(Damage,"Damage");

	/** HitReact Tags**/
	UE_DEFINE_GAMEPLAY_TAG(HitReact,"HitReact");

	
	UE_DEFINE_GAMEPLAY_TAG(Event_Montage_Attack_Melee,"Event.Montage.Attack.Melee");

	
	UE_DEFINE_GAMEPLAY_TAG(Montage_Attack_Weapon,"Montage.Attack.Weapon");

	
	/** Player Tags **/
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack,"Player.Ability.Attack");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Attack_Power,"Player.Attack.Power");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Attack_Left,"Player.Attack.Left");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attack_Right,"Player.Attack.Right");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attack_Up,"Player.Attack.Up");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attack_Down,"Player.Attack.Down");

	/** Attribute Tags **/
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Attack_AttackPower,"Attributes.Attack.AttackPower");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Attack_DamageMultiplier,"Attributes.Attack.DamageMultiplier");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Attack_Range,"Attributes.Attack.Range");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Attack_FireRate,"Attributes.Attack.FireRate");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Attack_ShotSpeed,"Attributes.Attack.ShotSpeed");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Attack_ShotCount,"Attributes.Attack.ShotCount");
	
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Player_MaxHealth,"Attributes.Player.MaxHealth");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Player_CurrentHealth,"Attributes.Player.CurrentHealth");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Player_BaseSpeed,"Attributes.Player.BaseSpeed");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Player_SpeedMultiplier,"Attributes.Player.SpeedMultiplier");
	
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Player_Gold,"Attributes.Player.Gold");
	
	/** Event Tags **/
	UE_DEFINE_GAMEPLAY_TAG(Event_Montage_EnergyBolt ,"Event.Montage.EnergyBolt");
	
}
