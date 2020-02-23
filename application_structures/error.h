
/*
	Error Object, to have a error available to all code. 
	
	Functionality :
	- (used in: standard games, social tool)
	- 
	- 
	- Files (project/errors.txt)
	
	Inherit :
	none
	
	Notes :
*/

// ========== DECLERATION =================

extern char error[];
extern char error_name[];
extern char error_file[];
extern int error_line[];
extern int error_assert[];
extern int error_lenght[];
extern char error_function[];
extern char error_memory[];
extern char assert[];
char error_mensage = "unknoned error";

extern int type;
extern int data;
extern int pos;
extern int type;
extern char tmp;
extern char text;

char errors[][] ;

//static pthread_once_t private_once = PTHREAD_ONCE_INIT;
//static void private_init ();
//static void private_free (void* data);
//static LISysError* private_get ();
//static pthread_key_t private_key;



// DEFINITION


int error_assert = 0;
int ERROR_LENGTH = 2048;
char error_assert;

int data;
int data_type;
int data_pos;
char tmp[LISYS_ERROR_LENGTH];
char text[LISYS_ERROR_LENGTH];

static pthread_once_t private_once = PTHREAD_ONCE_INIT;
static void private_init ();
static void private_free (void* data);
static LISysError* private_get ();

static pthread_key_t private_key;



void error_build(){
	
	if (debug == 1){
		error_file = "";
		error_line = "";
		error_function = "";
		error_mensage = "";
		
		
	}
	
	strcpy(error, "error in file");
	strcat(error, error_file);
	strcat(error, "on line");
	strcat(error, error_line);
	strcat(error, "on fuction");
	strcat(error, error_function);
	strcat(error, "gives this error");
	strcat(error, error_mensage);

	LIAPICALL (void, lisys_assert_fail, (
	const char* asrt,
	const char* file,
	int         line,
	const char* func));
	
}
 
void assert_error (){ // Program Crached
	
}

/**
 * \brief Appends a consequence to a previous error.
 * \param format Format string for error detail.
 * \param ... Variable argument list appropriate to the format string.
 */

 void error_append (const char* format, ...)
{
	int num;
	va_list args;
	LISysError* data;

	/* Get thread specific data. */
	data = private_get ();
	if (data == NULL)
		return;

	/* Append separator. */
	if (data->pos >= LISYS_ERROR_LENGTH - 4)
		return;
	strcpy (data->text + data->pos, " -> ");
	data->pos += 4;

	/* Append format. */
	va_start (args, format);
	num = vsnprintf (data->text + data->pos, LISYS_ERROR_LENGTH - data->pos, format, args);
	va_end (args);
	if (num > 0)
		data->pos += num;
}

/**
 * \brief Returns the error state without clearing it.
 * \return Error state.
 */
 
int error_peek ()
{
	LISysError* data;

	/* Get thread specific data. */
	data = private_get ();
	if (data == NULL)
		return 0;

	/* Get the current error state. */
	return data->type;
}


/**
 * \brief Prints and clears the last error message.
 */
 
void error_report (){
	
	const char* ret;
	lisys_error_get (&ret);
	printf ("ERROR: %s\n", ret);
}

/**
 * \brief Gets and clears the current error state.
 *
 * Gets the last set error state number and optionally a detailed error string.
 * The string description is guaranteed to remain valid as long as the thread
 * exists, although its contents may change if error state is get or set.
 *
 * Error states are thread specific and this call is thus thread safe.
 *
 * \param text Return location for detailed error string or NULL.
 * \return Error type.
 */
 
int error_get (const char** text)
{
	int type;
	LISysError* data;

	/* Get thread specific data. */
	data = private_get ();
	if (data == NULL)
	{
		if (text != NULL)
			*text = "";
		return 0;
	}

	/* Get the current error state. */
	type = data->type;
	if (text != NULL)
	{
		strcpy (data->tmp, data->text);
		*text = data->tmp;
	}
	data->pos = 0;
	data->type = 0;
	data->text[0] = '\0';
	return type;
}

/**
 * \brief Gets and clears the current error state.
 *
 * Gets the detailed error string of the last error. The string is guaranteed
 * to remain valid as long as the thread exists, although its contents may
 * change if error state is get or set.
 *
 * Error states are thread specific and this call is thus thread safe.
 *
 * \return Error detail string.
 */
 
const char*
lisys_error_get_string ()
{
	const char* ret;

	lisys_error_get (&ret);
	return ret;
}

/**
 * \brief Sets the current error state.
 *
 * Error states are thread specific and this call is thus thread safe.
 *
 * \param type Error type.
 * \param format Format string for error detail or NULL.
 * \param ... Variable argument list appropriate to the format string.
 * \return Error type.
 */
 
void lisys_error_set (int         type,
                 const char* format,
                             ...)
{
	va_list args;
	const char* tmp;
	LISysError* data;

	/* Get thread specific data. */
	data = private_get ();
	if (data == NULL)
		return;

	/* Try to set from format. */
	data->type = type;
	if (format != NULL)
	{
		va_start (args, format);
		data->pos = vsnprintf (data->text, LISYS_ERROR_LENGTH, format, args);
		if (data->pos < 0)
			data->pos = 0;
		va_end (args);
		return;
	}

	/* Use default message. */
	switch (type)
	{
		case EBUSY: tmp = "busy"; break;
		case EIO: tmp = "file error"; break;
		case ENOMEM: tmp = "out of memory"; break;
		case EINVAL: tmp = "invalid syntax"; break;
		case ENOTSUP: tmp = "not supported"; break;
		case LISYS_ERROR_NONE: tmp = "success"; break;
		case LISYS_ERROR_UNKNOWN: tmp = "unknown error"; break;
		case LISYS_ERROR_VERSION: tmp = "version mismatch"; break;
		default:
			tmp = "miscellaneous error";
			break;
	}
	strncpy (data->text, tmp, LISYS_ERROR_LENGTH);
	data->text[LISYS_ERROR_LENGTH - 1] = '\0';
	data->pos = strlen (data->text);
}



static void private_init ()
{
	pthread_key_create (&private_key, private_free);
}

static void
private_free (void* data)
{
	free (data);
}

static LISysError*
private_get ()
{
	LISysError* data;

	pthread_once (&private_once, private_init);
	data = pthread_getspecific (private_key);
	if (data == NULL)
	{
		data = calloc (1, sizeof (*data));
		if (data != NULL)
			pthread_setspecific (private_key, data);
	}

	return data;
}

