// https://gamedev.stackexchange.com/questions/59589/rpg-level-experience-formula#59590
// http://runescape.wikia.com/wiki/Combat_level


/*
	Manage the user local and with a database :
	
	Functionality :
	? Character Object (used in: Character, NPC, vehicles, race , class )
	? Menu 
	? Files ()
	
	Inherit :
	- damage
	
	Notes:
*/

// ========== DECLARATION =================

extern int character_id;
extern char character_name;
extern char character_age;
extern char character_title;
extern char character_image;
extern int character_3d_model;

extern int character_inventory;
int character_items[]; //link
extern int character_spells; //link
extern int character_abilitys; //link
extern int character_status;

int inventory_size;

extern char background; // History
extern char family; // History


float character_level_up = 0.3;
int character_level_up =

int character_damage;
int character_level;
int character_level_value;

int character_xp;

int character_xp_level_up;

//Status



/*  GENERIC VARIABLES */

// ========== DEFINITION =================

int inventory_size = 20; 

weapon_damage(int damage) //
{
	armor_damage = (character_level * character_level_value) + damage;
	//return armor_damage;
}

equip_item(3D model){
	character_3d_model = ;
}

unequip_item(){
	
}

pick_item(){
	
}

equip_weapon(){
	
}

equip_armor(){
	
}

level_up(){
	level = (PREVIOUS Level Xp + PREVIOUS Level Xp) * 10%;
	
}


/* CHARACTERS ARRAY INDEX
Name

*/

/*  CHARACTER INTERFACE */


char characters_index [10][4] = { 

   {"name", "image", "image_extension", "3d_model", "3d_model_etension", }  

   
};

char characters[10][4] = { 

   {"name", "image", "image_extension", "3d_model", "3d_model_etension", }  

};   
   
/*  CHARACTER STATUS */   
   
char characters_status_index [1][4] = {

	{"strenght", "agility", "endurance", "intelect", } 
};

char characters_status [10][4] = { 

   {"", "", 2, 3}  

   
};

/*  CHARACTER ATRIBUTES */   

char characters_status_index [1][4] = {

 
};

char characters_status [10][4] = { 

   {"", "", 2, 3}  

   
};char characters_status_index [1][4] = {

	{"strenght", "agility", "endurance", "3d_model", "3d_model_etension", } 
};

char characters_status [10][4] = { 

   {"", "", 2, 3}  

   
};

char characters_status_index [1][4] = {

 
};

char characters_status [10][4] = { 

   {"", "", 2, 3}  

   
};

char races_index [10][4] = { 

   {"", "", 2, 3}  

   
};

char races [10][4] = { 

   {"", "", 2, 3}  

   
};

