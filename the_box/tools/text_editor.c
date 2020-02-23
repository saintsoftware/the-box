// https://www.codingunit.com/c-tutorial-file-io-using-text-files

/*
	Manage the user local and with a database :
	
	Functionality :
	º Interface Property Object (used in: )
	º Menu 
	º Files ()
	
	Inherit:
	- variables (file_path, FILE_pointer)
	- font.h
*/

#include<stdio.h>
#include<conio.h>
#include<process.h>

int i,j,ch;
char fn[20],e,c;
FILE *fp1,*fp2,*fp;



window_size = 800;   //inherit from resolution.h or window.h
window_padding = 50; //px
window_color = "white";
font = ;



// https://forgetcode.com/C/112-Text-Editor-in-system-software

while (exit_tool != 1){

	printf(" Text Editor : pick option \n\n");
	printf("1. List tutorials \n"); // Nome, Discrição peque, dsc grande.
	printf("2. List Tutorials  \n");
	printf("3. Add Tutorial  \n");
	printf("3. exit  \n"); // 
	
	scanf("%d", &tool);

//void main(){}
	
	do {
		
	clrscr();
	printf("\n\t\t***** TEXT EDITOR *****");
	printf("\n\n\tMENU:\n\t\n");
	printf("\n\t1.CREATE\n\t2.DISPLAY\n\t3.APPEND\n\t4.COPY\n\t5.DELETE\n\t6.EXIT\n");
	printf("\n\tEnter your choice: ");
	scanf("%d",&ch);

		switch(ch)
		{
		case 1:
		Create();
		break;
		case 2:
		Display();
		break;
		case 3:
		Append();
		break;
		case 4:
		Copy();
		break;
		case 5:
		Delete();
		break;
		case 6:
		exit(0);
		}
	}while(1);
}	