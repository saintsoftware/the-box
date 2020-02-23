//https://www.geeksforgeeks.org/time-h-header-file-in-c-with-examples/

//https://www.geeksforgeeks.org/time-h-localtime-function-in-c-with-examples/

// https://www.geeksforgeeks.org/write-a-c-function-to-print-the-middle-of-the-linked-list/

// https://www.geeksforgeeks.org/asctime-and-asctime_s-functions-in-c-with-examples/

// #include <time.h> 

typedef struct Timer          Timer;

struct Timer {
	App *           app;                /* associated App */
	int             milliseconds;       /* interval between actions */
	unsigned long   last_time;          /* last checked time */	//!!
	TimerAction     action;             /* user-defined action */
	void *          data;               /* user-defined data */
	int             value;              /* user-defined value */
};


uint_16 year; /* full year, as in, 1995 */
byte month;   /* month of year, 1 - 12 */
byte day;     /* day of month, 1 - 31 */
byte hour;    /* hour of day, 0 - 23 */
byte minute;  /* minute of hour, 0 - 59 */
byte second; /* second of minute, 0 - 60 (for leap seconds) */

char time[];

struct tm* local; 
time_t t = time(NULL); 

// Get the localtime 
local = localtime(&t); 

printf("Local time and date: %s\n", asctime(local)); 

static Timer *        current_timer     = NULL;


/*
 *  Timing:
 */

int           app_delay(App *app, int milliseconds);
unsigned long app_current_time(App *app);

Timer *	app_new_timer(App *app, TimerAction action, int milliseconds);
void	app_del_timer(Timer *t);
void	app_reset_timer(Timer *t, int milliseconds);

/*
 *  Time functions.
 */

int settimer(unsigned millisec)
{
	current_msec = millisec;
	if (millisec == 0) {
		if (current_timer) {
			app_del_timer(current_timer);
			current_timer = NULL;
		}
	}
	return 1;
}

static void private_timeout(Timer *t)
{
	timerfn fn = get_association(t, ASSOC_TIMER);

	if (fn != NULL)
		fn(t->data);
}

void settimerfn(timerfn timeout, void *data)
{
	if (current_timer)
		app_del_timer(current_timer);
	current_timer = app_new_timer(app, private_timeout, current_msec);
	add_association(current_timer, ASSOC_TIMER, timeout);
	current_timer->data = data;
}

int setmousetimer(unsigned millisec)
{
	return 0; /* cheat */
}

void delay(unsigned millisec)
{
	app_delay(app, millisec);
}

long currenttime(void)
{
	return app_current_time(app);
}