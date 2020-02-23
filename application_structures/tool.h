
/*
	Tool Object

	To abstract tools funcionality interface and manage variables and functions better

	Functionality : add jobs to web, page, add things to web page.
	-Menu
	-Files (web_page, user)

	inherit:
	- vars

*/



char tool_name[] = ""; //repetir
char tool_title[] = "";

char tool_discription[] = "";
char tool_contact[] = "";
char tool_autor[] = "";
char tool_link[] = "";
char tool_links[] = "";
char tool_version[] = "";
char tool_tags[] = "";
char tool_images[] = "";
char tool_image[] = "";
char tool_videos[] = "";
char tool_video[] = "";
char tool_web_page[] = "";
char tool_members[] = "";
char tool_type[];
char tool_type_tags[];
char tool_email;
char tool_email_key;

char tool_city;
char tool_country;

char service[] = ""; // service inside
int string_size;


// Game lore

char characters_index_keys[][20] = {"character_id", "character_name", "biografy_id", "skills_id", "spells_id", "items_id", "weapons_id", "status_id"};
char skills_index_keys[][20] = {"skills_id", "skill_name", "ability", "tags", "targets"};
char spells_index_keys[][20] = {"spells_id", "spell_name", "ability", "tags", "targets"};
char biografy_index_keys[][20] = {"biografy_id", "biografy_name", "discription", "citys_id", "worlds_id"};
char items_index_keys[][20] = {"items_id", "item_name", "ability", "tags", "targets"};
char weapons_index_keys[][20] = {"weapons_id", "weapon_name", "ability", "tags", "targets", "wear"};
char status_index_keys[][20] = {"status_id", "status_name", "ability", "tags", "targets", "wear"};
char maps_index_keys[][20] = {"items_id", "map_name", "world", "discription", };
char armor_index_keys[][20] = {"armor_id", "armor_name", "ability", "tags", "targets", "wear"};
char families_index_keys[][20] = {"families_id", "familie_name", "world", "maps", "citys_id" "discription"};
char worlds_index_keys[][20] = {"worlds_id", "world_name", "world", "maps", "citys_id" "discription"};
char npcs_index_keys[][20] = {"npcs_id", "npc_name", "world", "maps", "citys_id", "location", "discription"};
char guilds_index_keys[][20] = {"guilds_id", "guild_name", "world", "maps", "citys_id" "discription"};
char clans_index_keys[][20] = {"guilds_id", "clan_name", "world", "maps_id", "citys_id" "discription"};
char classes_index_keys[][20] = {"guilds_id", "class_name", "world", "maps", "citys_id" "discription"};
char religion_index_keys[][20] = {"religion_id", "religion_name", "world", "maps", "citys_id" "discription"};
char monsters_rpg_index_keys[][20] = {"monster_rpg_id", "monster_rpg_name", "world", "maps", "citys_id" "discription"};
char monsters_sci_fi_index_keys[][20] = {"monster_scifi_id", "monster_sci_fi_name", "world", "maps", "citys_id" "discription"};
char races_index_keys[][20] = {"race_id", "race_name", "biografy_id", "lifespan", "language", "height", "weight" , "skin_color", "hair_color" , "eye_color", "distinctions", "subraces"};

//

information_index_converter(void){

	// Inherit: FILE_pointer, file, file_path

	//file = "character.txt";
	//file_path = "C:\\documentos\\character.txt";
	//error = "unable to open the file character.txt \n";

	FILE *FILE_pointer;

	FILE_pointer = fopen(file_path, "r");
	string_size = strlen(file_path);
	//string_pointer;

	char numbers_split[] = "<number>";
	char tags_split[] = "<tags>";
	char discription_split[] = "<discription>";
	char *pointer;

	pointer = strtok(FILE_pointer, numbers_split);

	if(FILE_pointer != null)
	{
		printf(error);
		//break;
	}
	else
	{

		while(FILE_pointer != NULL){

			printf("'%s'\n", FILE_pointer);
			ptr = strtok(NULL, numbers_split);

		}

		fscanf(FILE_pointer, "%s", &char);

		for(n = 1; n < 5; ++n)
		{
			fread(&num, sizeof(struct threeNum), 1, fptr);
			printf("n1: %d\tn2: %d\tn3: %d", num.n1, num.n2, num.n3);
		}
	}

	fclose(FILE_pointer);

}

void information_index_display(){

	char string[] = "strtok needs to be called several times to split a string";
	int string_size = strlen(string);

	char numbers_split[] = "<number>";
	char tags_split[] = "<tags>";
	char discription_split[] = "<discription>";

	char *pointer = strtok(FILE_pointer, numbers_split);

	while(ptr != NULL)
	{

		printf("'%s'\n", ptr);
		ptr = strtok(NULL, numbers_split);

		ptr = strtok(NULL, numbers_split);

	}

	char delim[] = "<tags>";

	while(pointer != NULL)
	{

		printf("'%s'\n", pointer);
		ptr = strtok(NULL, delim);

	}

	/* This loop will show that there are zeroes in the str after tokenizing */

	for (int i = 0; i < string_size; i++)
	{
		printf("%d ", string[i]); /* Convert the character to integer, in this case the character's ASCII equivalent */
	}

	printf("\n");

}
