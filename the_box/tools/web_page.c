/*
	Web Page 
	
	Functionality : add jobs to web, page, add things to web page.
	-Menu 
	-Files ()
	
	inherit:
	- tool object
	
*/

const char file_path[] = "projects.txt";  /* File with numbers */

int data[MAX_NUMBERS];  /* Array of numbers  */

const int line = 0;
int entreys = 0;

while (menu_option != 1){
	
		
	printf("\033[1;31m");
	printf(" Web page Menu : pick option \n\n");
	printf("\033[0m;");
	
	printf("2. List Web Pages  \n");
	printf("3. Add Web Page  \n");
	printf("3. Add Project  \n");
	printf("3. Add Design Document  \n");
	printf("3. Add Product  \n");
	printf("3. Add Service  \n");
	printf("3. Add Jobs  \n");
	printf("1. Exit tool\n");
	
	if(menu_option == 2) // list all
	{ 
		FILE_pointer = fopen("C:\\documentos\\character.txt","r");
	}
	else if(option == 3)
	{ // Add character
	
		printf("name: ");
		scanf("%d",&num1);
		printf("Title: ");
		scanf("%d",&num1);
		printf("Discription: ");
		scanf("%d",&num2);
		printf("Type: ");
		scanf("%d",&num2);
	}	
}	


/*
	Social Tool
	
	Functionality : add jobs to web, page, add things to web page.
	- Tool Object to abstract tools interface and manage variables and functions better
	-Menu 
	-Files (web_page, user)
	
	inherit: 
	- tool.h, used : information_index_converter(),
	- file.h, used : FILE_pointer, file_path, file, 
	
	Used :
	- 
	
*/

#include <stdio.h>

#include "application_structures\file.h";

#define MAX_NUMBERS   1000    /* Max numbers in file */

const char file_path[] = "projects.txt";  /* File with numbers */

int data[MAX_NUMBERS];  /* Array of numbers  */


char name[] = "page";
char post[] = "";
char cv[] = "";
char links[] = "";
char page_tags[] = {"line", "space", };
char images[] = "";
char videos[] = "";
char web_page[] = "";
char theme[] = "";
char tags[] = "";

 // search ,

char location = "";

while (menu_option != 1){
	
		
	printf("\033[1;31m");
	printf(" Web page Menu : pick option \n\n");
	printf("\033[0m;");
	
	printf("2. List Web Pages  \n");
	printf("3. Add Web Page  \n");
	printf("3. Add Project  \n");
	printf("3. Add Design Document  \n");
	printf("3. Add Product  \n");
	printf("3. Add Service  \n");
	printf("3. Add Jobs  \n");
	printf("1. Exit tool\n");
	
	if(menu_option == 2) // list all
	{ 
		
		file = "information_ranked.txt";
		file_path = "C:\\documentos\\projects.txt";
		error = "unable to open the file projects.txt \n";
		information_index_converter();
		
	}
	else if(option == 2) // List users
	{ 
	
		file = "users.txt";
		file_path = "C:\\documentos\\users.txt";
		error = "unable to open the file users.txt \n";
		information_index_converter();
		
	}	
	else if(option == 3) // Add character
	{ 
	
		printf("name: ");
		scanf("%d",&num1);
		printf("Title: ");
		scanf("%d",&num1);
		printf("Discription: ");
		scanf("%d",&num2);
		printf("Type: ");
		scanf("%d",&num2);
		
	}	
}	
