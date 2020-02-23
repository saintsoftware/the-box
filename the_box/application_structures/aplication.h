



typedef struct App            App;
static App *   app = NULL;

struct App {
	AppExtra *      extra;              /* platform-specific data */
	void *          data;               /* user-defined data */

	int             gui_available;      /* is the GUI available? */
	Rect            screen_area;        /* screen pixel dimensions */
	Rect            screen_mm;          /* screen size in millimetres */

	char *          program_name;       /* path to starting program */
	short           has_resources;      /* this app has resources? */
	short           use_X_copy_paste;   /* use X11 mouse copy/paste? */
	int             socket_fd;          /* X11 socket file descriptor */

	int             num_windows;        /* list of all windows */
	Window **       windows;
	int             visible_windows;    /* how many are visible */

	int             num_modals;         /* stack of modal windows */
	Window **       modals;

	int             num_fonts;          /* list of fonts */
	Font **         fonts;

	int             num_timers;         /* list of active timers */
	Timer **        timers;

	int             num_cursors;        /* list of cursors */
	Cursor **       cursors;

	int             compose_key;        /* for producing Unicode input */

	StringTable *   string_table;       /* for localisation */

	char *          open_folder;        /* file open dialog folder */
	Rect            open_dialog_area;   /* dialog screen location */
	char *          save_folder;        /* file save dialog folder */
	Rect            save_dialog_area;   /* dialog screen location */

	int             deleting;           /* doing delayed-deletion now? */
	int             num_deleted_windows;
	Window **       deleted_windows;    /* list of windows to delete */
	int             num_deleted_controls;
	Control **      deleted_controls;   /* list of controls to delete */

	void *			tip;				/* tip control */

	void *          ft_library;         /* for FreeType support */
};

int initapp(int argc, char *argv[])
{
	app_debug_memory(1);
	app = app_new_app(argc, argv);
	if (app == NULL)
		return 0;

	SystemFont = app_find_default_font(app);
	FixedFont = SystemFont;
	Times = app_new_font(app, "Times", PLAIN, 16);
	Helvetica = app_new_font(app, "Helvetica", PLAIN, 16);
	Courier = FixedFont;

	BlankCursor = 0;
	ArrowCursor = 1;
	WatchCursor = 2;
	CaretCursor = 3;
	TextCursor  = 4;
	HandCursor  = 5;

	return 1;
}

/*
 *  Application:
 */

App *	app_new_app(int argc, char *argv[]);
void	app_del_app(App *app);
int 	app_exec(App *app, const char *command);

void exitapp(void)
{
	if (app)
		app_del_app(app);
	exit(0);
}

void drawall(void)
{
	app_draw_all(app);
}

int peekevent(void)
{
	return app_peek_event(app);
}

int doevent(void)
{
	return app_do_event(app);
}

void mainloop(void)
{
	if (app == NULL)
		initapp(0, NULL);
	app_main_loop(app);
}

int execapp(char *cmd)
{
	return app_exec(app, cmd);
}

