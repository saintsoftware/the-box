/*
	Refactor appgraph code :
	
	Functionality :
	ยบ Texture Object (used in: )
	ยบ Menu 
	ยบ Files ()
	
	
	
*/

char buffer_48[48];
char buffer_64[64];
char buffer_80[80];
char buffer_128[128];
char buffer_255[255];
char buffer_512[512];
char buffer_1024[1024];	
int	x;
int	y;
float*	color;

d.dest;
set_rgb(d.hue);
draw_mode(d.mode);
moveto(d.p);
set_line_width(d.linewidth);
set_font(d.fnt);
set_cursor(d.crsr);


int current_point;
int point;
unsigned long rgb
Control *     dest;
unsigned long hue;
int           mode;
Point         p;
int           line_width;
Font *        font;
cursor        cursor;

/*
=================
Text_Draw
=================
*/
static void Text_Draw( menutext_s *t )
{
	int		x;
	int		y;
	char	buff[512];	
	float*	color;

	x = t->generic.x;
	y = t->generic.y;

	buff[0] = '\0';

	// possible label
	if (t->generic.name)
		strcpy(buff,t->generic.name);

	// possible value
	if (t->string)
		strcat(buff,t->string);
		
	if (t->generic.flags & QMF_GRAYED)
		color = text_color_disabled;
	else
		color = t->color;

	UI_DrawString( x, y, buff, t->style, color );
}

static Graphics *     gc                = NULL;

void draw_text(int x, int y, const char *text, int colorindex);
void draw_text(int x, int y, const char *text, int colorindex, int alignment);
void set_draw_surface(int surface);

typedef struct drawstruct
{
	Control *     dest;
	unsigned long hue;
	int           mode;
	Point         p;
	int           linewidth;
	Font *        fnt;
	cursor        crsr;
} drawstate;

/*
 *  Drawing operations:
 */

int 	app_copy_bits(Graphics *g, Rect r, Palette *pal, byte **rows);
int 	app_copy_rgbs(Graphics *g, Rect r, Colour **rows);

int 	app_draw_point(Graphics *g, Point p);
int 	app_draw_rect(Graphics *g, Rect r);
int 	app_draw_shadow_rect(Graphics *g, Rect r, Colour c1, Colour c2);
int 	app_draw_round_rect(Graphics *g, Rect r);
int 	app_fill_round_rect(Graphics *g, Rect r);
int 	app_draw_ellipse(Graphics *g, Rect r);
int 	app_fill_ellipse(Graphics *g, Rect r);
int 	app_draw_arc(Graphics *g, Rect r, int start_angle, int end_angle);
int 	app_fill_arc(Graphics *g, Rect r, int start_angle, int end_angle);
int 	app_draw_polyline(Graphics *g, Point *p, int n);
int 	app_draw_polygon(Graphics *g, Point *p, int n);
int 	app_fill_polygon(Graphics *g, Point *p, int n);
int 	app_texture_rect(Graphics *g, Rect dr, Graphics *src, Rect sr);
int 	app_fill_region(Graphics *g, Region *reg);

int 	app_portable_draw_line(Graphics *g, Point p1, Point p2);

/*
 *  Transfer modes for drawing operations, S=source, D=destination.
 *  The modes are arranged so that, for example, (~D)|S == notDorS.
 */

void setdrawmode(int mode) /* incomplete */
{
	Colour c;

	switch (mode) {
	 case 0x00: /* Zeros */
		app_set_rgb(gc, BLACK);
		app_set_paint_mode(gc);
		break;
	 case 0x01: /* DnorS */
		break;
	 case 0x02: /* DandnotS */
		break;
	 case 0x03: /* notS */
		c = gc->colour;
		app_set_rgb(gc, rgb(255-c.red, 255-c.green, 255-c.blue));
		app_set_paint_mode(gc);
		break;
	 case 0x04: /* notDandS */
		break;
	 case 0x05: /* notD */
		app_set_rgb(gc, WHITE);
		app_set_xor_mode(gc, WHITE);
		break;
	 case 0x06: /* DxorS */
		app_set_xor_mode(gc, WHITE);
		break;
	 case 0x07: /* DnandS */
		break;
	 case 0x08: /* DandS */
		break;
	 case 0x09: /* DxnorS */
		app_set_xor_mode(gc, BLACK);
		break;
	 case 0x0A: /* D */
		app_set_rgb(gc, CLEAR);
		break;
	 case 0x0B: /* DornotS */
		break;
	 case 0x0C: /* S */
		app_set_paint_mode(gc);
		break;
	 case 0x0D: /* notDorS */
		break;
	 case 0x0E: /* DorS */
		break;
	 case 0x0F: /* Ones */
		app_set_rgb(gc, WHITE);
		app_set_paint_mode(gc);
		break;
	 default: break;
	}
}

/*
 *  Change the drawing state.
 */

drawstate copydrawstate(void)
{
	drawstate d;
	Colour col;

	col = gc->colour;

	d.dest = current_dest;
	d.hue = colour_to_rgb(col);
	d.mode = 0x0C; /* S */
	d.p = current_point;
	d.linewidth = 1;
	d.fnt = gc->font;
	d.crsr = ArrowCursor;
	return d;
}

void setdrawstate(drawstate d)
{
	drawto(d.dest);
	setrgb(d.hue);
	setdrawmode(d.mode);
	moveto(d.p);
	setlinewidth(d.linewidth);
	setfont(d.fnt);
	setcursor(d.crsr);
}

void restoredrawstate(drawstate d)
{
	setdrawstate(d);
}

void resetdrawstate(void)
{
	setrgb(0UL);
	setdrawmode(0x0C); /* S */
	moveto(pt(0,0));
	setlinewidth(1);
	setfont(app_find_default_font(app));
	setcursor(ArrowCursor);
}


/*
 *  Find the current state of drawing.
 */

Control *currentdrawing(void)
{
	return current_dest;
}

unsigned long currentrgb(void)
{
	return current_rgb;
}

int currentmode(void)
{
	return 0x0C; /* S - a guess */
}

Point currentpoint(void)
{
	return current_point;
}

int currentlinewidth(void)
{
	return 1; /* guess */
}

Font *currentfont(void)
{
	if (gc)
		return gc->font;
	else if (app)
		return app_find_default_font(app);
	else
		return NULL;
}

/*
 *  Drawing text, selecting fonts.
 */

Font * newfont(char *name, int style, int size)
{
	return app_new_font(app, name, style, size);
}

void setfont(Font *f)
{
	app_set_font(gc, f);
}

int fontwidth(Font *f)
{
	return app_font_width(f, "W", 1); /* guess */
}

int fontheight(Font *f)
{
	return app_font_height(f);
}

int fontascent(Font *f)
{
	return app_font_height(f) * 3/4; /* guess */
}

int fontdescent(Font *f)
{
	return app_font_height(f) * 1/4; /* guess */
}

int strwidth(Font *f, char *s)
{
	return app_font_width(f, s, strlen(s));
}

Point strsize(Font *f, char *s)
{
	Point p;

	p.x = app_font_width(f, s, strlen(s));
	p.y = app_font_height(f);

	return p;
}

Rect strrect(Font *f, char *s)
{
	Rect r;

	r.x = 0;
	r.y = 0;
	r.width = app_font_width(f, s, strlen(s));
	r.height = app_font_height(f);

	return r;
}

int draw_string(Point p, char *s)
{
	draw_utf8(gc, p, s, strlen(s));
	return strwidth(gc->font, s);
}

int text_height(int width, char *s)
{
	return app_text_width(gc->font, width, s, strlen(s));
}


/*
 *  Drawing using the current colour.
 */

void move_to(Point p)
{
	current_point = p;
}

void line_to(Point p)
{
	app_draw_line(gc, current_point, p);
	current_point = p;
}

void draw_point(Point p)
{
	draw_point(gc, p);
}

void draw_line(Point p1, Point p2)
{
	draw_line(gc, p1, p2);
}

void draw_rect(Rect r)
{
	draw_rect(gc, r);
}

void fill_rect(Rect r)
{
	app_fill_rect(gc, r);
}

void draw_arc(Rect r, int start_angle, int end_angle)
{
	app_draw_arc(gc, r, start_angle, end_angle);
}

void fill_arc(Rect r, int start_angle, int end_angle)
{
	app_fill_arc(gc, r, start_angle, end_angle);
}

void draw_ellipse(Rect r)
{
	app_draw_ellipse(gc, r);
}

void fill_ellipse(Rect r)
{
	app_fill_ellipse(gc, r);
}

void draw_round_rect(Rect r)
{
	app_draw_round_rect(gc, r);
}

void fill_round_rect(Rect r)
{
	app_fill_round_rect(gc, r);
}

void draw_polygon(Point *p, int n)
{
	app_draw_polygon(gc, p, n);
}

void fill_polygon(Point *p, int n)
{
	app_fill_polygon(gc, p, n);
}


/*
 *  Drawing functions.
 */

void bitblt(Control *dst, Control *src, Point dp, Rect sr,
		int mode) /* mode is currently ignored (use S) */
{
	Graphics *g1, *g2;

	g1 = app_get_control_graphics(dst);
	g2 = app_get_control_graphics(src);

	app_copy_rect(g1, dp, g2, sr);

	del_graphics(g2);
	del_graphics(g1);
}

void scrollrect(Point dp, Rect sr)
{
	app_copy_rect(gc, dp, gc, sr);
}

void copyrect(Control *src, Point dp, Rect sr)
{
	Graphics *g2;

	g2 = app_get_control_graphics(src);

	app_copy_rect(gc, dp, g2, sr);

	app_del_graphics(g2);
}

void texture_rect(Control *src, Rect r)
{
	long x, y, sw, sh, sdx, sdy;
	long right, bottom;
	Rect sr;

	enable_drawing();

	sr = app_get_control_area(src);
	sw = r.width;
	sh = r.height;
	right = r.x+r.width;
	bottom = r.y+r.height;

	for (y=r.y; y<bottom; y+=sh)
		for (x=r.x; x<right; x+=sw) {

			/* reduce size of source rectangle for clipping */
			if (x+sw > right)	sdx = right - x;
			else			sdx = sw;
			if (y+sh > bottom)	sdy = bottom - y;
			else			sdy = sh;

			r = rect(sr.x, sr.y, sdx, sdy);
			copyrect(src, pt(x,y), r);
		}
}

void invertrect(Rect r)
{
	enable_drawing();

	app_set_rgb(gc, WHITE);
	app_set_xor_mode(gc, WHITE);
	app_fill_rect(gc, r);
	app_set_paint_mode(gc);
}




unsigned long get_pixel(Point p)
{
	return 0x00FFFFFF; /* cheat for now, return white */
}

void set_pixel(Point p, unsigned long c)
{
	enable_drawing();

	set_rgb(c);
	app_draw_point(gc, p);
}

/*
 *  Miscellany:
 */

char * new_string(char *s)
{
	return copy_string(s);
}

void del_string(char *s)
{
	del_string(s);
}

char * int_to_string(int i)
{
	char buf[80];

	sprintf(buf, "%d", i);
	return app_copy_string(buf);
}


/*
 *  A function which ensures there is a window, there is
 *  a current drawing destination, and there is a valid
 *  Graphics context for drawing to it.
 *  This function is called often within this file,
 *  to ensure the GraphApp version 2 global drawing state
 *  is valid.
 */
 
static void enable_drawing(void)
{
	if (current_dest == NULL) {
		if (current_win == NULL)
			current_win = app_new_window(app,
				rect(0,0,640,480),
				"Graphics", STANDARD_WINDOW);
		app_show_window(current_win);
		if (gc)
			app_del_graphics(gc);
		gc = app_get_window_graphics(current_win);
		current_dest = (Control *) current_win;
		return;
	}
	if (gc == NULL) {
		if (is_a_window((Window *) current_dest))
			gc = app_get_window_graphics((Window *)current_dest);
		else if (is_a_control(current_dest))
			gc = app_get_control_graphics(current_dest);
		else if (is_a_bitmap((Bitmap *) current_dest))
			gc = app_get_bitmap_graphics((Bitmap *)current_dest);
	}
}



while(draw_pixels != 0){
	
	
}