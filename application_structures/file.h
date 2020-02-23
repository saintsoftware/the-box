
/* 
 FSEEK() FUNCTION
 
int fseek(FILE *stream, long int offset, int whence)

SEEK_SET
Beginning of file
SEEK_CUR
Current position of the file pointer
SEEK_END
End of file


fseek( file pointer , 7, SEEK_SET );
*/

//#define LIEXT_SCRIPT_FILE "File"

//#include <string.h> // File open

/*
	Create File
	Delete File
	Copy File
	
*/

// ========== DECLARATION =================


//#define LIEXT_SCRIPT_FILE "File"

#include <string.h> // File open
#include <stdio.h>
#include <dirent.h>
#include<stdio.h>
#include<conio.h>
#include<process.h>

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
/* "readdir" etc. are defined here. */
#include <dirent.h>
/* limits.h defines "PATH_MAX". */
#include <limits.h>

// ========== DECLARATION =================
/*
//FILE *file_open; // fopen("woman.jpg", "rb");
//size_t string_lenght;
char *string;
extern char file_name;
//extern const char* file_name;
extern int lenght;
extern char* path_absolute;

extern const char* buffer;
//extern LIArcReader* reader;
//extern LIExtModule* module;
//extern LISysDir* dir;
extern int count;
char* path_abs;
const char* path;
const char* data;
//LIArcWriter* writer;
//LIExtModule* module;
//extern const char* path;
*/
//printf("Enter interface : %s", a);
//printf("%s", counter_4);

//FILE *file_open; // fopen("woman.jpg", "rb");

char *string;
char file_name;
char file_path;
char file_extension;
char file_types[][];

//extern const char* file_name;
extern int lenght;
extern char* path_absolute;
extern const char* file_path;
extern const char* buffer;
qboolean      file_open;
fileHandle_t  file_handle;
char          file_name[ MAX_QPATH ];
int           file_size;

FILE *f_ro;
FILE *f_doc;
FILE *f_path;
FILE *f_type;
FILE *f_pwd;
FILE * FILE_pointer; // FILE is a default structure that holds the information on the file, in order to work with files. Requires stdio.h, scanf printf

//extern LIArcReader* reader;
//extern LIExtModule* module;
//extern LISysDir* dir;
extern int count;
char* path_abs;
const char* path;
const char* data;

unsigned char *result;

char file_path[];
DIR *diectory_path;

open_folder[] = "";

//Writer* writer;
//Module* module;
//extern const char* path;

//printf("Enter interface : %s", a);
//printf("%s", counter_4);

//*stream; // − This is the pointer to a FILE object that identifies the stream.



int i,j,ch;
char fn[20],e,c;
FILE *fp1,*fp2,*fp;

// ========== Functions =================

void file_create();
void file_append();
void file_copy();
void file_delete_();
void file_display();

typedef struct Folder         Folder;

  struct Folder {
	int             id;                 /* directory identifier */
  };


/*
 *  Resources:
 */

FILE *	app_open_resource(const char *file_name, const char *resource, long *length);
int 	app_file_has_resources(const char *file_name);


valid_file(){
	
}

int open_file(){
	
	if (! valid_file(w, "Choose a file to open first!")){
		return 0;
	}
}


/*
 *  UTF-8 and ISO-Latin-1:
 */

#define IS_UTF8_EXTRA_BYTE(b) (((b)&0xC0)==0x80)

/*
 * Both of these routines converts the text between *sourceStart
 * and sourceEnd, putting the result into the buffer between *targetStart
 * and targetEnd. Note: the end pointers are *after* the last item:
 * i.e. *(sourceEnd - 1) is the last item.
 *
 * The return result indicates whether the conversion was successful,
 * and if not, whether the problem was in the source or target buffers.
 *
 * After the conversion, *sourceStart and *targetStart are both
 * updated to point to the end of last text successfully converted in
 * the respective buffers.
 */

typedef enum UTF8ConversionResult {
	ConversionSuccess = 0, 	/* conversion successful */
	SourceExhausted = 1,	/* partial char in source, but hit end */
	SourceCorrupt = 2,	/* corrupted character in source */
	TargetExhausted = 4	/* no room in target for conversion */
} ConversionResult;		/* bit-field holding conversion result */

int app_unicode_to_utf8(const Char ** source_start, const Char * source_end,
			      char ** target_start, const char * target_end);

int app_utf8_to_unicode(const char ** source_start, const char * source_end,
			      Char ** target_start, const Char * target_end);

int 	app_unicode_char_to_utf8(Char ch, char *utf8);
Char	app_utf8_char_to_unicode(const char *utf8);
int 	app_utf8_length(const char *utf8);

/*
 *  Transfer Unicode value to/from UTF-8 or ISO-Latin-1 files.
 *  The file must be open in binary mode.
 */

int	app_read_utf8_char (FILE *f, Char *dst);

char *	app_read_latin1_file (FILE *f, long *nbytes, long *nchars);
char *	app_read_utf8_file (FILE *f, long *nbytes, long *nchars);

char *	app_read_latin1_line (FILE *f, long *nbytes, long *nchars);
char *	app_read_utf8_line (FILE *f, long *nbytes, long *nchars);

int	app_write_latin1 (FILE *f, const char *s, long nbytes);
int	app_write_utf8 (FILE *f, const char *s, long nbytes);

char *	app_utf8_to_latin1 (const char *s, int *bytes);
char *	app_correct_utf8 (const char *s, int *bytes);

int 	app_utf8_is_ascii(const char *utf8, long nbytes);
int 	app_utf8_is_latin1(const char *utf8, long nbytes);

/*
 *  UTF-8 regular expressions:
 */

int 	app_regex_match(const char *regexp, const char *text);

/*
 *  File and folder access:
 */

enum FileInfo {
	IS_APP    = 1,
	IS_WRITE  = 2,
	IS_READ   = 4,
	IS_FOLDER = 8,
	IS_FILE   = 16
};

FILE *	app_open_file(const char *filepath, const char *mode);
int 	app_close_file(FILE *f);
int 	app_remove_file(const char *filepath);
int 	app_rename_file(const char *oldpath, const char *newpath);

Folder *app_open_folder(const char *folderpath);
char *	app_read_folder(Folder *f);
int 	app_close_folder(Folder *f);
int 	app_make_folder(const char *folderpath, int mode);
int 	app_remove_folder(const char *folderpath);
int 	app_rename_folder(const char *oldpath, const char *newpath);

int 	app_file_info(const char *filepath);
long	app_file_size(const char *filepath);
long	app_file_time(const char *filepath);
char *	app_current_folder(void);
int 	app_set_current_folder(const char *folderpath);
char *	app_form_file_path(const char *folderpath, const char *filename);
char *	app_get_file_name(const char *filepath);

static void do_delete_file(MenuItem *m)
{
	Window *w = app_parent_window(m->parent->parent->ctrl);
	char * file;
	char * confirm;
	int info;

	if (! valid_file(w, "Choose a file to delete first!"))
		return;

	file = get_current_path(w);

	info = app_file_info(file);
	if (info & IS_FOLDER) {
		file = get_current_path(w);
		if (app_remove_folder(file) == 0)
			app_ask_ok(w->app, ERROR_STRING,
				"Error: couldn't remove that folder!");
		rescan_folder(m);
		return;
	}

	confirm = add_strings(NULL, "Delete the file \"");
	confirm = add_strings(confirm, app_get_control_text(data(w)->filename));
	confirm = add_strings(confirm, "\" now?");

	if (app_ask_yes_no(w->app, QUESTION_STRING, confirm) == YES) {
		if (app_remove_file(file) == 0)
			app_ask_ok(w->app, ERROR_STRING,
				"Error: couldn't delete that file!");
		rescan_folder(m);
	}

	app_del_string(confirm);
}

/* List the files in "dir_name". */

static void list_dir (const char * dir_name)
{

    /* Open the directory specified by "dir_name". */

    DIR_pointer = opendir (dir_name);

    /* Check it was opened. */
    if (! d) {
        fprintf (stderr, "Cannot open directory '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }
	
    while (1) {
        struct dirent * entry;
        const char * d_name;

        /* "Readdir" gets subsequent entries from "d". */
        entry = readdir (d);
        if (! entry) {
            /* There are no more entries in this directory, so break
               out of the while loop. */
            break;
        }
        d_name = entry->d_name;
        /* Print the name of the file and directory. */
	printf ("%s/%s\n", dir_name, d_name);

#if 0
	/* If you don't want to print the directories, use the
	   following line: */

        if (! (entry->d_type & DT_DIR)) {
	    printf ("%s/%s\n", dir_name, d_name);
	}

#endif /* 0 */


        if (entry->d_type & DT_DIR) {

            /* Check that the directory is not "d" or d's parent. */
            
            if (strcmp (d_name, "..") != 0 &&
                strcmp (d_name, ".") != 0) {
                int path_length;
                char path[PATH_MAX];
 
                path_length = snprintf (path, PATH_MAX,
                                        "%s/%s", dir_name, d_name);
                printf ("%s\n", path);
                if (path_length >= PATH_MAX) {
                    fprintf (stderr, "Path length has got too long.\n");
                    exit (EXIT_FAILURE);
                }
                /* Recursively call "list_dir" with the new path. */
                list_dir (path);
            }
	}
    }
    /* After going through all the entries, close the directory. */
    if (closedir (d)) {
        fprintf (stderr, "Could not close '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }
}

void file_create()
{
	
fp1=fopen("temp.txt","w");
printf("\n\tEnter the text and press '.' to save\n\n\t");

	while(1)
	{
		c=getchar();
		fputc(c,fp1);
		if(c == '.')
		{
			fclose(fp1);
			break;
		}
	}

}
 
void file_display()
{
	printf("\n\tEnter the file name: ");
	scanf("%s",fn);
	fp1=fopen(fn,"r");

	if(fp1==NULL)
	{
	printf("\n\tFile not found!");
	goto end1;
	}

	while(!feof(fp1))
	{
		
	c=getc(fp1);
	printf("%c",c);
	}

	end1:
	fclose(fp1);
	printf("\n\n\tPress any key to continue\n");
	getch();
}

void file_copy()
{
	printf("\n\tEnter the new file name to copy:  ");
	scanf("%s",fn);
	
	fp1=fopen("temp.txt","r");
	fp2=fopen(fn,"w");
	
	while(!feof(fp1))
	{
		c=getc(fp1);
		putc(c,fp2);
	}
	
	fclose(fp2);
}
 
void delete_file()
{
	
	printf("\n\tEnter the file name: ");
	scanf("%s",fn);
	fp1=fopen(fn,"r");

	if(fp1==NULL)
	{
		printf("\n\tFile not found!");
		goto end2;
	}

	fclose(fp1);

	if(remove(fn)==0)
	{
		printf("\n\n\tFile has been deleted successfully!");
		goto end2;
	}
	else
		printf("\n\tError!\n");
		end2: printf("\n\n\tPress any key to continue\n");
		getch();
}
 
void Append()
{
	
	printf("\n\tEnter the file name: ");
	scanf("%s",fn);
	fp1=fopen(fn,"r");

	if(fp1==NULL)
	{
		printf("\n\tFile not found!");
		fclose(fp1);
		goto end3;
	}

	while(!feof(fp1))
	{
		c=getc(fp1);
		printf("%c",c);
	}
	
	fclose(fp1);
	printf("\n\tType the text and press Ctrl+S to append.\n");
	fp1=fopen(fn,"a");

	while(1)
	{
		c=getch();

	if(c==19)
	goto end3;
	if(c==13)
	{
		c='\n';
		printf("\n\t");
		fputc(c,fp1);
	}
	else
	{
		printf("%c",c);
		fputc(c,fp1);
	}
	}
	
	end3: fclose(fp1);
	 
	getch();
}

int deletedoc(char id[10]){
	
 struct Doctor doc;
 int n,i,y;
 n=getFileElement(_doct,sizeof(Doctor));
 f_doc=fopen(_doct,"rb+");
 rewind(f_doc);
 FILE *temp = fopen("TEMP","wb+");
 
 for(i=0; i<n; i++) {
  fread(&doc,sizeof(Doctor),1,f_doc);
  if(strcmp(doc.id,id)!=0) {
   fwrite(&doc,sizeof(Doctor),1,temp);
  }
 }
 
 fclose(temp);
 fclose(f_doc);
 remove(_doct);
 rename("TEMP",_doct);
 y=1;
 
end:
 return y;
}

/**************************************************************
 * A simpler and shorter implementation of ls(1)
 * ls(1) is very similar to the DIR command on DOS and Windows.
 **************************************************************/
 

int list_directory(const char *path)
{
  struct dirent *entry;
  DIR *dp;

  dp = opendir(path);
  if (dp == NULL)
  {
    perror("opendir");
    return -1;
  }

  while((entry = readdir(dp)))
    puts(entry->d_name);

  closedir(dp);
  return 0;
}

//int main(int argc, char **argv) {
	


if (argc == 1)
listdir(".");

while (++counter <= argc) {
printf("\nListing %s...\n", argv[counter-1]);
listdir(argv[counter-1]);
}

void get_string(){
 //args, 0, &path
 //return 1;
}





// https://forgetcode.com/C/112-Text-Editor-in-system-software

/* Para file -> code editor -> file browser. */


void Create()
{
	
fp1=fopen("temp.txt","w");
printf("\n\tEnter the text and press '.' to save\n\n\t");

	while(1)
	{
		c=getchar();
		fputc(c,fp1);
		if(c == '.')
		{
			fclose(fp1);
			break;
		}
	}

}
 
void display()
{
	
	printf("\n\tEnter the file name: ");
	scanf("%s",fn);
	fp1=fopen(fn,"r");

	if(fp1==NULL)
	{
	printf("\n\tFile not found!");
	goto end1;
	}

	while(!feof(fp1))
	{
		
	c=getc(fp1);
	printf("%c",c);
	}

	end1:
	fclose(fp1);
	printf("\n\n\tPress any key to continue\n");
	getch();
}

void copy_file()
{
	printf("\n\t Enter the new file name to copy:  ");
	scanf("%s",fn);
	fp1 = fopen("temp.txt","r");
	fp2 = fopen(fn,"w");
	
	while(!feof(fp1))
	{
	c=getc(fp1);
	putc(c,fp2);
	}
	
	fclose(fp2);
}
 
void delete_file()
{
	
	printf("\n\tEnter the file name: ");
	scanf("%s",fn);
	fp1=fopen(fn,"r");

	if(fp1==NULL)
	{
		printf("\n\tFile not found!");
		goto end2;
	}

	fclose(fp1);

	if(remove(fn)==0)
	{
		printf("\n\n\tFile has been deleted successfully!");
		goto end2;
	}
	else
		printf("\n\tError!\n");
		end2: printf("\n\n\tPress any key to continue\n");
		getch();
}
 
void Append()
{
	
	printf("\n\tEnter the file name: ");
	scanf("%s",fn);
	fp1=fopen(fn,"r");

	if(fp1==NULL)
	{
		printf("\n\tFile not found!");
		fclose(fp1);
		goto end3;
	}

	while(!feof(fp1))
	{
		c=getc(fp1);
		printf("%c",c);
	}
	
	fclose(fp1);
	printf("\n\tType the text and press Ctrl+S to append.\n");
	fp1=fopen(fn,"a");

	while(1)
	{
		c=getch();

	if(c==19)
	goto end3;
	if(c==13)
	{
		c='\n';
		printf("\n\t");
		fputc(c,fp1);
	}
	else
	{
		printf("%c",c);
		fputc(c,fp1);
	}
	}
	
	end3: fclose(fp1);
	 
	getch();
}



/*
return 0;

using namespace std;

int wmain()
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

    //open C:\Windows in Explorer

        CreateProcess
        (
        TEXT("c:\\WINDOWS\\system32\\explorer.exe"),
        " C:\\Windows",NULL,NULL,FALSE,
        CREATE_NEW_CONSOLE,
        NULL,NULL,
        &si,
        &pi
        );
        return 0;
}
*/

struct dirent *de;  // Pointer for directory entry



// opendir() returns a pointer of DIR type.
DIR *directory = opendir("."); // ("./");

if (directory == NULL)  // opendir returns NULL if couldn't open directory
{
    printf("Could not open current directory");
    return 0;
}

// Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
// for readdir()

while ((de = readdir(dr)) != NULL) {
    printf("%s\n", de -> d_name);
}


if (dr)
{
    while ((dir = readdir(d)) != NULL)
    {
        printf("%s\n", dir->d_name);
    }
    closedir(d);
}

closedir(dr);

//return 0;

/* Header */

tinydir_dir dir;
tinydir_open(&dir, "/path/to/dir");

while (dir.has_next)
{
    tinydir_file file;
    tinydir_readfile(&dir, &file);

    printf("%s", file.name);
    if (file.is_dir)
    {
        printf("/");
    }
    printf("\n");

    tinydir_next(&dir);
}

tinydir_close(&dir);


insert_cfunc (self, LIEXT_SCRIPT_FILE, "file_read", File_read);
insert_cfunc (self, LIEXT_SCRIPT_FILE, "file_scan_directory", File_scan_directory);
insert_cfunc (self, LIEXT_SCRIPT_FILE, "file_scan_save_directory", File_scan_save_directory);
insert_cfunc (self, LIEXT_SCRIPT_FILE, "file_write", File_write);



//static int stdio_read(void *user, char *data, int size){
	
fread(data, 1, size, (FILE*) user);

//static void stdio_skip(void *user, int n){
	
fseek( (FILE*) user, n, SEEK_CUR );


//static int stdio_eof(void *user)

 feof((FILE*) user);



static void stbi__start_file(stbi__context *s, FILE *f)
{
   stbi__start_callbacks(s, &stbi__stdio_callbacks, (void *) f);
}

static void stop_file(stbi__context *s) { }


STBIDEF float *stbi_loadf            (char const *filename, int *x, int *y, int *channels_in_file, int desired_channels);
STBIDEF float *stbi_loadf_from_file  (FILE *f, int *x, int *y, int *channels_in_file, int desired_channels);

STBIDEF us *stbi_load_16          (char const *filename, int *x, int *y, int *channels_in_file, int desired_channels);
STBIDEF us *stbi_load_from_file_16(FILE *f, int *x, int *y, int *channels_in_file, int desired_channels);


STBIDEF int      info               (char const *filename,     int *x, int *y, int *comp);
STBIDEF int      info_from_file     (FILE *f,                  int *x, int *y, int *comp);
STBIDEF int      is_16_bit          (char const *filename);
STBIDEF int      is_16_bit_from_file(FILE *f);


#ifndef NO_STDIO

static FILE *stbi__fopen(char const *filename, char const *mode)
{
   FILE *f;
#if defined(_MSC_VER) && _MSC_VER >= 1400
   if (0 != fopen_s(&f, filename, mode))
      f=0;
#else
   f = fopen(filename, mode);
#endif
   return f;
}


   FILE_pointer = fopen(filename, "rb");
   
   if (!FILE_pointer){
		return error("can't fopen", "Unable to open file");
   } 
   
   result = load_from_file(f,x,y,comp,req_comp);
   fclose(f);


DEF stbi_uc *load_from_file(FILE *f, int *x, int *y, int *comp, int req_comp)
{
   unsigned char *result;
   stbi__context s;
   stbi__start_file(&s,f);
   result = stbi__load_and_postprocess_8bit(&s,x,y,comp,req_comp);
   if (result) {
      // need to 'unget' all the characters in the IO buffer
      fseek(f, - (int) (s.img_buffer_end - s.img_buffer), SEEK_CUR);
   }
   return result;
}

DEF uint16 *load_from_file_16(FILE *f, int *x, int *y, int *comp, int req_comp){
	
   stbi__uint16 *result;
   stbi__context s;
   stbi__start_file(&s,f);
   result = stbi__load_and_postprocess_16bit(&s,x,y,comp,req_comp);
   if (result) {
      // need to 'unget' all the characters in the IO buffer
      fseek(f, - (int) (s.img_buffer_end - s.img_buffer), SEEK_CUR);
   }
   return result;
}

STBIDEF stbi_us *stbi_load_16(char const *filename, int *x, int *y, int *comp, int req_comp)
{
   FILE *f = stbi__fopen(filename, "rb");
   stbi__uint16 *result;
   if (!f) return (stbi_us *) stbi__errpuc("can't fopen", "Unable to open file");
   result = stbi_load_from_file_16(f,x,y,comp,req_comp);
   fclose(f);
   return result;
}

STBIDEF float *stbi_loadf(char const *filename, int *x, int *y, int *comp, int req_comp)
{
   float *result;
   FILE *f = stbi__fopen(filename, "rb");
   if (!f) return stbi__errpf("can't fopen", "Unable to open file");
   result = stbi_loadf_from_file(f,x,y,comp,req_comp);
   fclose(f);
   return result;
}

STBIDEF float *loadf_from_file(FILE *f, int *x, int *y, int *comp, int req_comp)
{
   stbi__context s;
   stbi__start_file(&s,f);
   return stbi__loadf_main(&s,x,y,comp,req_comp);
}


void construct_path (){ /* Construct the path. */



	//module = userdata (args->script, LIEXT_SCRIPT_FILE);
    /*
	if (!get_string ()){
		return;
	}

	for (counter_1 = 0 ; counter_1 < strlen (path) ; counter_1++){
		if ((path[counter_1] < 'a' || path[counter_1] > 'z') && (path[counter_1] < '0' || path[counter_1] > '9') &&
		    (path[counter_1] != '/' && path[counter_1] != '.' && path[counter_1] != '-' && path[counter_1] != '_')){
			return;
		}
	}
	*/
}

/*
typedef struct _LIExtModule LIExtModule;
struct _LIExtModule
{
	LIMaiProgram* program;
};

LIExtModule* liext_file_new (
	LIMaiProgram* program);

void liext_file_free (
	LIExtModule* self);

void liext_file_get_memstat (
	LIExtModule*  self,
	LIMaiMemstat* stat);

void liext_script_file (
	LIScrScript* self);


liext_file_info =
{
	LIMAI_EXTENSION_VERSION, "File",
	liext_file_new,
	liext_file_free,
	liext_file_get_memstat
};


LIExtModule* file_new (LIMaiProgram* program){
	LIExtModule* self;

	/* Allocate self.
	self = lisys_calloc (1, sizeof (LIExtModule));
	if (self == NULL)
		return NULL;
	self->program = program;

	/* Register classes.
	liscr_script_set_userdata (program->script, LIEXT_SCRIPT_FILE, self);
	liext_script_file (program->script);

	return self;
}

void liext_file_free (LIExtModule* self){
	lisys_free (self);
}



static void File_read (LIScrArgs* args){

	path_abs = lisys_path_concat (module->program->paths->module_data, path, NULL);

	/* Open the file.

	/* TODO: Also support additions in the home directory.

	reader = liarc_reader_new_from_file (path_abs);
	lisys_free (path_abs);
	if (reader == NULL)
		return;

	/* Return the file contents.
	len = reader->length;
	buf = reader->buffer;
	if (buf != NULL)
	{
		lua_pushlstring (args->lua, buf, len);
		liscr_args_seti_stack (args);
	}
	liarc_reader_free (reader);
}

static void File_scan_directory (LIScrArgs* args)
{

	/* Construct the path.
	module = liscr_script_get_userdata (args->script, LIEXT_SCRIPT_FILE);
	if (!liscr_args_geti_string (args, 0, &path))
		return;
	if (strstr (path, ".."))
		return;
	for (i = 0 ; i < strlen (path) ; i++)
	{
		if ((path[i] < 'a' || path[i] > 'z') && (path[i] < '0' || path[i] > '9') &&
		    (path[i] != '/' && path[i] != '.' && path[i] != '-' && path[i] != '_'))
			return;
	}
	path_abs = lisys_path_concat (module->program->paths->module_data, path, NULL);

	/* Scan the directory.
	/* TODO: Also support additions in the home directory.
	dir = lisys_dir_open (path_abs);
	lisys_free (path_abs);
	if (dir == NULL)
		return;
	lisys_dir_set_sorter (dir, lisys_dir_sorter_alpha);
	if (!lisys_dir_scan (dir))
	{
		lisys_dir_free (dir);
		return;
	}

	/* Return the file names.
	liscr_args_set_output (args, LISCR_ARGS_OUTPUT_TABLE_FORCE);
	count = lisys_dir_get_count (dir);
	for (i = 0 ; i < count ; i++)
	{
		name = lisys_dir_get_name (dir, i);
		if (name[0] != '.')
			liscr_args_seti_string (args, name);
	}

	lisys_dir_free (dir);
}

static void File_write (LIScrArgs* args)
{
	/* Construct the path.
	module = liscr_script_get_userdata (args->script, LIEXT_SCRIPT_FILE);
	if (!liscr_args_geti_string (args, 0, &path) ||
	    !liscr_args_geti_string (args, 1, &data))
		return;
	for (i = 0 ; i < strlen (path) ; i++)
	{
		if ((path[i] < 'a' || path[i] > 'z') && (path[i] < '0' || path[i] > '9') &&
		    (path[i] != '/' && path[i] != '.' && path[i] != '-' && path[i] != '_'))
			return;
	}
	path_abs = lisys_path_concat (module->program->paths->module_data, path, NULL);

	/* Open the file.
	/* TODO: Also support additions in the home directory.
	writer = liarc_writer_new_file (path_abs);
	lisys_free (path_abs);
	if (writer == NULL)
		return;

	/* Write the file contents.
	if (liarc_writer_append_string (writer, data))
		liscr_args_seti_bool (args, 1);
		liarc_writer_free (writer);
}

/**
 * \brief Gets the memory statistics of the module.
 * \param self Module.
 * \param stat Return location for the stats.
 *


fwrite(row[0], lengths[0], 1, fp);

if (ferror(fp))
{
    fprintf(stderr, "fwrite() failed\n");
    mysql_free_result(result);
    mysql_close(con);

    exit(1);
}
*/

/*

 FSEEK() FUNCTION
 
int fseek(FILE *stream, long int offset, int whence)

SEEK_SET
Beginning of file
SEEK_CUR
Current position of the file pointer
SEEK_END
End of file


fseek( file pointer , 7, SEEK_SET );
*/

//#define LIEXT_SCRIPT_FILE "File"



// ========== DECLARATION =================

//FILE *file_open; // fopen("woman.jpg", "rb");

//FILE * FILE_pointer; // FILE is a default structure that holds the information on the file, in order to work with files. Requires stdio.h, scanf printf

char *string;
extern char file_name;
//extern const char* file_name;
extern int lenght;
extern char* path_absolute;
extern const char* file_path;
extern const char* buffer;
//extern LIArcReader* reader;
//extern LIExtModule* module;
//extern LISysDir* dir;
extern int count;
char* path_abs;
const char* path;
const char* data;

unsigned char *result;

//Writer* writer;
//Module* module;
//extern const char* path;

//printf("Enter interface : %s", a);
//printf("%s", counter_4);

//*stream; // − This is the pointer to a FILE object that identifies the stream.

void get_string(){
 //args, 0, &path
 //return 1;
}

insert_cfunc (self, LIEXT_SCRIPT_FILE, "file_read", File_read);
insert_cfunc (self, LIEXT_SCRIPT_FILE, "file_scan_directory", File_scan_directory);
insert_cfunc (self, LIEXT_SCRIPT_FILE, "file_scan_save_directory", File_scan_save_directory);
insert_cfunc (self, LIEXT_SCRIPT_FILE, "file_write", File_write);



//static int stdio_read(void *user, char *data, int size){
	
fread(data, 1, size, (FILE*) user);

//static void stdio_skip(void *user, int n){
	
fseek( (FILE*) user, n, SEEK_CUR );


//static int stdio_eof(void *user)

 feof((FILE*) user);



static void stbi__start_file(stbi__context *s, FILE *f)
{
   stbi__start_callbacks(s, &stbi__stdio_callbacks, (void *) f);
}

static void stop_file(stbi__context *s) { }


STBIDEF float *stbi_loadf            (char const *filename, int *x, int *y, int *channels_in_file, int desired_channels);
STBIDEF float *stbi_loadf_from_file  (FILE *f, int *x, int *y, int *channels_in_file, int desired_channels);

STBIDEF us *stbi_load_16          (char const *filename, int *x, int *y, int *channels_in_file, int desired_channels);
STBIDEF us *stbi_load_from_file_16(FILE *f, int *x, int *y, int *channels_in_file, int desired_channels);


STBIDEF int      info               (char const *filename,     int *x, int *y, int *comp);
STBIDEF int      info_from_file     (FILE *f,                  int *x, int *y, int *comp);
STBIDEF int      is_16_bit          (char const *filename);
STBIDEF int      is_16_bit_from_file(FILE *f);


#ifndef NO_STDIO

static FILE *stbi__fopen(char const *filename, char const *mode)
{
   FILE *f;
#if defined(_MSC_VER) && _MSC_VER >= 1400
   if (0 != fopen_s(&f, filename, mode))
      f=0;
#else
   f = fopen(filename, mode);
#endif
   return f;
}


   


DEF stbi_uc *load_from_file(FILE *f, int *x, int *y, int *comp, int req_comp)
{
   unsigned char *result;
   stbi__context s;
   stbi__start_file(&s,f);
   result = stbi__load_and_postprocess_8bit(&s,x,y,comp,req_comp);
   if (result) {
      // need to 'unget' all the characters in the IO buffer
      fseek(f, - (int) (s.img_buffer_end - s.img_buffer), SEEK_CUR);
   }
   return result;
}

DEF uint16 *load_from_file_16(FILE *f, int *x, int *y, int *comp, int req_comp){
	
   stbi__uint16 *result;
   stbi__context s;
   stbi__start_file(&s,f);
   result = stbi__load_and_postprocess_16bit(&s,x,y,comp,req_comp);
   if (result) {
      // need to 'unget' all the characters in the IO buffer
      fseek(f, - (int) (s.img_buffer_end - s.img_buffer), SEEK_CUR);
   }
   return result;
}

STBIDEF stbi_us *stbi_load_16(char const *filename, int *x, int *y, int *comp, int req_comp)
{
   FILE *f = stbi__fopen(filename, "rb");
   stbi__uint16 *result;
   if (!f) return (stbi_us *) stbi__errpuc("can't fopen", "Unable to open file");
   result = stbi_load_from_file_16(f,x,y,comp,req_comp);
   fclose(f);
   return result;
}

STBIDEF float *stbi_loadf(char const *filename, int *x, int *y, int *comp, int req_comp)
{
   float *result;
   FILE *f = stbi__fopen(filename, "rb");
   if (!f) return stbi__errpf("can't fopen", "Unable to open file");
   result = stbi_loadf_from_file(f,x,y,comp,req_comp);
   fclose(f);
   return result;
}

STBIDEF float *loadf_from_file(FILE *f, int *x, int *y, int *comp, int req_comp)
{
   stbi__context s;
   stbi__start_file(&s,f);
   return stbi__loadf_main(&s,x,y,comp,req_comp);
}


void construct_path (){ /* Construct the path. */



	//module = userdata (args->script, LIEXT_SCRIPT_FILE);
    /*
	if (!get_string ()){
		return;
	}

	for (counter_1 = 0 ; counter_1 < strlen (path) ; counter_1++){
		if ((path[counter_1] < 'a' || path[counter_1] > 'z') && (path[counter_1] < '0' || path[counter_1] > '9') &&
		    (path[counter_1] != '/' && path[counter_1] != '.' && path[counter_1] != '-' && path[counter_1] != '_')){
			return;
		}
	}
	*/
}

/*
typedef struct _LIExtModule LIExtModule;
struct _LIExtModule
{
	LIMaiProgram* program;
};

LIExtModule* liext_file_new (
	LIMaiProgram* program);

void liext_file_free (
	LIExtModule* self);

void liext_file_get_memstat (
	LIExtModule*  self,
	LIMaiMemstat* stat);

void liext_script_file (
	LIScrScript* self);


liext_file_info =
{
	LIMAI_EXTENSION_VERSION, "File",
	liext_file_new,
	liext_file_free,
	liext_file_get_memstat
};


LIExtModule* file_new (LIMaiProgram* program){
	LIExtModule* self;

	/* Allocate self.
	self = lisys_calloc (1, sizeof (LIExtModule));
	if (self == NULL)
		return NULL;
	self->program = program;

	/* Register classes.
	liscr_script_set_userdata (program->script, LIEXT_SCRIPT_FILE, self);
	liext_script_file (program->script);

	return self;
}

void liext_file_free (LIExtModule* self){
	lisys_free (self);
}



static void File_read (LIScrArgs* args){

	path_abs = lisys_path_concat (module->program->paths->module_data, path, NULL);

	/* Open the file.

	/* TODO: Also support additions in the home directory.

	reader = liarc_reader_new_from_file (path_abs);
	lisys_free (path_abs);
	if (reader == NULL)
		return;

	/* Return the file contents.
	len = reader->length;
	buf = reader->buffer;
	if (buf != NULL)
	{
		lua_pushlstring (args->lua, buf, len);
		liscr_args_seti_stack (args);
	}
	liarc_reader_free (reader);
}

static void File_scan_directory (LIScrArgs* args)
{

	/* Construct the path.
	module = liscr_script_get_userdata (args->script, LIEXT_SCRIPT_FILE);
	if (!liscr_args_geti_string (args, 0, &path))
		return;
	if (strstr (path, ".."))
		return;
	for (i = 0 ; i < strlen (path) ; i++)
	{
		if ((path[i] < 'a' || path[i] > 'z') && (path[i] < '0' || path[i] > '9') &&
		    (path[i] != '/' && path[i] != '.' && path[i] != '-' && path[i] != '_'))
			return;
	}
	path_abs = lisys_path_concat (module->program->paths->module_data, path, NULL);

	/* Scan the directory.
	/* TODO: Also support additions in the home directory.
	dir = lisys_dir_open (path_abs);
	lisys_free (path_abs);
	if (dir == NULL)
		return;
	lisys_dir_set_sorter (dir, lisys_dir_sorter_alpha);
	if (!lisys_dir_scan (dir))
	{
		lisys_dir_free (dir);
		return;
	}

	/* Return the file names.
	liscr_args_set_output (args, LISCR_ARGS_OUTPUT_TABLE_FORCE);
	count = lisys_dir_get_count (dir);
	for (i = 0 ; i < count ; i++)
	{
		name = lisys_dir_get_name (dir, i);
		if (name[0] != '.')
			liscr_args_seti_string (args, name);
	}

	lisys_dir_free (dir);
}

static void File_write (LIScrArgs* args)
{
	/* Construct the path.
	module = liscr_script_get_userdata (args->script, LIEXT_SCRIPT_FILE);
	if (!liscr_args_geti_string (args, 0, &path) ||
	    !liscr_args_geti_string (args, 1, &data))
		return;
	for (i = 0 ; i < strlen (path) ; i++)
	{
		if ((path[i] < 'a' || path[i] > 'z') && (path[i] < '0' || path[i] > '9') &&
		    (path[i] != '/' && path[i] != '.' && path[i] != '-' && path[i] != '_'))
			return;
	}
	path_abs = lisys_path_concat (module->program->paths->module_data, path, NULL);

	/* Open the file.
	/* TODO: Also support additions in the home directory.
	writer = liarc_writer_new_file (path_abs);
	lisys_free (path_abs);
	if (writer == NULL)
		return;

	/* Write the file contents.
	if (liarc_writer_append_string (writer, data))
		liscr_args_seti_bool (args, 1);
		liarc_writer_free (writer);
}

/**
 * \brief Gets the memory statistics of the module.
 * \param self Module.
 * \param stat Return location for the stats.
 *


fwrite(row[0], lengths[0], 1, fp);

if (ferror(fp))
{
    fprintf(stderr, "fwrite() failed\n");
    mysql_free_result(result);
    mysql_close(con);

    exit(1);
}
*/



void get_string(){
 //args, 0, &path
 //return 1;
}



void construct_path (){ /* Construct the path. */



	//module = userdata (args->script, LIEXT_SCRIPT_FILE);
    /*
	if (!get_string ()){
		return;
	}

	for (counter_1 = 0 ; counter_1 < strlen (path) ; counter_1++){
		if ((path[counter_1] < 'a' || path[counter_1] > 'z') && (path[counter_1] < '0' || path[counter_1] > '9') &&
		    (path[counter_1] != '/' && path[counter_1] != '.' && path[counter_1] != '-' && path[counter_1] != '_')){
			return;
		}
	}
	*/
}

/*
typedef struct _LIExtModule LIExtModule;
struct _LIExtModule
{
	LIMaiProgram* program;
};

LIExtModule* liext_file_new (
	LIMaiProgram* program);

void liext_file_free (
	LIExtModule* self);

void liext_file_get_memstat (
	LIExtModule*  self,
	LIMaiMemstat* stat);

void liext_script_file (
	LIScrScript* self);


liext_file_info =
{
	LIMAI_EXTENSION_VERSION, "File",
	liext_file_new,
	liext_file_free,
	liext_file_get_memstat
};


LIExtModule* file_new (LIMaiProgram* program){
	LIExtModule* self;

	/* Allocate self.
	self = lisys_calloc (1, sizeof (LIExtModule));
	if (self == NULL)
		return NULL;
	self->program = program;

	/* Register classes.
	liscr_script_set_userdata (program->script, LIEXT_SCRIPT_FILE, self);
	liext_script_file (program->script);

	return self;
}

void liext_file_free (LIExtModule* self){
	lisys_free (self);
}



static void File_read (LIScrArgs* args){

	path_abs = lisys_path_concat (module->program->paths->module_data, path, NULL);

	/* Open the file.

	/* TODO: Also support additions in the home directory.

	reader = liarc_reader_new_from_file (path_abs);
	lisys_free (path_abs);
	if (reader == NULL)
		return;

	/* Return the file contents.
	len = reader->length;
	buf = reader->buffer;
	if (buf != NULL)
	{
		lua_pushlstring (args->lua, buf, len);
		liscr_args_seti_stack (args);
	}
	liarc_reader_free (reader);
}

static void File_scan_directory (LIScrArgs* args)
{

	/* Construct the path.
	module = liscr_script_get_userdata (args->script, LIEXT_SCRIPT_FILE);
	if (!liscr_args_geti_string (args, 0, &path))
		return;
	if (strstr (path, ".."))
		return;
	for (i = 0 ; i < strlen (path) ; i++)
	{
		if ((path[i] < 'a' || path[i] > 'z') && (path[i] < '0' || path[i] > '9') &&
		    (path[i] != '/' && path[i] != '.' && path[i] != '-' && path[i] != '_'))
			return;
	}
	path_abs = lisys_path_concat (module->program->paths->module_data, path, NULL);

	/* Scan the directory.
	/* TODO: Also support additions in the home directory.
	dir = lisys_dir_open (path_abs);
	lisys_free (path_abs);
	if (dir == NULL)
		return;
	lisys_dir_set_sorter (dir, lisys_dir_sorter_alpha);
	if (!lisys_dir_scan (dir))
	{
		lisys_dir_free (dir);
		return;
	}

	/* Return the file names.
	liscr_args_set_output (args, LISCR_ARGS_OUTPUT_TABLE_FORCE);
	count = lisys_dir_get_count (dir);
	for (i = 0 ; i < count ; i++)
	{
		name = lisys_dir_get_name (dir, i);
		if (name[0] != '.')
			liscr_args_seti_string (args, name);
	}

	lisys_dir_free (dir);
}

static void File_write (LIScrArgs* args)
{
	/* Construct the path.
	module = liscr_script_get_userdata (args->script, LIEXT_SCRIPT_FILE);
	if (!liscr_args_geti_string (args, 0, &path) ||
	    !liscr_args_geti_string (args, 1, &data))
		return;
	for (i = 0 ; i < strlen (path) ; i++)
	{
		if ((path[i] < 'a' || path[i] > 'z') && (path[i] < '0' || path[i] > '9') &&
		    (path[i] != '/' && path[i] != '.' && path[i] != '-' && path[i] != '_'))
			return;
	}
	path_abs = lisys_path_concat (module->program->paths->module_data, path, NULL);

	/* Open the file.
	/* TODO: Also support additions in the home directory.
	writer = liarc_writer_new_file (path_abs);
	lisys_free (path_abs);
	if (writer == NULL)
		return;

	/* Write the file contents.
	if (liarc_writer_append_string (writer, data))
		liscr_args_seti_bool (args, 1);
		liarc_writer_free (writer);
}

/**
 * \brief Gets the memory statistics of the module.
 * \param self Module.
 * \param stat Return location for the stats.
 *

void file_get_memstat (LIExtModule*  self,LIMaiMemstat* stat){
// TODO: memstat
}

fwrite(row[0], lengths[0], 1, fp);

if (ferror(fp))
{
    fprintf(stderr, "fwrite() failed\n");
    mysql_free_result(result);
    mysql_close(con);

    exit(1);
}
*/
