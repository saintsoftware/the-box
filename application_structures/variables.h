
// https://www.geeksforgeeks.org/c-program-to-insert-an-element-in-an-array/
// https://www.geeksforgeeks.org/understanding-extern-keyword-in-c/
// https://www.geeksforgeeks.org/how-to-store-words-in-an-array-in-c/
// https://www.geeksforgeeks.org/c-program-to-concatenate-two-strings-without-using-strcat/
// https://www.geeksforgeeks.org/swap-strings-in-c/

// https://stackoverflow.com/questions/572547/what-does-static-mean-in-c

// ========== DECLARATION =================

/*
	The Box - Generic Variables
*/

/*
 *  Data object declarations:
 */

  typedef unsigned char      byte;
  typedef unsigned long      Char;

int BUFF_SIZE = 4096;

/*
	Web Page 
	
	Functionality : add jobs to web, page, add things to web page.
	-Menu 
	-Files ()
	
	inherit:
	- vars
	
*/

char title[] = "";
char discription[] = "";
char contact[] = "";
char autor[] = "";
char link[] = "";
char version[] = "";
char tags[] = "";
char images[] = "";
char videos[] = "";
char web_page[] = "";
char members[] = "";

int debug = 0;

const char* char_pointer;
char* char_self_pointer;

char string[] = "";
int integer = "";

char counter[] = "aaaaa"; //
int counter = 1;
int login = 0;
//counter[] ;

int interface; // 0 - Main Menu , 1 - character creation

interface = 0;

int some_var = 13;
char str1[20];

char *structure_pointer;

size_t size //is an unsigned type. So, it cannot represent any negative values(<0). You use it when you are counting something, and are sure that it cannot be negative.

unsigned char *unsigned_char_pointer;

static unsigned int   current_msec      = 0UL; // Graph app

/*
 *  Private platform-specific declarations:
 */

#ifndef APP_PRIVATE_DECLARATIONS

  /*
   *  This ensures we have no incomplete types.
   *  Some compilers dislike incomplete types.
   */

  #define AppExtra       void
  #define WindowExtra    void
  #define BitmapExtra    void
  #define GraphicsExtra  void
  #define SubfontExtra   void
  #define FontExtra      void
  #define FolderExtra    void
  #define CursorExtra    void

#endif /* APP_PRIVATE_DECLARATIONS */

array(int pos, char value){

/*
    int counter_1 = 0;
    int counter_2  = 0;
    int counter_3  = 0;

    char counter_4[10];

    int debug = 1; // 1 true, 0 false
*/

    int arr[100] = { 0 }; 
    int i, x, pos, n = 10; 
  
    // initial array of size 10 
    for (i = 0; i < 10; i++) 
        arr[i] = i + 1; 
  
    // print the original array 
    for (i = 0; i < n; i++) 
        printf("%d ", arr[i]); 
    printf("\n"); 
  
    // element to be inserted 
    x = 50; 
  
    // position at which element 
    // is to be inserted 
    pos = 5; 
  
    // increase the size by 1 
    n++; 
  
    // shift elements forward 
    for (i = n; i >= pos; i--) 
        arr[i] = arr[i - 1]; 
  
    // insert x at pos 
    arr[pos - 1] = x; 
  
    // print the updated array 
    for (i = 0; i < n; i++) 
        printf("%d ", arr[i]); 
    printf("\n"); 
  
    return 0; 
}


/*  Associations are a way of storing extra pointers with
 *  controls, windows and other objects. There isn't space
 *  inside the objects themselves to store the pointer,
 *  so we store them in a linked list, which uses the
 *  object's pointer as a lookup key.
 */

typedef struct Association  Association;

struct Association {
  Association * next;
  Association * prev;
  void *        key;
  int           kind;
  void *        data;
};

enum {
	ASSOC_ALL = 0,
	ASSOC_HIT,
	ASSOC_REDRAW,
	ASSOC_RESIZE,
	ASSOC_DATA,
	ASSOC_CMAP,
	ASSOC_TIMER
};

static Association * assoc_list = NULL;

static void del_association(void *key, int kind)
{
	Association *a, *next;

	a = assoc_list;
	do {
		if (a == NULL)
			return;
		next = a->next;
		if ( (a->key == key)
		  && ((kind == ASSOC_ALL) || (a->kind == kind)) )
		{
			if (a == assoc_list)
				assoc_list = a->next;
			if (a->next == a->prev)
				assoc_list = next = NULL;
			a->next->prev = a->prev;
			a->prev->next = a->next;
			app_free(a);
		}
		a = next;
	} while (a != assoc_list);
}

static void add_association(void *key, int kind, void *data)
{
	Association *a;

	del_association(key, kind);

	a = app_alloc(sizeof(Association));
	a->key = key;
	a->kind = kind;
	a->data = data;

	if (assoc_list == NULL) {
		assoc_list = a;
		a->next = a->prev = a;
	}
	else {
		a->next = assoc_list;
		a->prev = a->next->prev;
		a->next->prev = a;
		a->prev->next = a;
	}
}

static void * get_association(void *key, int kind)
{
	Association *a;

	a = assoc_list;
	if (a == NULL)
		return NULL;
	do {
		if ((a->key == key) && (a->kind == kind))
			return a->data;
		a = a->next;
	} while (a != assoc_list);
	return NULL;
}




