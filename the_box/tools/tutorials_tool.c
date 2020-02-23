
// tutorial https://www.codingame.com/playgrounds/14213/how-to-play-with-strings-in-c/string-split
//https://www.codingame.com/playgrounds/14213/how-to-play-with-strings-in-c/search-within-a-string

//char tags[] = {"tool", "tutorial", "tutorial",};
// https://libregamewiki.org/List_of_games

// https://www.pcgamingwiki.com/wiki/ListofOpenGL_games
//https://www.yoyogames.com/showcase
//hhttps://libregamewiki.org/SDL_games

// https://www.cprogramming.com/tutorial/c/lesson4.html

/*
	Tutorials tool to Link tutorials in to parts of code, projects, or files :

	Functionality :
	º Menu
	º Files ()

	Inherit:
	- variables (file_path, FILE_pointer)
*/


type[] = "";
type_tags[] = {"Tool", "programing", "software", "game"};
projects[] = "";

//char tutorials_file[] = "";
char tutorial_index_keys[] = {"id" ,"title", "tags" , "links", "autor", "programing language", "", "discription"}; // Order of array in .txt file


printf("Title: ");
scanf("%d",&num1);
printf("Discription: ");
scanf("%d",&num2);
printf("Type: ");
scanf("%d",&num2);
printf("Tags: ");
scanf("%d",&num2);
printf("Files used: ");
scanf("%d",&num2);
printf("Projects: ");
scanf("%d",&num2);
printf("Format: ");
scanf("%d",&num2);


//void string_information_converter(char str[]);



while (menu_option != 1){

	printf(" Tutorials Menu : pick option \n\n");
	printf("1. List tutorials \n"); // Nome, Discrição peque, dsc grande.
	printf("3. Add Tutorial  \n");
	printf("3. Add Dev Log  \n"); // Têm que ser para projecto
	printf("2. Add Book  \n");
	printf("2. Add Guide  \n");

	scanf("%d", &tool);

	/*
		Tools Interface
	*/

	if(menu_option == 1){

		break;

	}
	else if(menu_option == 2){ // list tutorials

		file_type = "txt";
		files = {"tutorials.txt", "books.txt" , "dev_logs.txt"};
		file_path = "C:\\documentos\\tutorials.txt";
		error = "unable to open the file tutorials.txt \n";
		
		information_index_converter();
		
		#include labraies_stack/open_files
		
		object_type = "tutorial";
		object[] = files[0];
		
		#include labraies_stack/load_objects

		object_type = "tutorial";
		object[] = files[0];
		
		#include labraies_stack/load_objects
		
		//FILE_pointer = fopen(file_path, "r");


		if(FILE_pointer != null){
			break;
		}

		char string[] = "strtok needs to be called several times to split a string";
		int string_size = strlen(string);
		char delim[] = ";";

		char *ptr = strtok(string, delim);

		while(ptr != NULL)
		{
			printf("'%s'\n", ptr);
			ptr = strtok(NULL, delim);
		}

		/* This loop will show that there are zeroes in the str after tokenizing */

		for (int i = 0; i < size_string; i++)
		{
			printf("%d ", string[i]); /* Convert the character to integer, in this case
								   the character's ASCII equivalent */
		}
		printf("\n");

		while (FILE_pointer){

		}

	}
	else if(menu_option == 3){ // Add

		printf("Title: ");
		scanf("%d", tool_title);
		printf("Link: ");
		scanf("%d",&num1);
		printf("Discription: ");
		scanf("%d",&num2);
		printf("Type: ");
		scanf("%d",&num2);
		printf("Tags: ");
		scanf("%d",&num2);
		printf("Files used: ");
		scanf("%d",&num2);
		printf("Project: ");
		scanf("%d",&num2);
		printf("Projects used: ");
		scanf("%d",&num2);
		printf("Format: ");
		scanf("%d",&num2);
		printf("Autor: ");
		scanf("%d",&num2);
		printf("Links: ");
		scanf("%d",&num2);

		printf("Contacts: ");
		scanf("%d",&num2);
		printf("Web Page: ");
		scanf("%d",&num2);
		printf("Images: ");
		scanf("%d",&num2);
		printf("Videos: ");
		scanf("%d",&num2);

		printf("Members: ");
		scanf("%d",&num2);
		printf("Version: ");
		scanf("%d",&num2);
		printf("languages: ");
		scanf("%d",&num2);


	}
	else if(tool == 4){ // Add Dev Log

		printf("Title: ");
		scanf("%d",&num1);
		printf("Discription: ");
		scanf("%d",&num2);
		printf("Type: ");
		scanf("%d",&num2);

	}
	else if(tool == 4){ // Books

		printf("Book: ");
		scanf("%d",&num1);
		printf("Type: "); // new or page
		scanf("%d",&num2);
		printf("Title: ");
		scanf("%d",&num1);
		printf("Discription: ");
		scanf("%d",&num2);

		printf("Add page: ");
		scanf("%d",&num2);
		printf("Index pages: ");
		scanf("%d",&num2);
		printf("Total pages: ");
		scanf("%d",&num2);
	}
	else if(tool == 5){ // Guide


		printf("Game/software : ");
		printf("Level/tool : ");
		scanf("%d",&num2);

	}
	else if(tool == 5){ // List books


		printf("Discription: ");
		scanf("%d",&num2);

	}
}

}
