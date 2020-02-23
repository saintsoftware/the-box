// +-


// https://www.includehelp.com/c-programs/display-a-linked-list-in-reverse.aspx
// https://www.w3resource.com/c-programming-exercises/linked_list/c-linked_list-exercise-22.php
// https://www.programiz.com/c-programming/examples/multiplication-table
// https://stackoverflow.com/questions/39025074/c-program-how-to-print-in-table-format-alignment

/*
	
	
	Functionality :
	- Error Object (used in: standard games, social tool)
	- 
	- 
	- Files (project/errors.txt)
	
	Inherit :
	
	Notes :
*/

#include <stdio.h>
#include <stdlib.h>

char subscription[];
char tournaments[];


event_name = "";

char tournament_name;
char tournament_type[] = {}; 
char tournament_type;
char tournament_time;
char tournament_start;
char tournament_end;


mouse_set_xy(int mx, int my);


struct node{
	int data; // data field
	struct node *next;
};

void display(struct node* head){
	struct node* current=head; // current node set to head

	printf("traversing the list...\n");
	while(current!=NULL){ //traverse until current node isn't NULL
		printf("%d ",current->data);
		current=current->next; // go to next node
	}
}

void reverse_display(struct node* head){
	if(head){
		//recursive call to display in reverse order
		reverse_display(head->next);
		printf("%d ",head->data);
	}
}

struct node* creatnode(int d){
	struct node* temp=malloc(sizeof(struct node));
	temp->data=d;
	temp->next=NULL;
	return temp;
}

int main(){
	printf("creating the linked list by inserting new nodes at the end\n");

	printf("enter 0 to stop building the list, else enter any integer\n");

	int k,count=1,x;

	struct node* curr,*temp;

	scanf("%d",&k);
	struct node* head=creatnode(k); //buliding list, first node
	scanf("%d",&k);
	temp=head;

	///////////////////inserting at the end//////////////////////
	while(k){
		curr=creatnode(k);
		temp->next=curr;//appending each node
		temp=temp->next;
		scanf("%d",&k);
	}
	
	display(head); // displaying the list
	printf("\ndisplaying in reverse order...\n");
	reverse_display(head);//display in reverse order

	return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>

void gotoxy(int column, int line);
int main();
int addProduct();
int displayProduct(); //prototype

struct product {
    int quantity, reorder, i, id;
    char name[20];
    float price;
};

COORD coord = { 0, 0 };

void gotoxy(int x, int y) {
    coord.X = x; coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main() {
    int choice;

    gotoxy(17, 5);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 SYZ INVENTORY PROGRAM \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

    gotoxy(17, 20);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

    gotoxy(22, 8);
    printf("1. Add Product\n\n");

    gotoxy(22, 10);
    printf("2. Display Product\n\n");

    gotoxy(22, 12);
    printf("3. Search Product\n\n");

    gotoxy(22, 14);
    printf("4. Reorder Level of Product\n\n");

    gotoxy(22, 16);
    printf("5. Update Product\n\n");

    gotoxy(22, 18);
    printf("6. Exit\n\n");

    gotoxy(22, 22);
    printf("Please Enter Your Choice : ");
    scanf(" %d", &choice);

    switch (choice) {
      case 1:
        addProduct();
        break;
      case 2:
        displayProduct();
        break;
      case 3:
        searchProduct();
        break;
      case 4:
        reorderProduct();
        break;
      case 5:
        updateProduct();
        break;
      case 6:
        break;
      default:
        system("cls");
        main();
    }
    return (0);
}

/*MENU CODE ENDS !*/

int addProduct() {
    FILE *fp;

    int i = 0;
    struct product a;
    system("cls");

    fp = fopen("inventory.txt", "a+t");

    char checker;

    do {
        system("cls");

        gotoxy(17, 5);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 SYZ INVENTORY PROGRAM \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

        gotoxy(17, 20);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

        gotoxy(22, 8);
        printf("Enter product ID : ");
        scanf(" %d", &a.id);

        gotoxy(22, 10);
        printf("Enter product name : ");
        scanf(" %s", a.name);

        gotoxy(22, 12);
        printf("Enter product quantity : ");
        scanf(" %d", &a.quantity);

        gotoxy(22, 14);
        printf("Enter product price : ");
        scanf(" %f", &a.price);

        gotoxy(22, 17);
        fprintf(fp, "%d %s %d %f\n\n", a.id, a.name, a.quantity, a.price); //SAVE TO TXT FILE LINE !
        printf("Record saved!\n\n");

        fclose(fp);

        gotoxy(22, 22);
        printf("Do you want to enter new product? Y / N : ");

        scanf(" %c", &checker);
        checker = toupper(checker);

        i++;

        system("cls");
    } while (checker=='Y');

    if (checker == 'N') {
        main();
    } else {
        do {
            system("cls");

            gotoxy(17, 5);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 SYZ INVENTORY PROGRAM \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

            gotoxy(17, 20);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

            gotoxy(18, 8);
            printf(">>> Wrong Input! Please Enter Y Or N Only! <<<");

            gotoxy(19, 12);
            printf("Do You Want To Enter New Product? Y / N : ");
            scanf(" %c", &checker);
            checker = toupper(checker);
        } while (checker != 'Y' && checker != 'N');

        if (checker == 'Y'){
            addProduct();
        }

        if (checker == 'N') {
            system("cls");
            main();
        }
    }
    return(0);
}

/*ADD PRODUCT LINE ENDS !*/

int displayProduct() {
    FILE *fp;
    struct product a;

    char true;
    system("cls");

    fp = fopen("inventory.txt", "r");

    gotoxy(17, 5);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 SYZ INVENTORY PROGRAM \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

    gotoxy(5, 6);
    printf("======================================================================");

    gotoxy(5, 7);
    printf("Product ID\t\t Product Name\t\t Quantity\t Unit Price\n"); //TABLE TITLES !

    gotoxy(5, 8);
    printf("======================================================================");

    gotoxy(5,10);
    while (fscanf(fp, "%d %s %d %f", &a.id, a.name, &a.quantity, &a.price) == 4) {
        printf("%d\t\t\t %s\t\t\t %d\t\t %.2f\n\n", a.id, a.name, a.quantity, a.price); //PRINT FROM TXT FILE TO COMMAND PROMPT.
    }
	
    fclose(fp);

    printf("\t\t \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

    printf("\nPress any key to return to Main Menu.");

    getch();

    int main();

    return (0);
}

update

gotoxy(5,10);
                while(fscanf(fp, "%d %s %d %f", &a.id, a.name, &a.quantity, &a.price)==4)
                {
                printf("%-10d\t\t %-12s\t\t %8d\t %8.2f\n\n", a.id, a.name, a.quantity, a.price);
                }

                fclose(fp);