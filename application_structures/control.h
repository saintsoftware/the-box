
https://www.mathworks.com/help/matlab/ref/loadlibrary.html
http://www.dyncall.org/
http://www.vitanuova.com/inferno/downloads.html

/*

A Control is a area on a window which responds to user's actions, such as mouse clicks and the keyboard, to perform some function. Functions which create controls take as an argument a rectangle, which specifies where on the current window the control should be placed. The rectangle is measured in pixels, relative to the top-left point of the window which is the point (0,0).

Buttons, check boxes, text fields, etc are all kinds of <I>Controls</I>, so many of the functions described in the following sections apply equally to those objects, as they do to custom-made controls.

The <B>new_control</B> function creates and returns a generic control of the requested size and attaches it to the given window. The control can have call-backs added to it using <B>on_control_redraw, ap_on_control_mouse_down</B> etc (see later sections), to allow the control to respond to events.

The <B>add_control</B> function behaves much the same, except the created control is attached to the given parent control. Controls can have other controls attached to their surfaces. These child controls will appear inside the parent control, and cannot move outside of the parent's boundary.

The <B>del_control</B> function destroys a control and removes it from any window to which it is attached. Normally this function is not used, since destroying a window will destroy all of its child controls.

The <B>remove_control</B> function removes a control from its parent window or control. A side-effect of this function is that the control will become invisible since the parent window or control will be redrawn. Such a removed control can be re-attached to a window or control's surface using <B>attach_to_window</B> or <B>attach_to_control</B>.

A control's position in the stacking hierarchy can be manipulated. The <B>bring_control_to_front</B> function moves a control in front of its siblings, while <B>send_control_to_back</B> places it behind its siblings.

The <B>parent_window</B> function returns the window where the control resides. If a control is a child of another control, this function looks up the parent window of the parent controls until it finds the enclosing window. If the control or its parents are not currently attached to any window, this function returns NULL.
</BODY>
</HTML>

*/

/*
	Control draw area
	
	inherit:
	-window
	-image
	-font
	
	Functionality :
	ยบ Texture Object (used in: )
	ยบ Menu 
	ยบ Files ()
	
*/

/*
 *  Control and Window state flags:
 */

/* State flags: */
#define VISIBLE        0x00000001L
#define ENABLED        0x00000002L
#define CHECKED        0x00000004L
#define HIGHLIGHTED    0x00000008L
#define ARMED          0x00000010L

/* Layout flags: */
#define EDGE_LEFT      0x00000100L
#define EDGE_TOP       0x00000200L
#define EDGE_RIGHT     0x00000400L
#define EDGE_BOTTOM    0x00000800L
#define EDGE_ALL       (EDGE_LEFT | EDGE_TOP | EDGE_RIGHT | EDGE_BOTTOM)
#define DOCK           0x00001000L
#define FILL           (EDGE_ALL | DOCK)

#define FLOW           0x00002000L
#define FLOW_VERT      0x00004000L
#define LAYOUT_MASK    0x0000FF00L
#define AUTOSIZE       0x00010000L
#define TABSTOP        0x00020000L
#define MANAGER        0x00040000L

/* Border flags: */
#define BORDER_LEFT    0x00100000L
#define BORDER_TOP     0x00200000L
#define BORDER_RIGHT   0x00400000L
#define BORDER_BOTTOM  0x00800000L
#define BORDER_ALL     (BORDER_LEFT |BORDER_TOP |BORDER_RIGHT |BORDER_BOTTOM)

/* Tips flags: */	//!!
#define TIP_TEXT       0x01000000L
#define TIP_HANDLER    0x02000000L
#define TIP_MASK       (TIP_TEXT | TIP_HANDLER)

typedef struct Region         Region;

typedef void (*voidfn)(void);
typedef void (*timerfn)(void *data);
typedef void (*actionfn)(Control *c);
typedef void (*drawfn)(Control *c, Rect r);
typedef void (*mousefn)(Control *c, int buttons, Point xy);
typedef void (*intfn)(Control *c, int argument);
typedef void (*keyfn)(Control *c, int key);
typedef void (*menufn)(MenuItem *m);
typedef void (*scrollfn)(Control *c, int position);

#define REDEFINE_FUNC_NAMES
#define addpt      GA_addpt
#define subpt      GA_subpt
#define equalpt    GA_equalpt
#define newmenu    GA_newmenu
#define newcontrol GA_newcontrol
#define newwindow  GA_newwindow
#define gettext    GA_gettext
#define settext    GA_settext

 typedef struct Control        Control;

int             control_children;       /* list of child controls */
Control **      children;
Control *       mouse_grab;         /* last mouse down was here */
Control *       key_focus;          /* keyboard focus control */
int             pass_event;         /* pass event up the chain? */ 

Rect            extents;            /* maximum affected rect */
int             control_size;               /* current allocated size */
int             control_num_rects;          /* list of distinct rects */
Rect *          rects;


static Control *      current_dest      = NULL;

Rect control_area;
int control_childrens; 
Control * control_parent;

/*
	Example
	
	window_type = "";
*/

char control;
int control_id;

Window *        win;                /* parent window */
Control *       parent;             /* parent control (optional) */
Rect            area;               /* drawable area */
Rect            natural;            /* natural area */
//int             padding;            /* inner gap */
//int             margin;             /* outer gap */
Point           corner;             /* from parent RB-corner */
Point           offset;             /* to window co-ordinates */

int             num_children;       /* list of child controls */
Control **      children;
Colour          bg;                 /* background fill colour */
Colour          fg;                 /* foreground draw colour */
long            state;              /* enabled? layout? border? */
Region *        visible;            /* visible region on window */
void *          data;               /* user-defined data */
char *          text;               /* control-defined data */
void *          extra;              /* control-defined data */
long            value;              /* control-defined data */
Image *         img;                /* control-defined data */
Font *          font;               /* control-defined data */
Cursor *        cursor;             /* control-defined data */
ControlFunc *   resize;             /* call-back used to resize */
DrawFunc *      redraw;             /* call-back used to redraw */
MouseFunc *     mouse_down;         /* mouse event handler */
MouseFunc *     mouse_up;           /* mouse event handler */
MouseFunc *     mouse_drag;         /* mouse event handler */
MouseFunc *     mouse_move;         /* mouse event handler */
KeyFunc *       key_down;           /* Unicode key handler */
KeyFunc *       key_action;         /* arrow key, etc, handler */
ControlFunc *   action;             /* action to perform */
ControlFunc *   update;             /* used when any data changes */
ControlFunc *   refocus;            /* used when focus changes */
ControlFunc *   del;                /* used during deletion */


/*
 *  Controls:
 */

Control *app_new_control(Window *parent, Rect r);
Control *app_add_control(Control *parent, Rect r);
void	app_del_control(Control *c);

int 	app_attach_to_window(Window *parent, Control *c);
int 	app_attach_to_control(Control *parent, Control *c);
int		app_bring_control_to_front(Control *c);
int		app_send_control_to_back(Control *c);
int 	app_remove_control(Control *c);

void	app_place_window_controls(Window *w, int recalculate);
Control *app_locate_control(Window *w, Point p);

#define app_parent_window(c)	((c)->win)
void	app_draw_control(Control *c);
void	app_redraw_control(Control *c);
void	app_redraw_control_rect(Control *c, Rect r);

void	app_move_control(Control *c, Rect r);
void	app_size_control(Control *c, Rect r);
void	app_set_control_area(Control *c, Rect r);
Rect	app_get_control_area(Control *c);

int 	app_is_visible(Control *c);
void	app_show_control(Control *c);
void	app_hide_control(Control *c);

void	app_on_control_resize    (Control *c, ControlFunc resize);
void	app_on_control_redraw    (Control *c, DrawFunc redraw);
void	app_on_control_mouse_down(Control *c, MouseFunc mouse_down);
void	app_on_control_mouse_up  (Control *c, MouseFunc mouse_up);
void	app_on_control_mouse_drag(Control *c, MouseFunc mouse_drag);
void	app_on_control_mouse_move(Control *c, MouseFunc mouse_move);
void	app_on_control_key_down  (Control *c, KeyFunc key_down);
void	app_on_control_key_action(Control *c, KeyFunc key_action);
void	app_on_control_action    (Control *c, ControlFunc action);
void	app_on_control_update    (Control *c, ControlFunc update);
void	app_on_control_refocus   (Control *c, ControlFunc refocus);
void	app_on_control_deletion  (Control *c, ControlFunc del);

void	app_set_control_background(Control *c, Colour col);
Colour	app_get_control_background(Control *c);

void	app_set_control_foreground(Control *c, Colour col);
Colour	app_get_control_foreground(Control *c);

void	app_set_control_text(Control *c, const char *text);
char *	app_get_control_text(Control *c);

void	app_set_control_data(Control *c, void *data);
void *	app_get_control_data(Control *c);

void	app_set_control_value(Control *c, long value);
long	app_get_control_value(Control *c);

void	app_set_control_image(Control *c, Image *img);
Image *	app_get_control_image(Control *c);

void	app_set_control_font(Control *c, Font *f);
Font *	app_get_control_font(Control *c);

void	app_set_control_cursor(Control *c, Cursor *cursor);
Cursor *app_get_control_cursor(Control *c);

int 	app_set_control_tip(Control *c, long mode, void *p);

void	app_set_control_border(Control *c, long flags);
void	app_set_control_layout(Control *c, long flags);
void	app_set_control_gap(Control *c, int padding, int margin);
void	app_set_control_autosize(Control *c, int autosizable);

int 	app_is_enabled(Control *c);
void	app_enable(Control *c);
void	app_disable(Control *c);

int 	app_is_checked(Control *c);
void	app_check(Control *c);
void	app_uncheck(Control *c);

int 	app_is_highlighted(Control *c);
void	app_highlight(Control *c);
void	app_unhighlight(Control *c);

int 	app_is_armed(Control *c);
void	app_arm(Control *c);
void	app_disarm(Control *c);

int 	app_has_focus(Control *c);
void	app_set_focus(Control *c);

void	app_flash_control(Control *c);
void	app_activate_control(Control *c);


/* Tips: */	//!!

int 	app_set_control_tip(Control *c, long mode, void *p);
void	app_handle_tip(Control *c);


/*
 *  Managers:	//!!
 */
void	app_manager_hbox(Control *c);
void	app_manager_vbox(Control *c);

static void private_resize_control(Control *c)
{
	Graphics *old;
	drawfn fn = get_association(c, ASSOC_RESIZE);

	old = gc;
	gc = app_get_control_graphics(c);
	if (fn != NULL)
		fn(c, app_get_control_area(c));
	app_del_graphics(gc);
	gc = old;
}

void setresize(Control *c, drawfn fn)
{
	Window *w = (Window *) c;

	add_association(c, ASSOC_RESIZE, fn);
	if (is_a_window(w))
		app_on_window_resize(w, private_resize_window);
	else if (is_a_control(c))
		app_on_control_resize(c, private_resize_control);
}

void setkeydown(Control *c, keyfn fn)
{
	/* assuming sizeof(int) == sizeof(unsigned long) ... */

	Window *w = (Window *) c;

	if (is_a_window(w))
		app_on_window_key_down(w, (WindowKeyFunc) fn);
	else if (is_a_control(c))
		app_on_control_key_down(c, (KeyFunc) fn);
}

void setkeyaction(Control *c, keyfn fn)
{
	/* assuming sizeof(int) == sizeof(unsigned long) ... */

	Window *w = (Window *) c;

	if (is_a_window(w))
		app_on_window_key_action(w, (WindowKeyFunc) fn);
	else if (is_a_control(c))
		app_on_control_key_action(c, (KeyFunc) fn);
}

void setmousedown(Control *c, mousefn fn)
{
	Window *w = (Window *) c;

	if (is_a_window(w))
		app_on_window_mouse_down(w, (WindowMouseFunc) fn);
	else if (is_a_control(c))
		app_on_control_mouse_down(c, fn);
}

void setmousedrag(Control *c, mousefn fn)
{
	Window *w = (Window *) c;

	if (is_a_window(w))
		app_on_window_mouse_drag(w, (WindowMouseFunc) fn);
	else if (is_a_control(c))
		app_on_control_mouse_drag(c, fn);
}

void setmouseup(Control *c, mousefn fn)
{
	Window *w = (Window *) c;

	if (is_a_window(w))
		app_on_window_mouse_up(w, (WindowMouseFunc) fn);
	else if (is_a_control(c))
		app_on_control_mouse_up(c, fn);
}

void setmousemove(Control *c, mousefn fn)
{
	Window *w = (Window *) c;

	if (is_a_window(w))
		app_on_window_mouse_move(w, (WindowMouseFunc) fn);
	else if (is_a_control(c))
		app_on_control_mouse_move(c, fn);
}

void setmouserepeat(Control *c, mousefn fn)
{
	/* difficult to do */
}


/*
 *  Changing the state of a control.
 */

void settext(Control *c, char *text)
{
	Window *w = (Window *) c;
	Menu *m = (Menu *) c;
	MenuItem *mi = (MenuItem *) c;

	if (is_a_window(w))
		app_set_window_title(w, text);
	else if (is_a_control(c))
		app_set_control_text(c, text);
	else if (is_a_menu(m)) {
		char *old = m->text;
		m->text = app_copy_string(text?text:"");
		app_del_string(old);
		app_redraw_control(m->parent->ctrl);
	}
	else if (is_a_menu_item(mi)) {
		char *old = mi->text;
		mi->text = app_copy_string(text?text:"");
		app_del_string(old);
	}
}

char * gettext(Control *c)
{
	Window *w = (Window *) c;
	Menu *m = (Menu *) c;
	MenuItem *mi = (MenuItem *) c;

	if (is_a_window(w))
		return app_get_window_title(w);
	else if (is_a_control(c))
		return app_get_control_text(c);
	else if (is_a_menu(m))
		return m->text;
	else if (is_a_menu_item(mi))
		return mi->text;
	return "";
}

void settextfont(Control *c, Font *f)
{
	Window *w = (Window *) c;
	MenuBar *mb = (MenuBar *) c;
	Menu *m = (Menu *) c;
	MenuItem *mi = (MenuItem *) c;

	if (is_a_window(w))
		return;
	else if (is_a_control(c))
		app_set_control_font(c, f);
	else if (is_a_menu_bar(mb))
		app_set_menu_bar_font(mb, f);
	else if (is_a_menu(m))
		app_set_menu_font(m, f);
	else if (is_a_menu_item(mi))
		app_set_menu_item_font(mi, f);
}

Font *gettextfont(Control *c)
{
	Window *w = (Window *) c;
	MenuBar *mb = (MenuBar *) c;
	Menu *m = (Menu *) c;
	MenuItem *mi = (MenuItem *) c;

	if (is_a_window(w))
		return app_find_default_font(app);
	else if (is_a_control(c))
		return app_get_control_font(c);
	else if (is_a_menu_bar(mb))
		return app_get_menu_bar_font(mb);
	else if (is_a_menu(m))
		return app_get_menu_font(m);
	else if (is_a_menu_item(mi))
		return app_get_menu_item_font(mi);
	return app_find_default_font(app);
}

void setforeground(Control *c, unsigned long fg)
{
	Window *w = (Window *) c;
	MenuBar *mb = (MenuBar *) c;
	Menu *m = (Menu *) c;
	MenuItem *mi = (MenuItem *) c;

	Colour col;

	col.alpha = getalpha(fg);
	col.red   = getred(fg);
	col.green = getgreen(fg);
	col.blue  = getblue(fg);

	if (is_a_window(w))
		return;
	else if (is_a_control(c))
		app_set_control_foreground(c, col);
	else if (is_a_menu_bar(mb))
		app_set_control_foreground(mb->ctrl, col);
	else if (is_a_menu(m))
		app_set_menu_foreground(m, col);
	else if (is_a_menu_item(mi))
		app_set_menu_item_foreground(mi, col);
}

unsigned long getforeground(Control *c)
{
	Colour col = BLACK;
	Window *w = (Window *) c;
	MenuBar *mb = (MenuBar *) c;
	Menu *m = (Menu *) c;
	MenuItem *mi = (MenuItem *) c;

	if (is_a_window(w))
		;
	else if (is_a_control(c))
		col = app_get_control_foreground(c);
	else if (is_a_menu_bar(mb))
		col = app_get_control_foreground(mb->ctrl);
	else if (is_a_menu(m))
		col = app_get_menu_foreground(m);
	else if (is_a_menu_item(mi))
		col = app_get_menu_item_foreground(mi);

	return colour_to_rgb(col);
}

void setbackground(Control *c, unsigned long bg)
{
	Window *w = (Window *) c;
	MenuBar *mb = (MenuBar *) c;

	Colour col;

	col.alpha = getalpha(bg);
	col.red   = getred(bg);
	col.green = getgreen(bg);
	col.blue  = getblue(bg);

	if (is_a_window(w))
		return;
	else if (is_a_control(c))
		app_set_control_background(c, col);
	else if (is_a_menu_bar(mb))
		app_set_control_background(mb->ctrl, col);
}

unsigned long getbackground(Control *c)
{
	Colour col = WHITE;
	Window *w = (Window *) c;
	MenuBar *mb = (MenuBar *) c;

	if (is_a_window(w))
		;
	else if (is_a_control(c))
		col = app_get_control_background(c);
	else if (is_a_menu_bar(mb))
		col = app_get_control_background(mb->ctrl);

	return colour_to_rgb(col);
}

void setvalue(Control *c, int value)
{
	Window *w = (Window *) c;
	MenuBar *mb = (MenuBar *) c;
	MenuItem *mi = (MenuItem *) c;

	if (is_a_window(w))
		return;
	else if (is_a_control(c))
		app_set_control_value(c, value);
	else if (is_a_menu_bar(mb))
		app_set_control_value(mb->ctrl, value);
	else if (is_a_menu_item(mi))
		app_set_menu_item_value(mi, value);
}

int getvalue(Control *c)
{
	Window *w = (Window *) c;
	MenuBar *mb = (MenuBar *) c;
	MenuItem *mi = (MenuItem *) c;

	if (is_a_window(w))
		return 0;
	else if (is_a_control(c))
		return app_get_control_value(c);
	else if (is_a_menu_bar(mb))
		return app_get_control_value(mb->ctrl);
	else if (is_a_menu_item(mi))
		return app_get_menu_item_value(mi);
	return 0;
}

void setdata(Control *c, void *data)
{
	Window *w = (Window *) c;
	MenuBar *mb = (MenuBar *) c;
	Menu *m = (Menu *) c;
	MenuItem *mi = (MenuItem *) c;

	if (is_a_window(w))
		app_set_window_data(w, data);
	else if (is_a_control(c))
		app_set_control_data(c, data);
	else if (is_a_menu_bar(mb))
		app_set_control_data(mb->ctrl, data);
	else if (is_a_menu(m))
		add_association(m, ASSOC_DATA, data);
	else if (is_a_menu_item(mi))
		mi->data = data;
	else
		add_association(c, ASSOC_DATA, data);
}

void * getdata(Control *c)
{
	Window *w = (Window *) c;
	MenuBar *mb = (MenuBar *) c;
	Menu *m = (Menu *) c;
	MenuItem *mi = (MenuItem *) c;

	if (is_a_window(w))
		return app_get_window_data(w);
	else if (is_a_control(c))
		return app_get_control_data(c);
	else if (is_a_menu_bar(mb))
		return app_get_control_data(mb->ctrl);
	else if (is_a_menu(m))
		return get_association(m, ASSOC_DATA);
	else if (is_a_menu_item(mi))
		return mi->data;
	else
		return get_association(c, ASSOC_DATA);
}

Window *parentwindow(Control *c)
{
	Window *w = (Window *) c;
	MenuBar *mb = (MenuBar *) c;
	Menu *m = (Menu *) c;
	MenuItem *mi = (MenuItem *) c;

	if (is_a_window(w))
		return w;
	else if (is_a_control(c))
		return app_parent_window(c);
	else if (is_a_menu_bar(mb))
		return app_parent_window(mb->ctrl);
	else if (is_a_menu(m))
		return app_parent_window(m->parent->ctrl);
	else if (is_a_menu_item(mi))
		return app_parent_window(mi->parent->parent->ctrl);
	return NULL;
}
