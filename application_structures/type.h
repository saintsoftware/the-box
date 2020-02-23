
/*
 *  Some functions used to determine what kind of thing
 *  an object is. In GraphApp version 2, there was an
 *  integer as the first field in every object's data
 *  structure. This integer was guaranteed to be unique
 *  for each type of object. So switch statements could
 *  be used to determine quickly what kind of object
 *  a run-time-polymorphic function was examining.
 *  Version 3 favours compiler-based polymorphism instead,
 *  and has abandoned this run-time strategy. So we
 *  need these functions to look through the window list
 *  and check whether the object is a window, control,
 *  menu item, font, etc.
 *
 *  In some cases this is little better than a guess, but
 *  for windows, controls, menu bars, menus and menu items
 *  at least (the most common objects) it should work
 *  exactly, because we have a global App object we can
 *  examine, without interpreting the object pointer in
 *  any way. We look forward from the App's data structures
 *  for a match, rather than interpreting the object
 *  pointer and trying to look backwards. This avoids
 *  violating memory as much as possible.
 */
 
char property_type;


/*
 *  apptypes.h
 *  Contains platform and compiler-specific definitions.
 *  Do not edit this machine-generated file.
 *  Re-compile and run apptypes.c instead.
 */

/* Standard type names: */
typedef signed char     app_int8;    /* 8-bit signed integer. */
typedef unsigned char   app_uint8;   /* 8-bit unsigned integer. */
typedef short           app_int16;   /* 16-bit signed integer. */
typedef unsigned short  app_uint16;  /* 16-bit unsigned integer. */
typedef int             app_int32;   /* 32-bit signed integer. */
typedef unsigned int    app_uint32;  /* 32-bit unsigned integer. */
typedef float           app_float32; /* Small floating-point number. */
typedef double          app_float64; /* Large floating-point number. */
typedef void *          app_pointer; /* Largest pointer. */

/* Common type names: */
typedef app_uint8       app_byte;    /* 8-bit unsigned integer. */
typedef app_int8        app_sbyte;   /* 8-bit signed integer. */
typedef app_int16       app_short;   /* 16-bit signed integer. */
typedef app_uint16      app_ushort;  /* 16-bit unsigned integer. */
typedef app_int32       app_int;     /* 32-bit signed integer. */
typedef app_uint32      app_uint;    /* 32-bit unsigned integer. */
typedef app_float32     app_float;   /* 32-bit floating point number. */
typedef app_float64     app_real;    /* 64-bit floating point number. */
typedef app_uint32      app_char;    /* 32-bit Unicode Char. */

/* The printf length modifier format strings. */
#define APP_BYTE_PRINTF_FMT   
#define APP_SHORT_PRINTF_FMT  "h"
#define APP_INT_PRINTF_FMT    
#define APP_FLOAT_PRINTF_FMT  
#define APP_REAL_PRINTF_FMT   

/* The scanf length modifier format strings. */
#define APP_BYTE_SCANF_FMT    
#define APP_SHORT_SCANF_FMT   "h"
#define APP_INT_SCANF_FMT     
#define APP_FLOAT_SCANF_FMT   
#define APP_REAL_SCANF_FMT    "l"

/* Type sizes (in bytes). */
enum {
	APP_BYTE_SIZE       = 1,
	APP_SHORT_SIZE      = 2,
	APP_INT_SIZE        = 4,
	APP_FLOAT_SIZE      = 4,
	APP_REAL_SIZE       = 8,
	APP_POINTER_SIZE    = 4
};

/* Type packing alignment within structures. */
enum {
	APP_BYTE_PACKING    = 1,
	APP_SHORT_PACKING   = 2,
	APP_INT_PACKING     = 4,
	APP_FLOAT_PACKING   = 4,
	APP_REAL_PACKING    = 4,
	APP_POINTER_PACKING = 4,
	APP_MAXIMUM_PACKING = 4
};

/* Arithmetic limits. */
#define APP_BYTE_MIN    (0)
#define APP_BYTE_MAX    (255)
#define APP_SBYTE_MIN   (-128)
#define APP_SBYTE_MAX   (127)

#define APP_SHORT_MIN   (-32768)
#define APP_SHORT_MAX   (32767)
#define APP_USHORT_MIN  (0)
#define APP_USHORT_MAX  (65535)

#define APP_INT_MIN     (-2147483648)
#define APP_INT_MAX     (2147483647)
#define APP_UINT_MIN    (0)
#define APP_UINT_MAX    (4294967295)

#define APP_CHAR_MIN    (0)
#define APP_CHAR_MAX    (4294967295)

/*
 *  Functions which work for bitmaps, windows and controls.
 */

int objdepth(Window *w)
{
	Image *img = (Image *) w;

	if (is_a_window(w))
		return 8; /* guess */
	else if ((img->depth == 32) && (img->cmap_size == 0))
		return 32;
	else if ((img->depth == 8) && (img->cmap_size > 0)
		 && (img->cmap_size <= 256))
		return 8;
	else
		return 8; /* guess */
}

Rect objrect(void *obj)
{
	Rect r;

	if (is_a_window(obj)) {
		r = app_get_window_area(obj);
		r.y += MENU_BAR_HEIGHT; /* account for menu bar */
		r.height -= MENU_BAR_HEIGHT;
	}
	else if (is_a_control(obj))
		r = app_get_control_area(obj);
	else if (is_a_bitmap(obj))
		r = app_get_bitmap_area(obj);
	else if (is_a_font(obj))
		r = rect(0,0,fontheight(obj), fontwidth(obj));
	else if (is_a_image(obj))
		r = app_get_image_area(obj);
	else
		r = rect(0,0,0,0);
	return r;
}

int objwidth(void *obj)
{
	return objrect(obj).width;
}

int objheight(void *obj)
{
	return objrect(obj).height;
}

void delobj(void *obj)
{
	del_association(obj, ASSOC_ALL);
	if (is_a_window(obj))
		return app_del_window(obj);
	else if (is_a_control(obj))
		return app_del_control(obj);
	else if (is_a_menu_bar(obj))
		return app_del_menu_bar(obj);
	else if (is_a_menu(obj))
		return app_del_menu(obj);
	else if (is_a_menu_item(obj))
		return app_del_menu_item(obj);
	else if (is_a_bitmap(obj))
		return app_del_bitmap(obj);
	else if (is_a_image(obj))
		return app_del_image(obj);
} 
 
static int is_a_window(Window *w)
{
	int i;

	if (w == NULL)
		return 0;
	if (app == NULL)
		return 0;
	/* just look through the window list for a match */
	for (i=0; i < app->num_windows; i++)
		if (w == app->windows[i])
			return 1;
	return 0;
}

static int is_a_child_control(Control *c, Control *parent)
{
	int i;

	if (c == parent)
		return 1;
	/* look recursively through the child controls */
	for (i=0; i < parent->num_children; i++)
		if (is_a_child_control(c, parent->children[i]))
			return 1;
	return 0;
}

static int is_a_control(Control *c)
{
	int i, j;
	Window *w;

	if (c == NULL)
		return 0;
	if (app == NULL)
		return 0;
	for (i=0; i < app->num_windows; i++) {
		w = app->windows[i];
		/* look recursively through the window's controls */
		for (j=0; j < w->num_children; j++)
			if (is_a_child_control(c, w->children[j]))
				return 1;
	}
	return 0;
}

static int is_a_menu_bar(MenuBar *mb)
{
	int i;
	Window *w;

	if (mb == NULL)
		return 0;
	if (app == NULL)
		return 0;
	/* look through the window list for a matching menu bar */
	for (i=0; i < app->num_windows; i++) {
		w = app->windows[i];
		if (w->menubar == mb)
			return 1;
	}
	return 0;
}

static int is_a_child_menu(Menu *m, Menu *parent)
{
	int i;
	MenuItem *mi;

	if (m == parent)
		return 1;
	/* recursively look for submenus */
	for (i=0; i < parent->num_items; i++) {
		mi = parent->items[i];
		if (mi->submenu == NULL)
			continue;
		if (is_a_child_menu(m, mi->submenu))
			return 1;
	}
	return 0;
}

static int is_a_menu(Menu *m)
{
	int i, j;
	Window *w;
	Menu *toplevel;

	if (m == NULL)
		return 0;
	if (app == NULL)
		return 0;
	/* look through the window list for menu bars */
	/* then look through each menu bar for menus */
	for (i=0; i < app->num_windows; i++) {
		w = app->windows[i];
		if (w->menubar == NULL)
			continue;
		for (j=0; j < w->menubar->num_menus; j++) {
			toplevel = w->menubar->menus[j];
			if (is_a_child_menu(m, toplevel))
				return 1;
		}
	}
	return 0;
}

static int is_a_child_menu_item(MenuItem *mi, MenuItem *parent)
{
	int i;
	Menu *m;

	if (mi == parent)
		return 1;
	if (parent->submenu == NULL)
		return 0;
	/* recursively look for menu items inside submenus */
	m = parent->submenu;
	for (i=0; i < m->num_items; i++) {
		if (is_a_child_menu_item(mi, m->items[i]))
			return 1;
	}
	return 0;
}

static int is_a_menu_item(MenuItem *mi)
{
	int i, j, k;
	Window *w;
	MenuBar *mb;
	Menu *m;

	if (mi == NULL)
		return 0;
	if (app == NULL)
		return 0;
	/* look through the window list for menu bars */
	/* then look through each menu bar for menus */
	/* then look through each menu for menu items */
	for (i=0; i < app->num_windows; i++) {
		w = app->windows[i];
		if (w->menubar == NULL)
			continue;
		mb = w->menubar;
		for (j=0; j < mb->num_menus; j++) {
			m = mb->menus[j];
			for (k=0; k < m->num_items; k++) {
				if (is_a_child_menu_item(mi, m->items[k]))
					return 1;
			}
		}
	}
	return 0;
}

static int is_a_bitmap(Bitmap *b)
{
	if (b == NULL)
		return 0;
	if (is_a_window((Window *)b))
		return 0;
	if (is_a_control((Control *)b))
		return 0;
	if (is_a_menu_bar((MenuBar *)b))
		return 0;
	if (is_a_menu((Menu *)b))
		return 0;
	if (is_a_menu_item((MenuItem *)b))
		return 0;
	if (is_a_window(b->win))
		return 1;
	/* but what if the bitmap's window has been deleted? */
	return 0;
}

static int is_a_font(Font *f)
{
	if (f == NULL)
		return 0;
	if (is_a_window((Window *)f))
		return 0;
	if (is_a_control((Control *)f))
		return 0;
	if (is_a_menu_bar((MenuBar *)f))
		return 0;
	if (is_a_menu((Menu *)f))
		return 0;
	if (is_a_menu_item((MenuItem *)f))
		return 0;
	if (is_a_bitmap((Bitmap *)f))
		return 0;
	if (f->app == app)
		return 1;
	return 0;
}

static int is_a_image(Image *img)
{
	if (img == NULL)
		return 0;
	if (is_a_window((Window *)img))
		return 0;
	if (is_a_control((Control *)img))
		return 0;
	if (is_a_menu_bar((MenuBar *)img))
		return 0;
	if (is_a_menu((Menu *)img))
		return 0;
	if (is_a_menu_item((MenuItem *)img))
		return 0;
	if ((img->depth != 8) && (img->depth != 32))
		return 0;
	if (is_a_bitmap((Bitmap *)img))
		return 0;
	return 1;
}


