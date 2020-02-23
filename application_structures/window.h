https://stackoverflow.com/questions/17160553/making-the-console-window-bigger-in-c
https://social.msdn.microsoft.com/Forums/en-US/7eb84377-10e8-4ac4-889a-33ce6bdaa185/changing-the-console-window-size
https://www.programming-techniques.com/2011/09/how-to-resize-console-window-using-c.html
https://www.c-sharpcorner.com/article/creating-custom-window-in-win32/
https://www.dreamincode.net/forums/topic/141561-using-createwindow-function/
http://zetcode.com/gui/winapi/main/
https://www.binarytides.com/winsock-socket-programming-tutorial/
https://www.clubedohardware.com.br/forums/topic/729087-ajuda-com-a-fun%C3%A7%C3%A3o-gotoxyxy/

#include <stdlib.h>
#include <stdio.h>


/*
	Refactor appgraph code :
	
	Functionality :
	ยบ Texture Object (used in: )
	ยบ Menu 
	ยบ Files ()
	
*/

/*
	Example
	
	window.h
	control.h
	draw.h
	2D.h
	interface.h
	cursor.h
	keyboard.h
	
	Window
	
	window_id = 1;
	window_type = SIMPLE_WINDOW;
	window_children = 10;
	
	control = newcontrol;
	control_Region = 200px ;
	control_size = 100;               
	control_num_rects = 20;
	
	3D = 3_D;
	2D =
	
	window();
	
	Main Menu
	
	text = "window title"; //
	color_text = "black";
	color_backround = "white";
	interface_border = "solid";
	interface_border_width = "2"; //px
	
	cursor = "";
	
	
	
	Title
	
	text_font = "";
	
	Buttons
	
	interface_property = "button";
	interface_border = "solid";
	color_border = "gray";
	interface_border_width = "1"; //px
	interface_positon_y = 10; //px 

	
	interface_positon_x = 10; //px
	
	file_path = "images/texture_button";
	open_file();
	
	if(open_file() =! true){
		error open file;
	}
	
	button();
	interface_id = 1;
	interface_positon_x = 20; //px 
	button();
	interface_positon_x = 30; //px 
	button();
	interface_positon_x = 40; //px 
	button();
	
	Menu 
	
	color_border = "black";
	color_backround = "gray";
	interface_border = "solid";
	interface_border_width = "2"; //px
	interface_buttons = 4;
	
	event_ = "menu";
	event();
	
	menu();
	
	Menu items
	
	language = "EN";
	
	event = "houver";
	color_background = "gray";
	color_text = "black";
	event();
	
	file_types = {"jpg", "png"};
	event();
	file_open();
	
	event = "click";
	text = "file open";
	event();
	
	item_default();
	menu_item();
	
	text = "new project";
	menu_item();
	
	text = "new project";
	menu_item();
	
	//menu_items();


	Tools
*/

char SIMPLE_WINDOW   "0x00000000L"; //Window creation flags:
char MENUBAR         0x00000010L
char TITLEBAR        0x00000020L
char CLOSEBOX        0x00000040L
char RESIZE          0x00000080L
char MAXIMIZE        0x00000100L
char MINIMIZE        0x00000200L
char HSCROLLBAR      0x00000400L
char VSCROLLBAR      0x00000800L
char MODAL           0x00001000L
char FLOATING        0x00002000L
char CENTERED        0x00004000L
char CENTRED         0x00004000L
char POPUP           0x00008000L
char BASE            0x00010000L
char TEMP_CURSOR     0x80000000L

#define STANDARD_WINDOW (TITLEBAR|CLOSEBOX|RESIZE|MAXIMIZE|MINIMIZE)


Window *        win;                /* target window, or */
int window_id;
char window_type[];
char window_current;

WindowExtra *   extra;              /* platform-specific data */
void *          data;               /* user-defined data */
App *           app;                /* back-pointer */
//char *          text;               /* title bar name */
long            flags;              /* decorations bit-field */
Rect            area;               /* drawable area */
Palette *       pal;                /* private palette */
//Colour          bg;                 /* background fill colour */
int             state;              /* visible? enabled? */
Region *        redraw_rgn;         /* accumulated area to draw */
Region *        visible;            /* visible region */
MenuBar *       menubar;            /* menu list, if any */

Cursor *        cursor;             /* this window's current cursor */
Cursor *        old_cursor;         /* original cursor used */
WindowFunc *        close;          /* after user selects Close */
WindowFunc *        move;           /* after window was moved */
WindowFunc *        resize;         /* after window was resized */

WindowDrawFunc *    redraw;         /* to redraw the window */
WindowMouseFunc *   mouse_down;     /* mouse button click */
WindowMouseFunc *   mouse_up;       /* mouse button released */
WindowMouseFunc *   mouse_drag;     /* mouse button down, moved */
WindowMouseFunc *   mouse_move;     /* mouse buttons up, moved */
WindowKeyFunc *     key_down;       /* normal Unicode keystroke */
WindowKeyFunc *     key_action;     /* arrow keys, etc */

static Window *       current_win       = NULL;

/*
 *  Windows:
 */

Window *app_new_window(App *app, Rect area, const char *name, long flags);
void	app_del_window(Window *w);

void	show_window(Window *w);
void	hide_window(Window *w);

Window *app_get_window_under_cursor(App *app);

void	app_move_window(Window *w, Rect r);
void	app_size_window(Window *w, Rect r);
void	app_redraw_rect(Window *w, Rect r);
void	app_redraw_window(Window *w);
void	app_draw_window(Window *w);
Rect	app_get_window_area(const Window *w);
Rect	app_get_window_rect(const Window *w);

void	app_set_window_title(Window *w, const char *title);
char *	app_get_window_title(Window *w);
void	app_set_window_icon(Window *w, Image *icon);

void	app_on_window_close (Window *w, WindowFunc close);
void	app_on_window_move(Window *w, WindowFunc move);
void	app_on_window_resize(Window *w, WindowFunc resize);
void	app_on_window_redraw(Window *w, WindowDrawFunc redraw);

void	app_on_window_mouse_down(Window *w, WindowMouseFunc mouse_down);
void	app_on_window_mouse_up  (Window *w, WindowMouseFunc mouse_up);
void	app_on_window_mouse_drag(Window *w, WindowMouseFunc mouse_drag);
void	app_on_window_mouse_move(Window *w, WindowMouseFunc mouse_move);
void	app_on_window_key_down  (Window *w, WindowKeyFunc key_down);
void	app_on_window_key_action(Window *w, WindowKeyFunc key_action);

void	app_set_window_background(Window *w, Colour col);
Colour	app_get_window_background(Window *w);

void	app_set_window_data(Window *w, void *data);
void *	app_get_window_data(Window *w);

void	app_hide_all_windows(App *app);
void	app_del_all_windows(App *app);


Window * window_current = app_parent_window(m->parent->parent->ctrl);



static void window_open_image(MenuItem *m)
{

	perform_function(w->app, get_editor_by_type("image/*"),
			 get_current_filename(w));
}

static void do_close(MenuItem *m)
{
	

	app_hide_window(w);
}

/*
 *  Windows.
 */

Window *newwindow(char *name, Rect r, long flags)
{
	Window *w;

	if (app == NULL)
		initapp(0, NULL);

	r.height += MENU_BAR_HEIGHT;
	w = app_new_window(app, r, name?name:"", flags);
	drawto((Control *)w);
	return w;
}

/*
 *  Context functions for bitmaps, windows, controls.
 */

void addto(Window *w)
{
	current_win = w;
}

void drawto(Control *c)
{
	Window *w = (Window *) c;
	Bitmap *b = (Bitmap *) c;

	if (is_a_window(w)) {
		current_win = w;
		current_dest = c;
		if (gc)
			app_del_graphics(gc);
		gc = app_get_window_graphics(w);
		app_set_font(gc, app_find_default_font(app));
	}
	else if (is_a_control(c)) {
		current_dest = c;
		if (gc)
			app_del_graphics(gc);
		gc = app_get_control_graphics(c);
		app_set_font(gc, app_find_default_font(app));
	}
	else if (is_a_bitmap(b)) {
		current_dest = c;
		if (gc)
			app_del_graphics(gc);
		gc = app_get_bitmap_graphics(b);
		app_set_font(gc, app_find_default_font(app));
	}
}

void setlinewidth(int width)
{
	app_set_line_width(gc, width);
}

/*
 *  Images.
 */

Image * new_image_IMAGE(int width, int height, int depth)
{
	return app_new_image(width, height, depth);
}

Image * copy_image(Image *img)
{
	return app_copy_image(img);
}

void del_image(Image *img)
{
	app_del_image(img);
}

Image * scaleimage(Image * src, Rect dr, Rect sr)
{
	return app_scale_image(src, dr, sr);
}

Image * convert32to8(Image *img)
{
	return app_image_convert_32_to_8(img);
}

Image * convert8to32(Image *img)
{
	return app_image_convert_8_to_32(img);
}

void setpalette(Image *img, int length, unsigned long cmap[])
{
	Colour pal[256]; /* assume length <= 256 */
	int i;

	for (i=0; i < length; i++) {
		pal[i].alpha = getalpha(cmap[i]);
		pal[i].red   = getred(cmap[i]);
		pal[i].green = getgreen(cmap[i]);
		pal[i].blue  = getblue(cmap[i]);
	}

	app_set_image_cmap(img, length, pal);
}

unsigned long *	getpalette(Image *img)
{
	int i;
	unsigned long *data;
	Colour col;

	data = get_association(img, ASSOC_CMAP);
	if (data)
		app_free(data);
	data = app_alloc(img->cmap_size * sizeof(unsigned long));
	if (data == NULL)
		return NULL;
	add_association(img, ASSOC_CMAP, data);

	for (i=0; i < img->cmap_size; i++) {
		col = img->cmap[i];
		data[i] = colour_to_rgb(col);
	}
	return data;
}

int getpalettesize(Image *img)
{
	return img->cmap_size;
}



void sortpalette(Image *img)
{
	app_image_sort_palette(img);
}

Image * loadimage(char *filename)
{
	Image *img;

	img = app_read_image(filename, 8);
	if (img == NULL)
		img = app_read_image(filename, 32);
	return img;
}

void saveimage(Image *img, char *filename)
{
	app_write_image(img, filename);
}

void drawimage(Image *img, Rect dr, Rect sr)
{
	enable_drawing();

	app_draw_image(gc, dr, img, sr);
}


/*
 *  Setting window and control callback functions.
 */

void setaction(Control *c, actionfn fn)
{
	if (is_a_control(c))
		app_on_control_action(c, fn);
}

static void private_hit_action(Control *c)
{
	intfn hit = get_association(c, ASSOC_HIT);

	if (hit != NULL)
		hit(c, app_get_control_value(c));
}

void sethit(Control *c, intfn fn)
{
	add_association(c, ASSOC_HIT, fn);
	if (is_a_control(c))
		app_on_control_action(c, private_hit_action);
}

void setdel(Control *c, actionfn fn)
{
	if (is_a_control(c))
		app_on_control_deletion(c, fn);
}

void setclose(Window *w, WindowFunc fn)
{
	if (is_a_window(w))
		app_on_window_close(w, fn);
}

static void private_redraw_window(Window *w, Graphics *g)
{
	Graphics *old;
	drawfn fn = get_association(w, ASSOC_REDRAW);

	old = gc;
	gc = g;
	if (fn != NULL)
		fn((Control *)w, app_get_window_area(w));
	gc = old;
}

static void private_redraw_control(Control *c, Graphics *g)
{
	Graphics *old;
	drawfn fn = get_association(c, ASSOC_REDRAW);

	old = gc;
	gc = g;
	if (fn != NULL)
		fn(c, app_get_control_area(c));
	gc = old;
}

void setredraw(Control *c, drawfn fn)
{
	Window *w = (Window *) c;

	add_association(c, ASSOC_REDRAW, fn);
	if (is_a_window(w))
		app_on_window_redraw(w, private_redraw_window);
	else if (is_a_control(c))
		app_on_control_redraw(c, private_redraw_control);
}

static void private_resize_window(Window *w)
{
	Graphics *old;
	drawfn fn = get_association(w, ASSOC_RESIZE);

	old = gc;
	gc = app_get_window_graphics(w);
	if (fn != NULL)
		fn((Control *)w, app_get_window_area(w));
	app_del_graphics(gc);
	gc = old;
}


/*
 *  Using windows and controls.
 */

void clear(Control *c)
{
	Graphics *g;
	Window *w = (Window *) c;
	Bitmap *b = (Bitmap *) c;

	if (is_a_window(w)) {
		g = app_get_window_graphics(w);
		app_set_rgb(g, w->bg);
		app_fill_rect(g, app_get_window_area(w));
		app_del_graphics(g);
	}
	else if (is_a_control(c)) {
		g = app_get_control_graphics(c);
		app_set_rgb(g, c->bg);
		app_fill_rect(g, app_get_control_area(c));
		app_del_graphics(g);
	}
	else if (is_a_bitmap(b)) {
		g = app_get_bitmap_graphics(b);
		app_set_rgb(g, WHITE);
		app_fill_rect(g, app_get_bitmap_area(b));
		app_del_graphics(g);
	}
}

void draw(Control *c)
{
	Window *w = (Window *) c;

	if (is_a_window(w))
		app_draw_window(w);
	else if (is_a_control(c))
		app_draw_control(c);
}

void redraw(Control *c)
{
	Window *w = (Window *) c;

	if (is_a_window(w))
		app_redraw_window(w);
	else if (is_a_control(c))
		app_redraw_control(c);
}

static Rect adjust_rect(Rect r)
{
	r.y += MENU_BAR_HEIGHT; /* account for menu bar */
	return r;
}

void resize(Control *c, Rect r)
{
	Window *w = (Window *) c;

	if (is_a_window(w))
		app_size_window(w, r);
	else if (is_a_control(c))
		app_set_control_area(c, adjust_rect(r));
}

void show(Control *c)
{
	Window *w = (Window *) c;

	if (is_a_window(w))
		app_show_window(w);
	else if (is_a_control(c))
		app_show_control(c);
}

void hide(Control *c)
{
	Window *w = (Window *) c;

	if (is_a_window(w))
		app_hide_window(w);
	else if (is_a_control(c))
		app_hide_control(c);
}

int isvisible(Control *c)
{
	Window *w = (Window *) c;

	if (is_a_window(w))
		return w->state & VISIBLE;
	else if (is_a_control(c))
		return app_is_visible(c);
	return 0;
}

void enable(Control *c)
{
	Window *w = (Window *) c;
	MenuItem *mi = (MenuItem *) c;

	if (is_a_window(w))
		w->state |= ENABLED;
	else if (is_a_control(c))
		app_enable(c);
	else if (is_a_menu_item(mi))
		app_enable_menu_item(mi);
}

void disable(Control *c)
{
	Window *w = (Window *) c;
	MenuItem *mi = (MenuItem *) c;

	if (is_a_window(w))
		w->state &= ~ENABLED;
	else if (is_a_control(c))
		app_disable(c);
	else if (is_a_menu_item(mi))
		app_disable_menu_item(mi);
}

int isenabled(Control *c)
{
	Window *w = (Window *) c;
	MenuItem *mi = (MenuItem *) c;

	if (is_a_window(w))
		return (w->state & ENABLED) ? 1 : 0;
	else if (is_a_control(c))
		return app_is_enabled(c);
	else if (is_a_menu_item(mi))
		return app_menu_item_is_enabled(mi);
	return 1;
}

void check(Control *c)
{
	MenuItem *mi = (MenuItem *) c;

	if (is_a_control(c))
		app_check(c);
	else if (is_a_menu_item(mi))
		app_check_menu_item(mi);
}

void uncheck(Control *c)
{
	MenuItem *mi = (MenuItem *) c;

	if (is_a_control(c))
		app_uncheck(c);
	else if (is_a_menu_item(mi))
		app_uncheck_menu_item(mi);
}

int ischecked(Control *c)
{
	MenuItem *mi = (MenuItem *) c;

	if (is_a_control(c))
		return app_is_checked(c);
	else if (is_a_menu_item(mi))
		return app_menu_item_is_checked(mi);
	return 0;
}

void highlight(Control *c)
{
	if (is_a_control(c))
		app_highlight(c);
}

void unhighlight(Control *c)
{
	if (is_a_control(c))
		app_unhighlight(c);
}

int ishighlighted(Control *c)
{
	if (is_a_control(c))
		return app_is_highlighted(c);
	return 0;
}

void flashcontrol(Control *c)
{
	if (is_a_control(c))
		return app_flash_control(c);
}

void activatecontrol(Control *c)
{
	if (is_a_control(c))
		return app_activate_control(c);
}

