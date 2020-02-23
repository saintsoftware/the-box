
#include "mysql/mysql.h"
#include <my_global.h>

// ========== DECLARATION =================

extern char database_name[];
extern char database_password[];
extern char database_user[];
extern char database_host[];
extern char *database_connection;
extern char database_extension;

extern int database_column;
extern int database_row;
extern int database_ret;
extern int database_size;



char database;


char database_rows[];

int database_started;
database_started=0;

//databases_get_memstat /* TODO: memstat */

const char* database_query;
const char* str;
sqlite3* self;
LIArcPacket* packet;
LIScrData* data;
sqlite3_stmt* statement;

char database_errors[] = "database not initiate", "extension", database_extension ;
	
database_name = "box";
database_password = "";
database_user = "test";
database_host = "localhost";
database_extension = "mysql"; //mysql, sqlite3,

//static void Database_get_memory_used (LIScrArgs* args){ liscr_args_seti_int (args, sqlite3_memory_used ());}


//void database_create (LIScrScript* self){}
	
insert_cfunc (self, LIEXT_SCRIPT_DATABASE, "database_get_memory_used", Database_get_memory_used);
insert_cfunc (self, LIEXT_SCRIPT_DATABASE, "database_new", Database_new);
insert_mfunc (self, LIEXT_SCRIPT_DATABASE, "database_query", Database_query);






