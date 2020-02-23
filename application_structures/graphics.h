
/*
	Manage kind of graphics: 3D, ISO, 2D
	
	Refactor appgraph code :

	
	inherit :
	
	-Window.h
	-Application.h
	-Bitpmap
	-Control
	-Image
	
	Functionality :
	
	ยบ Texture Object (used in: )
	ยบ Menu 
	ยบ Files ()
	
	
*/

class Point{
	
	public:
	Point(int x, int y);
	Point(int x, int y, void *tag);
	Point(Point *p);
	int x;
	int y;
	void *tag;
	
};

GraphicsExtra * extra;              /* platform-specific data */

long            pix_val;             /* current colour index */
int             line_width;         /* current pixel line width */
int             text_direction;     /* current text direction */ //Text variable it may be used only in graphics
int             xor_mode;           /* currently XOR drawing? */

Rect            area;               /* target's drawable area */
Region *        clip;               /* clip drawing to region */
Point           offset;             /* (0,0) is actually here */

CopyRectFunc    copy_rect;          /* pointer to drawing func */
FillRectFunc    fill_rect;          /* pointer to drawing func */
DrawUTF8Func    draw_utf8;          /* pointer to drawing func */
DrawLineFunc    draw_line;          /* pointer to drawing func */
 
 
typedef struct Graphics       Graphics;

/*
*  Drawing operation prototypes:
*/

typedef int (*CopyRectFunc)(Graphics *g, Point dp, Graphics *src, Rect sr);
typedef int (*FillRectFunc)(Graphics *g, Rect r);
typedef int (*DrawUTF8Func)(Graphics *g, Point p, const char *utf8, int nbytes);
typedef int (*DrawLineFunc)(Graphics *g, Point p1, Point p2);
 
  };
  
GraphicsExtra * extra;              /* platform-specific data */
Colour          colour;             /* current drawing colour */
long            pixval;             /* current colour index */
Font *          font;               /* current text font */
int             line_width;         /* current pixel line width */
int             text_direction;     /* current text direction */
int             xor_mode;           /* currently XOR drawing? */

App *           app;                /* if required */
Window *        win;                /* target window, or */
Bitmap *        bmap;               /* target bitmap, or */
Control *       ctrl;               /* target control, or */
Image *         img;                /* target image */

Rect            area;               /* target's drawable area */
Region *        clip;               /* clip drawing to region */
Point           offset;             /* (0,0) is actually here */

CopyRectFunc    copy_rect;          /* pointer to drawing func */
FillRectFunc    fill_rect;          /* pointer to drawing func */
DrawUTF8Func    draw_utf8;          /* pointer to drawing func */
DrawLineFunc    draw_line;          /* pointer to drawing func */

  
  /*
 *  Graphics:
 */

Graphics *app_get_window_graphics(Window *w);
Graphics *app_get_control_graphics(Control *c);
Graphics *app_get_bitmap_graphics(Bitmap *b);
Graphics *app_get_image_graphics(Image *img);

void	app_del_graphics(Graphics *g);

#define app_set_color(g,col)  app_set_rgb((g),(col))
#define app_set_colour(g,col) app_set_rgb((g),(col))

void	set_rgb(Graphics *g, Colour col);
void	set_rgbindex(Graphics *g, int index);

void	set_line_width(Graphics *g, int width);
void	app_set_text_direction(Graphics *g, int direction);

void	app_set_font(Graphics *g, Font *f);
void    app_set_default_font(Graphics *g);

void	app_set_clip_rect(Graphics *g, Rect r);
void	app_set_clip_region(Graphics *g, Region *rgn);

void	app_set_xor_mode(Graphics *g, Colour bgcol);
void	app_set_paint_mode(Graphics *g);