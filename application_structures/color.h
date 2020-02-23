
// http://web.theurbanpenguin.com/adding-color-to-your-output-from-c/
// https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
// https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c


char color_rgb;

long current_colour_index;

static unsigned long  current_rgb       = 0UL;

typedef struct Colour      Color;
typedef struct Colour      Colour;
typedef struct Palette        Palette;

Colour          colour;             /* current drawing colour */

Colour color_background;                 /* background fill colour */
Colour color_foreground;               /* foreground draw colour */

int color_background;
int color_text;

char color_red[10] = "[0;31m";
char color_red_bold[10] = "[1;31m";

char color_green[10] = "[0;32m";
char color_green_bold[10] = "[1;32m";


char color_yellow[10] = "0;33m";
char color_yellow_bold[10] = "[01;33m";

char color_blue[10] = "[0;34m";
char color_blue_bold[10] = "[1;34m";

char color_magenta[10] = "[0;34m";
char color_magenta_bold[10] = "[1;34m";

char color_magenta[10] = "[0;35m";
char color_magenta_bold[10] = "[1;35m";

char color_cyan[10] = "[0;36m";
char color_cyan_bold[10] = "[1;36m";

//[0m	Reset

  struct Colour {
	byte  alpha;    /* transparency, 0=opaque, 255=transparent */
	byte  red;      /* intensity, 0=black, 255=bright red */
	byte  green;    /* intensity, 0=black, 255=bright green */
	byte  blue;     /* intensity, 0=black, 255=bright blue */
  };


  struct Palette {
	int             size;               /* list of colours */
	Colour *        element;
  };


/*
 *  Palettes:
 */

Palette * app_new_palette(int size, Colour *elem);
void      app_del_palette(Palette *pal);

void      app_set_window_palette(Window *w, Palette *pal);
Palette * app_get_window_palette(Window *w);

byte *    app_palette_translation(Palette *target, byte *dest, int size, Colour *elem);

/*
 *  Colour functions and constants.
 */

#define getalpha(col) (((col)>>24)&0x00FFUL)
#define getred(col)   (((col)>>16)&0x00FFUL)
#define getgreen(col) (((col)>>8)&0x00FFUL)
#define getblue(col)  ((col)&0x00FFUL)

static unsigned long colour_to_rgb(Colour col)
{
	return (  (((unsigned long)col.alpha)<<24)
		| (((unsigned long)col.red  )<<16)
		| (((unsigned long)col.green)<<8 )
		|  ((unsigned long)col.blue )     );
}

void setrgb(unsigned long c)
{
	app_set_rgb(gc, argb(getalpha(c), getred(c),
				getgreen(c), getblue(c)));
}


/*
 *  Colours:
 */

#define rgb(r,g,b)             app_new_rgb((r),(g),(b))
#define argb(a,r,g,b)          app_new_argb((a),(r),(g),(b))
#define app_new_color(r,g,b)   app_new_rgb((r),(g),(b))
#define app_new_colour(r,g,b)  app_new_rgb((r),(g),(b))

Colour	app_new_rgb(int r, int g, int b);
Colour	app_new_argb(int a, int r, int g, int b);

int 	app_rgbs_equal(Colour a, Colour b);
#define app_colors_equal(a,b)  app_rgbs_equal((a),(b))
#define app_colours_equal(a,b) app_rgbs_equal((a),(b))


/*
 *  Some standard colours:
 */

#define CLEAR           argb(0xFF,0xFF,0xFF,0xFF)

#define BLACK           rgb(0x00,0x00,0x00)
#define WHITE           rgb(0xFF,0xFF,0xFF)
#define BLUE            rgb(0x00,0x00,0xFF)
#define YELLOW          rgb(0xFF,0xFF,0x00)
#define GREEN           rgb(0x00,0xFF,0x00)
#define MAGENTA         rgb(0xFF,0x00,0xFF)
#define RED             rgb(0xFF,0x00,0x00)
#define CYAN            rgb(0x00,0xFF,0xFF)

#define GREY            rgb(0x80,0x80,0x80)
#define GRAY            rgb(0x80,0x80,0x80)
#define LIGHT_GREY      rgb(0xC0,0xC0,0xC0)
#define LIGHT_GRAY      rgb(0xC0,0xC0,0xC0)
#define PALE_GREY       rgb(0xE0,0xE0,0xE0)
#define PALE_GRAY       rgb(0xE0,0xE0,0xE0)
#define DARK_GREY       rgb(0x40,0x40,0x40)
#define DARK_GRAY       rgb(0x40,0x40,0x40)

#define DARK_BLUE       rgb(0x00,0x00,0x80)
#define DARK_GREEN      rgb(0x00,0x80,0x00)
#define DARK_RED        rgb(0x80,0x00,0x00)
#define LIGHT_BLUE      rgb(0x80,0xC0,0xFF)
#define LIGHT_GREEN     rgb(0x80,0xFF,0x80)
#define LIGHT_RED       rgb(0xFF,0xC0,0xFF)
#define PINK            rgb(0xFF,0xAF,0xAF)
#define BROWN           rgb(0x60,0x30,0x00)
#define ORANGE          rgb(0xFF,0x80,0x00)
#define PURPLE          rgb(0xC0,0x00,0xFF)
#define LIME            rgb(0x80,0xFF,0x00)
