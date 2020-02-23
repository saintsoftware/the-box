
// https://www.geeksforgeeks.org/scope-rules-in-c/
// https://www.geeksforgeeks.org/multithreading-c-2/
// https://www.geeksforgeeks.org/fork-system-call/
// https://www.geeksforgeeks.org/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/
// https://www.geeksforgeeks.org/basic-code-optimizations-in-c/
// https://www.geeksforgeeks.org/linked-list-set-2-inserting-a-node/
// https://www.geeksforgeeks.org/code-optimization-in-compiler-design/
// https://www.geeksforgeeks.org/c-program-demonstrate-fork-and-pipe/
// https://www.geeksforgeeks.org/understanding-volatile-qualifier-in-c/
// https://www.geeksforgeeks.org/cc-preprocessors/
// https://www.geeksforgeeks.org/exit-vs-_exit-c-cpp/
// https://www.geeksforgeeks.org/basics-file-handling-c/
// https://www.geeksforgeeks.org/pass-2d-array-parameter-c/
// https://www.geeksforgeeks.org/thread-in-operating-system/
// https://www.geeksforgeeks.org/binary-tree-set-1-introduction/
// https://www.geeksforgeeks.org/double-pointer-pointer-pointer-c/
// https://www.geeksforgeeks.org/difference-int-main-int-mainvoid/
// https://www.geeksforgeeks.org/line-splicing-in-c-cpp/
// https://www.geeksforgeeks.org/c-language-2-gq/functions-gq/
//https://www.geeksforgeeks.org/output-of-a-program-set-1/
// https://www.geeksforgeeks.org/bankers-algorithm-in-operating-system-2/


/* EXTERNAL LIBRARY */

#include <stdio.h>  // Scanf and printf functionality
#include <stdlib.h> // Sistem,
#include <unistd.h> //
#include <windows.h> // Create simple windows
#include <stddef.h> // ptrdiff_t on osx
#include <limits.h>
#include <dirent.h>  // Directory's
//#include <typeinfo> //

#include <stdint.h> //integer types - The "width" of an integer type is the number of bits used to store its value in a pure binary system;

#include <stdarg.h> // Get unknowned arguments in to functions
#include <assert.h> // Debug : assert(); print result
#include <string.h> // Compares srings

#include <math.h> // Math functions exemple: absolute values.

#include <conio.h>
#include <graphics.h>
#include <dos.h>
#include <alloc.h> // memory
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//#include <arm_neon.h> //Need to be installed - It can accelerate multimedia and signal processing algorithms such as video encoder/decoder, 2D/3D graphics, gaming, audio and speech processing, image processing, telephony, and sound.

//#include <sys/types.h> // Manage Types of data : http://pubs.opengroup.org/onlinepubs/009696699/basedefs/sys/types.h.html
//#include <sys/stat.h> Data returned by the stat() function

//#include <emmintrin.h> // 3D graphics
//#include <intrin.h> //Need to be installed - __cpuid

//#include <gtk/gtk.h> // Need to be installed


#include <shlobj.h>

/*
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "system.h"
#include "system-error.h"
#include "system-filesystem.h"
#include "system-memory.h"
#include "system-path.h"
#include "system-paths.h"
#include "system-string.h"

#include "system-error.h"
#include "system-memory.h"
#include "system-path.h"
#include "system-compiler.h"


#include <unistd.h>
#include <time.h>
#include <shlobj.h>
#include "config.h"
#define _WIN32_IE 0x0400
#include "system.h"
#include "system-error.h"
#include "config.h"
#include "system-compiler.h"
*/

//#define _WIN32_IE 0x0400

//#include <sqlite3.h> // DATABASE may need to download, not included in base package

/* ACCESS LIBRARY */

//#include "interface4.h"

/*

========== DECLARATION =================

Variables outside main need to be external
*/


//extern int *int_pointer;
//extern char *char_pointer;
//extern float *float_pointer;
//extern FILE *file_pointer;

//counter_4[10] = "test";
//char a = (string)

//int counter_4[10];

// This declaration is needed for communication between the file and program.

/*
	MAIN
	Don't Call Functions or Includes outside Main. C is single threat it doesn't support

*/

#include error.h

#include file.h
#include path.h
#include type.h // manage data types
#include position.h

#include memory.h

#include database.h

#include image.h
#include bitmap.h
#include model.h
#include cursor.h
#include keys.h
#include font.h
#include event.h

#include layer.h
#include pixel_map.h
#include window.h
#include control.h
#include graphics.h
#include 3D.h
#include 2D.h
#include draw.h



	/*
		The Box - Inherit File Structure - application_structures
	*/

#include "application_structures\variables.h" // General Variables
#include "application_structures\debug.h" // Debug
#include "application_structures\time.h"  // Time
#include "application_structures\error.h" // Error manager
#include "application_structures\file.h"  // handle files
#include "application_structures\string.h" // Strings management
#include "application_structures\paths.h" // Paths

#include "game_strutures\user.h"				// User, login
#include "application_structures\database.h" // Database, inherit from user.

#include "application_structures\mouse.h"

// Images

#include "application_structures\image.h" 		// Image
#include "application_structures\image_jpg.h"	// JPG
//#include "application_structures\image_png.h" // PNG
//#include "application_structures\image_gif.h" // GIF

#include "application_structures\sound.h"		// Sound
#include "application_structures\keys.h"		// Key
#include "application_structures\resolution.h"  // Resolution
//#include "application_structures\interface.h" // Interface

// Models

#include "application_structures\model.h"			// Model
#include "application_structures\model_textures.h"
#include "application_structures\model_animation.h"
#include "application_structures\model_particles.h"
#include "application_structures\model_bounds.h"    //colision, triggers

#include "application_structures\model_blend.h"
//#include "application_structures\model_DAE.h"
//#include "application_structures\model_FBX.h"
//#include "application_structures\model_OBJ.h"

// Camera

//#include "application_structures\camera.h
//#include "application_structures\camera_RTS.h
//#include "application_structures\camera_FPS.h
//#include "application_structures\camera_2D.h
//#include "application_structures\camera_3Person.h

#include "application_structures\print_screen.h

#include "application_structures\movement.h" 	  //Movement
#include "application_structures\movement_RPG.h"
#include "application_structures\movement_Vehicles.h"

	#include "application_structures\AI.h"

//extern int interface;

int main(int argc, char **argv) { //double pointer int argc, char **argv

	/*

		Functionality :
		- Main single threat (used in: )
		-
		-
		- Files (project/errors.txt)

		Inherit : interface.h ,

		Notes :
	*/

	/*
	char path_base[] = "c:\user\name\documents"; // path to folders
	char path_the_box[] = "\the_box";
	char path_external_librarys[] = "\the box\external_librarys";
	char path_external_projects[] = "\the box_external_projects";
	char path_external_tools[] = "\the_box_projects";
	char path_the_box_projects[] = "\the_box_projects";
	char path_the_box_toturials[] = "\the_box_toturials";
	*/

	property_width = 600;
	property_height = 400;
	property_padding = 10;

	const int tool_option = 0;
	const int menu_option = 0;

	printf("Hello. Welcome to the Box, version 0.1.2 text based only .\n");
    printf("Press any key to continue...\n");
    getchar();

    //inherit from file

   if (!FILE_pointer){
		return error("can't fopen", "Unable to open file");
   }

   //result = load_from_file(f, x, y, comp,req_comp);
   //fclose(f);

//int counter_4[10] = counter_1;
//printf("name printed as %%s is %s\n",name);

//printf("teste");
//printf("counter %s", a);
//printf("%s\n", counter);


	//printf(a);
    //printf("Enter interface : %i", some_var);
	//printf("ASCII value = %d, Character = %c\n", ch , ch );


	//#include "test_file.c"
	//#include "main3.h"
	//#include "main4.h"

	//printf("test file : %s", a);

	//printf("main : %s", a);



	// The Box - Inherit File Structure	- GAME STRUCTURE LIBRARY

	/*



	*/

	/* TEST LIBRARY */

	//#include "variables_interface.h"
    //#include "interfaces/interface2.h"

	/* EXTERNAL LIBRARY */

	//#include "external_library_strutures\gtk.h"

	if (debug == 1){
		//fprintf (stderr, "%s:%d: %s: Assertion `%s' failed.\n", error_file, error_line, error_func, error_assert);
		//abort ();
	}


	/* Smi

		Tutorial : https://www.includehelp.com/c/
		https://www.includehelp.com/c-programs/design-a-smiley-face-using-graphics-h.aspx
		https://www.includehelp.com/c-programs/
	*/


	while (menu_option != 1)
    {

       /* Title with color */

        printf("\033[1;31m");
		printf("Tools Menu - pick a option \n\n");
		printf("\033[0m;");


		printf("10. Advanced File Browser  \n");
		printf("10. Mapper \n"); // Structure

		printf("10. Game lore  \n");
		printf("10. Game lore : Add lore  \n"); // spells, skills,
		printf("3. Game lore : Create character  \n"); // Templates
		printf("10. Game lore : Screenplay Tool \n"); // Imagens e texto
		printf("10. Game lore : Design Document  \n"); // Templates, Images, Text, ligar as cenas automáticamente
		printf("10. Game lore : Name Generator \n");
		printf("2. Game lore : Maps  \n");
		printf("2. Game lore : Syncronize  \n"); //

		printf("10. Library's   \n");
		printf("10. Library's : Add  \n");

		printf(" Server : User"); // Login, Register,
		printf("10. Server : The Box  \n"); // Connect torrents
		printf("10. Server : Database  \n");
		printf("10. Server : Web  \n");
		printf("10. Server : Local  \n"); // RPG, rts,
		printf("10. Server : Application  \n"); // RPG, rts,
		printf("10. Server : List  \n");
		printf("10. Server : Mail  \n");
		printf("10. Server : FTP  \n");
		prinf("1 Server : File storage : "); // Download, storage projects, torrents, Vários sites


		printf("10. Language tool  \n"); // Manage project languages
		printf("error interface"); // printf("4. Debug Tool  \n");

		printf("polls"); //polls

		printf("2. Team Management \n"); // Chat
		printf("2. Team Management : Add Project \n");
		printf("2. Team Management : Add User \n"); // registed
		printf("2. Team Management : Add Task \n");
		printf("2. Team Management : Add Debate \n");

		printf("2. Generic Management tool \n"); // Hoteis,
		printf("2. Generic Management tool : Add Property \n");
		printf("2. Generic Management tool : Add bill \n");
		printf("2. Generic Management tool : Add client \n"); // Email, Contacts
		printf("2. Generic Management tool : Add Entry \n"); // Email, Contacts
		printf("2. Generic Management tool : Add Task \n"); // Email, Contacts

		printf("2. Projects \n"); // Projects created
		printf("1 projects Add: ");
        printf("2. Projects : Add profile \n");
		printf("2. Projects : Create  \n");
		printf("2. Projects : Syncronize  \n"); //
		printf("2. Projects : Import  \n");
		printf("2  projects : Information: ");
		printf("10. Projects : Programing Simulation Enviorment  \n");
		printf("10. Projects : Database  \n");
		printf("10. Projects : Templates  \n"); // Base projects, manager
		printf("10. Projects : Tasks  \n"); // add tasks

		printf("1 projects:  Debug: ");

		printf("10. projects:  Linker  \n");
		printf("10. projects:  Compiler  \n"); // Make file or link files

		printf("10. Generic Animation \n"); // Base projects 2D,3D,  Create animations
		printf("10. 3D : model management \n"); // Base projects, Load models
		printf("10. 3D : Game Concept \n"); // Templates
		printf("6.  3D : Standard Level Editor  \n"); // Base projects, Load models
		printf("6. 3D  Shadder Tool  \n");
		printf("2.  3D : Particle tool \n"); // Locais e Online printf("1 projects:  Load Games : ");
		printf("6. 3D  Shape Tool  \n");
		printf("6. 3D  Model texture mapping \n");
		printf("6. 3D  Texture Tool  \n");
		
		printf("1 2D  Standard Game : "); // Design a 2D project
		printf("1 2D : Logo ");
        printf("1 2D : Concept Tool "); // Create concepts, Shapes, Characters
        printf("1 2D : standad Interface "); //Interfaces, Templates
		printf("1 Menu Design "); //Interfaces

		printf("1 Isometric ");	// Game
		printf("1 Isometric : Tiles ");
		printf("1 Isometric : Add ");
		printf("1 Isometric : Converter 3D-2D ");

		printf(" light tool"); // manage lights, information on lights

		printf("4. Guardian  \n"); // Monitor internet command request activitys
		printf("4. Font tool  \n");

		printf("4. Text Tool  \n"); // Publish to sites,

		printf("5. Founding \n"); // Votes
		printf("5. Founding : Add  \n");
		printf("5. Founding : Donate  \n");

		//If not connect another color
		printf("5. Market  \n"); //Productos
		printf("5. Market : 2º hand  \n"); //Productos
		printf("5. Market : trade  \n");
		printf("5. Market : add service or product  \n");

		printf("6. Social Tool \n"); // Most viewed, users, ranking content , wall
		printf("6. Social Tool : add comment \n");
		printf("6. Social Tool : search  \n"); 	// ranked information
		printf("6. Social Tool : user \n"); // login, Register - hash
		printf("6. Social Tool : add content \n");
		printf("9. Social Tool : Settings \n"); //user
		printf("9. Social Tool : add Web Page \n"); // Templates
		printf("9. Social Tool : Edit Web Page \n");
		printf("9. Social Tool : Chat \n");
		printf("9. Social Tool : Post \n");
		printf("9. Social Tool : Links Manager \n");
		printf("9. Social Tool : Agenda \n"); //
		printf("9. Social Tool : Mensages \n"); //
		printf("9. Social Tool : groups \n"); //
		printf("9. Social Tool : projects \n");
		prinf("1  Social Tool : Radio : "); // News, projects, music
		prinf("1  Social Tool : TV  : "); // News, about projects and updates.
		printf("9. Newspaper Online \n");
		 // Ranking : sites, filmes, series, ...
		prinf("1  Social Tool :  Tournaments "); // Resultados
		prinf("1  Social Tool :  Events ");
		prinf("1  Social Tool :  Clans & Guilds ");

		printf("9. Jobs \n");
		printf("9. Jobs : Add \n"); // Add to web page, project, or user

		printf("9. Encrypt tool \n");

		printf("9. Web Page : search \n");
		printf("9. Web Page : add Web Page \n"); // Templates
		printf("9. Web Page : Edit Web Page \n");
		printf("9. Web Page : Add module \n");

		printf("9. Links manager \n"); // encrypted
		printf("9. Links manager : Add \n");
		printf("9. Links manager : encrypted \n");

		/*
			Create costume games for old games.
		*/

		printf("9. Games Manager \n") // epocas, ligas, jogadores, jogos, streams
		printf("9. Games Manager : Games \n"); 
		printf("9. Games Manager : Servers \n");
		printf("9. Games Manager : Players  \n"); // List of players, with information on games, rank optional by layes
		printf("9. Games Manager : : Tournaments \n");
		printf("9. Games Manager : Seasons \n"); // epocas  // events, calender, Liga "eventos por tipo)
		
		printf("9. Games Manager : ADD Games  \n");
		printf("9. Games Manager : ADD Tournaments  \n");
		printf("9. Games Manager : ADD Events  \n");
		printf("9. Games Manager : Streaming \n"); // Add user, 

		printf("9. Events \n");
		printf("9. Events : Add \n"); // Costum, comercial event, or Season ou tournament
		printf("9. Events : Calender \n");

		prinf("1  Information ranked "); // social. Vote ranking sistem
		prinf("1  Information ranked : Add ");
		prinf("1  Information ranked : Vote ");
		prinf("1  Information ranked : financing ");
		//printf("9. Vote  \n"); //
		//printf("9. Vote : Add \n");

		printf("8. Toturials  \n");
		printf("8. Toturials : Add  \n"); // Tags
		prinf("1  Toturials : Books : ");
		prinf("1  Toturials : Guides : "); //games
		

		printf("10. scientific Lab  \n"); // Add experiments
		printf("10. scientific Lab : projects  \n");

        printf("5 Settings: "); //language, Keyboard,
        scanf("%d",&language);

		printf(" List tool"); //project management

        printf("1 Standard Functions : "); // Functions
		printf("1 Standard Functions : Add ");
		printf("7. Code snippet : add  \n");

		printf("10. Standard Database  \n");
		printf("10. Standard Database : ADD list  \n"); // To market, social tool
		printf("10. Standard Database : Create \n");
		printf("10. Database  Mysql Interface \n");

        printf("1 Code Editor : "); // link stuff automaticaly
		printf("1 Sound editing : "); // +- Simple
        printf("1 Video editing : "); //

		prinf("1 Web sites downloader tool : "); // Load sites to the software
		printf("10. File converter  \n"); // Active File
		printf("10. Screen record  \n");
		printf("10. Screen print  \n");

		printf("10. Data Manager "); 
		/* Once data is added to the libray there is no need to
			Add it again, just add from library, it saves a lot of time,
			lets say we have to sell 2º hand products which are diferent which time.
			If the product is already in the library is just a matter of adding.		
		*/

		printf("10. Exit \n");
		printf("10. The Box info \n");

        scanf("%d", &interface);


        	//printf("Choose interface : ");
            //scanf("%s", str1);
	       //printf("Enter interface : %s", str1);
            //interface = atoi (str1); // Convertes the string to a integer

		if(interface == 1){
            exit_program = 1;
			break;

		}
		else if(interface == 2){ // Projects

			//printf("Main Menu loading");

			#include "interfaces/projects.c"

			//#include "tools\file_manager.c"
            //#include "tools\variable_manager.c"
            //#include "tools\spells.c"
            //#include "tools\spells.c"
            //#include "tools\character_generator.c"
            //#include "tools\shadder_tool.c"
            //#include "tools\social_tool.c"

		}
		else if(interface == 0){ // Starting Menu
			//printf("Main Menu loading");

			#include "interfaces/starting_menu_GTK.c"
			//#include "interfaces/main_menu_SDL.c"
			//#include "interfaces/main_menu_Free_GLUT.c"
			//#include "interfaces/main_menu_Ogre3D.c" //C++
			//#include "interfaces/main_menu_windows.c"
			//#include "interfaces/main_menu_horde3d.c" //C++

		}
		else if(interface == 1){ // Character Creator

			//printf("Character Creator loading");
			//#include "interfaces/character_generator.h"
			#include "interfaces/character_generator_GTK.c"
		}
		else if(interface == 2){ // Shadder Tool
				//printf("Interface2");
				//#include "interfaces/interface2.c"
		}
		else if(interface == 3){ // Map Editor
				//printf("Map Editor");
				//#include "interfaces/interface3.c"
		}
		else if(interface == 4){ // Variable Manager
				//printf("Interface3");
				//#include "interfaces/interface3.c"
		}
		else if(interface == 5){ // Generic Animation
				//printf("Interface3");
				//#include "interfaces/interface3.c"
		}
		else if(interface == 6){ // Particle Tool
				//printf("Interface3");
				//#include "interfaces/interface3.c"
		}
		else if(interface == 7){ // Particle Tool
				//printf("Interface3");
				//#include "interfaces/interface3.c"
		}
		else if(interface == 8){ // Level Models Position
				//printf("Interface3");
				//#include "applications/the_box/levels_models_position.c"
		}
		else if(interface == 9){ // Level Editor

				//printf("Interface9");

				//#include "applications/the_box/levels_models_position.c"
		}
		else if(interface == 10){ // Database tool
				//printf("Interface9");
				//#include "applications/the_box/levels_models_position.c"
		}
		else if(interface == 11){ // Options
				//printf("Interface9");
				//#include "applications/the_box/levels_models_position.c"
		}
		else if(interface == 12){ // Titans - Medieval battle ground

			#include "game_strutures\money.h" //timers
			#include "game_strutures\spells.h"
			#include "game_strutures\abilitys.h"
			#include "game_strutures\items.h"
			#include "game_strutures\items_sci_fi.h"
			#include "game_strutures\items_rpg.h"
			#include "game_strutures\items_fantasy.h"
			#include "game_strutures\loots.h"
			#include "game_strutures\save.h"
			#include "game_strutures\save_RPG.h"
			#include "game_strutures\save_SCI-FI.h"

			#include "game_strutures/map.h"
			#include "applications/save.h"
			#include "applications/items.h"
			#include "applications/characters.h"
			#include "game_strutures/npcs.h"
			#include "applications/audio.h"
			#include "game_strutures/interface.h"
			#include "game_strutures/game.h"


			items = "the_box_projects/medivel_titans/interface.txt";
			interface = "the_box_projects/medivel_titans/interface.txt";
			maps = "the_box_projects/medivel_titans/map.txt";
			saves = 	"the_box_projects/medivel_titans/save.txt";
			charactes = 	"the_box_projects/medivel_titans/chacters.txt";
			audio = 	"the_box_projects/medivel_titans/audio.txt";
			interface = 	"the_box_projects/medivel_titans/save.obj";
			game();


		}
		else if(interface == 12){ // Fight game 3D

			#include "game_strutures/map.h"
			#include "applications/save.h"
			#include "applications/items.h"
			#include "applications/characters.h"
			#include "game_strutures/npcs.h"
			#include "applications/audio.h"
			#include "game_strutures/interface.h"

			maps = "the_box_projects/medivel_titans/map.obj";
			saves = 	"the_box_projects/medivel_titans/save.obj";
			charactes = 	"the_box_projects/medivel_titans/save.obj";
			audio = 	"the_box_projects/medivel_titans/save.obj";
			interface = 	"the_box_projects/medivel_titans/save.obj";

			#include "game_strutures/game.c"

		}
		else if(interface == 12){ // Eva project - Sci-fi battle ground
				//printf("Interface9");

			#include "game_strutures/map.h"
			#include "applications/save.h"
			#include "applications/items.h"
			#include "applications/characters.h"
			#include "game_strutures/npcs.h"
			#include "applications/audio.h"
			#include "game_strutures/interface.h"

			maps = "the_box_projects/medivel_titans/map.obj";
			saves = 	"the_box_projects/medivel_titans/save.obj";
			items = 	"the_box_projects/medivel_titans/save.obj";
			charactes = 	"the_box_projects/medivel_titans/save.obj";
			npcs = 	"the_box_projects/medivel_titans/save.obj";
			audio = 	"the_box_projects/medivel_titans/save.obj";
			interface = 	"the_box_projects/medivel_titans/save.obj";

			#include "game_strutures/game.c"

		}

		system("cls");
		system("pause");
	}


    return 0; // Zero indicates success any other failed
}


/*

*/
