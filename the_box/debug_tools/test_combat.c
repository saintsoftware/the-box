
int level_n = 0;

main(void)
{
	
	while(loop != 0)
	{

	
		levels = {""};
		level[0];
		
		#include "../labraries_stack/map.c"
		
		active_monster = 1;
		flags = {"random monsters", "fixed monsters"};
		areas_flags = {"city", "arena", "random encounter", "pvp", "fixe encounter"};
		areas = {"city sorrounding", "fire dungeon level 1"};
		
		#include "../labraries_stack/area.c"
		
		spells_active = 1;
		abilitys_active = 1;
		defend_active = 1;
		move_active = 1;
		attack_active = 1;
		
		
		attack_range = 10;
		attack_types = {"melee", "slash", "ranged", "piercing", "magic"};
		
		#include "../labraries_stack/attack.c"
		
		
		defense_range = 10;
		defense_types = {"block", "dodge", "shield"};
		
		#include "../labraries_stack/defense.c"
		
		movement_speed = 5;
		jump_active = 1;
		
		
		#include "../labraries_stack/movement.c"
		
		spells_types = {""};
		spells_levels = {1, 1, 5};
		
		#include "../labraries_stack/spells.c"
		
		
		monsters = {"Acolyte", "Aurelia", "Battleforce Angel"};
		
		monsters_levels = {1, 2, 3}
		
		spawm_type = {"random", "fixed"};
		spanws_fixed = {""};
		
		load_monster_area;
		
		
		#include "../labraries_stack/load_mosters_to_areas.c"
		
		combat_area = {""};
		combat_type = {"turns", "range", "auto", "income"};
		combat_turn_time = 1000;
		
		#include "../labraries_stack/combat.c"
		
		
		win_condition_types = {"value", "range"};
		
		#include "../labraries_stack/win_condition.c"
		
		
		
	
	}
}	