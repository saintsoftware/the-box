// https://stackoverflow.com/questions/12489/how-do-you-get-a-directory-listing-in-c

/*

#include <stdio.h>
#include <stdio.h> // File Object
#include <dirent.h> // DIR Object

menu(){
}

int main(void)
{

    int menu_option = 0;

    /*
        Tools Interface
    *



    while (menu_option != 7){

    printf(" Tutorials Menu : pick option \n\n");
    printf("1. List tutorials \n"); // Nome, Discrição peque, dsc grande.
    printf("3. Add Tutorial  \n");
    printf("3. Add Dev Log  \n"); // Têm que ser para projecto
    printf("2. Add Book  \n");
    printf("2. Add Guide  \n");
    printf("7. exit  \n");

        scanf("%d", &menu_option);

        if(menu_option == 1){
            printf("menu_option 1  \n");
            system("cls");
            //system("pause");

        }
        else if(menu_option == 2){ // list tutorials
            printf("menu_option 2  \n");
            //system("pause");
            system("cls");
        }
        else if(menu_option == 3){ // Add

            printf("menu_option 3  \n");
            system("cls");

        }
        else if(menu_option == 4){ // Add Dev Log



        }
        else if(menu_option == 4){ // Books


        }
        else if(menu_option == 5){ // Guide




        }
        else if(menu_option == 5){ // List books




        }
        else{
            break;
        }
    }

        //system("cls");
    system("pause");

    return(1);

}
*/

#include <stdlib.h>
#include <stdio.h>
#include <conio.h> // Dos
#include <windows.h>

HANDLE wHnd;    // Handle to write to the console.
HANDLE rHnd;    // Handle to read from the console.

int main(int argc, char* argv[]) {

    // Set up the handles for reading/writing:
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);

    // Change the window title:
    SetConsoleTitle("The Box");

    // Set up the required window size:
    SMALL_RECT windowSize = {0, 0, 850, 810};
    SetConsoleWindowInfo(wHnd, 1, &windowSize);

    // Change the console window size:
    // Create a COORD to hold the buffer size:

    COORD bufferSize = {110, 110};
    SetConsoleScreenBufferSize(wHnd, bufferSize);
    // Exit

        int menu_option = 0;

    /*
        Tools Interface
    */



    while (menu_option != 7){

    printf(" Tutorials Menu : pick option \n\n");
    printf("1. List tutorials \n"); // Nome, Discrição peque, dsc grande.
    printf("3. Add Tutorial  \n");
    printf("3. Add Dev Log  \n"); // Têm que ser para projecto
    printf("2. Add Book  \n");
    printf("2. Add Guide  \n");
    printf("7. exit  \n");

        scanf("%d", &menu_option);

        if(menu_option == 1){
            gotoxy(10, 10);
            printf("menu_option 1  \n");
            system("cls");
            //system("pause");

        }
        else if(menu_option == 2){ // list tutorials
            printf("menu_option 2  \n");
            //system("pause");
            system("cls");
        }
        else if(menu_option == 3){ // Add

            printf("menu_option 3  \n");
            system("cls");

        }
        else if(menu_option == 4){ // Add Dev Log



        }
        else if(menu_option == 4){ // Books


        }
        else if(menu_option == 5){ // Guide




        }
        else if(menu_option == 5){ // List books




        }
        else{
            break;
        }
    }

        //system("cls");
    system("pause");




    return 1;
}
