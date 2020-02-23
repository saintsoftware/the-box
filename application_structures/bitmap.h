/*

is preferable to draw the graphics on a bitmap residing in memory which can be rendered on a component whenever the a Paint() event is triggered. This avoids the problem of having to call all the Draw methods or store and replay a complex sequence of draw commands each time the graphics need to be refreshed.

Read the bitmap header, then read the data which is an array of RGB values (assuming 24bit bitmaps). DON'T read it all in one step since:
a) Structure sizes are usually multiples of 4, which 54 isn't.
b) The way variables are stored may or may not match (little big endian).

https://pt.stackoverflow.com/questions/210877/leitura-de-uma-imagem-bitmap
https://stackoverflow.com/questions/1225998/what-is-a-bitmap-in-c
https://codereview.stackexchange.com/questions/8213/bitmap-implementation

https://cboard.cprogramming.com/c-programming/50007-reading-bitmap-image.html

https://en.wikipedia.org/wiki/Bitmap
*/

#include <limits.h>    /* for CHAR_BIT */
#include <stdint.h>   /* for uint32_t */

const int BmpHeaderSize = 54;
struct BmpHeader
{
    char ID[2];
    long FileSize;
    long RESERVED;
    long BitmapDataOffset;
    long BitmapHeaderSize;
    long Width;
    long Height;
    short NrOfPlanes;
    short BitsPerPixel;
    long Compression;
    long BitmapDataSize;
    long HorizontalResolution;
    long VerticalResolution;
    long Colors;
    long ImportantColors;
};

struct BMP
{
  char Type[2];           //File type. Set to "BM".
  unsigned long Size;     //Size in BYTES of the file.
  unsigned long Reserved;      //Reserved. Set to zero.
  unsigned long OffSet;   //Offset to the data.
  unsigned long headsize; //Size of rest of header. Set to 40.
  unsigned long Width;     //Width of bitmap in pixels.
  unsigned long Height;     //  Height of bitmap in pixels.
  unsigned int  Planes;    //Number of Planes. Set to 1.
  unsigned int  BitsPerPixel;       //Number of Bits per pixels.
  unsigned long Compression;   //Compression. Usually set to 0.
  unsigned long SizeImage;  //Size in bytes of the bitmap.
  unsigned long XPixelsPreMeter;     //Horizontal pixels per meter.
  unsigned long YPixelsPreMeter;     //Vertical pixels per meter.
  unsigned long ColorsUsed;   //Number of colors used.
  unsigned long ColorsImportant;  //Number of "important" colors.
};

int bitmpa_sizeInBits;

byte * bitmap_Alloc(int sizeInBits);
void   bitmap_Free(byte * bitmap);

typedef uint32_t word_t;

enum { BITS_PER_WORD = sizeof(word_t) * CHAR_BIT };
#define WORD_OFFSET(b) ((b) / BITS_PER_WORD)
#define BIT_OFFSET(b)  ((b) % BITS_PER_WORD)

void set_bit(word_t *words, int n) { 
    words[WORD_OFFSET(n)] |= (1 << BIT_OFFSET(n));
}

void clear_bit(word_t *words, int n) {
    words[WORD_OFFSET(n)] &= ~(1 << BIT_OFFSET(n)); 
}

int get_bit(word_t *words, int n) {
    word_t bit = words[WORD_OFFSET(n)] & (1 << BIT_OFFSET(n));
    return bit != 0; 
}

typedef struct Bitmap         Bitmap;

  struct Bitmap {
	BitmapExtra *   extra;              /* platform-specific data */
	Window *        win;                /* for colour format info */
	Rect            area;               /* drawable area */
  };

/*
 *  Bitmaps:
 */

Bitmap *app_new_bitmap(Window *w, int width, int height);
void	app_del_bitmap(Bitmap *b);
Rect	app_get_bitmap_area(Bitmap *b);


/*
 *  Bitmaps.
 */

Bitmap * newbitmap(int width, int height, int depth)
{
	Bitmap *b;

	enable_drawing();

	b = app_new_bitmap(current_win, width, height);
	drawto((Control *)b);
	return b;
}

Bitmap * loadbitmap(char *name)
{
	Image *img;
	Bitmap *bmap;

	enable_drawing();

	img = app_read_image(name, 8);
	if (img == NULL)
		app_read_image(name, 32);
	if (img == NULL)
		return NULL;

	bmap = app_image_to_bitmap(current_win, img);
	app_del_image(img);
	return bmap;
}

Bitmap * imagetobitmap(Image *img)
{
	enable_drawing();

	return app_image_to_bitmap(current_win, img);
}

Bitmap * createbitmap(int width, int height, int depth, byte *data)
{
	return NULL; /* cheat because this function is deprecated */
}

void setbitmapdata(Bitmap *b, byte data[])
{
	return; /* cheat because this function is deprecated */
}

void getbitmapdata(Bitmap *b, byte data[])
{
	return; /* cheat because this function is deprecated */
}



void set_pixels(Image *img, byte pixels[])
{
	int i, w, h;
	unsigned long c;

	i = 0;
	if (img->depth == 8)
		for (h=0; h < img->height; h++)
			for (w=0; w < img->width; i++)
				img->data8[h][w] = pixels[i++];
	else
		for (h=0; h < img->height; h++)
			for (w=0; w < img->width; i++) {
				c = 0;
				c |= pixels[i++];
				c <<= 8;
				c |= pixels[i++];
				c <<= 8;
				c |= pixels[i++];
				c <<= 8;
				c |= pixels[i++];
				img->data8[h][w] = c;
			}
}

byte * get_pixels(Image *img) /* convert to a linear memory model */
{
	int i, w, h;
	byte *data;

	data = get_association(img, ASSOC_DATA);
	if (data)
		app_free(data);
	data = app_alloc(img->width * img->height * (img->depth/8));
	if (data == NULL)
		return NULL;
	add_association(img, ASSOC_DATA, data);

	if (img->depth == 8) {
		i = 0;
		for (h=0; h < img->height; h++)
			for (w=0; w < img->width; w++)
				data[i++] = img->data8[h][w];
	}
	else if (img->depth == 32) {
		i = 0;
		for (h=0; h < img->height; h++)
			for (w=0; w < img->width; w++) {
				data[i++] = img->data32[h][w].alpha;
				data[i++] = img->data32[h][w].red;
				data[i++] = img->data32[h][w].green;
				data[i++] = img->data32[h][w].blue;
			}
	}
	return data;
}



void draw_monochrome(Image *img, Rect dr, Rect sr)
{
	enable_drawing();

	app_draw_image_monochrome(gc, dr, img, sr);
}

void drawgreyscale(Image *img, Rect dr, Rect sr)
{
	enable_drawing();

	app_draw_image_greyscale(gc, dr, img, sr);
}

void drawdarker(Image *img, Rect dr, Rect sr)
{
	enable_drawing();

	app_draw_image_darker(gc, dr, img, sr);
}

void drawbrighter(Image *img, Rect dr, Rect sr)
{
	enable_drawing();

	app_draw_image_brighter(gc, dr, img, sr);
}



typedef struct
    {
        unsigned char RGB[3];
    }RGB;
 
typedef struct
    {
        unsigned int size;
        int width,height;
        unsigned short int planes;
        unsigned short int bpp;
        unsigned int compression;
        unsigned int imagesize;
        int xresolution,yresolution;
        unsigned int colours;
        unsigned int impcolours;
    }INFOHEADER;
 
// ********** Create Matrix **********

RGB** createMatrix(){
    RGB** Matrix;
    int i;
    Matrix = (RGB **) malloc (sizeof (RGB*) * height);
    if (Matrix == NULL){
        perror("***** No memory available *****");
        exit(0);
    }
    for (i=0;i<height;i++){
        Matrix[i] = (RGB *) malloc (sizeof(RGB) * width);
        if (Matrix[i] == NULL){
        perror("***** No memory available *****");
            exit(0);
        }
    }
    return(Matrix);
}
 
// ********** Verify if the file is BMP *********
void isBMP(FILE* arq, HEADER head, INFOHEADER info){
    char type[3];
    unsigned short int bpp;
    fseek(arq,0,0);
    fread(type,1,2,arq);
    type[2] = '\0';
 
    fseek(arq,28,0);
    fread(&bpp,1,2,arq);
 
    if (strcmp(type,"BM") || (bpp != 24)){
        printf("\nThe file is not BMP format or is not 24 bits\n");
            exit(0);
    }
}
 
// ********** Read BMP info from file **********
INFOHEADER readInfo(FILE* arq){
    INFOHEADER info;
 
    // Image Width in pixels
    fseek(arq,18,0);
    fread(&info.width,1,4,arq);
 
    // Image Height in pixels
    fseek(arq,22,0);
    fread(&info.height,1,4,arq);
 
    // Color depth, BPP (bits per pixel)
    fseek(arq,28,0);
    fread(&info.bpp,1,2,arq);
 
    // Compression type
    // 0 = Normmally
    // 1 = 8 bits per pixel
    // 2 = 4 bits per pixel
    fseek(arq,30,0);
    fread(&info.compression,1,4,arq);
 
    // Image size in bytes
    fseek(arq,34,0);
    fread(&info.imagesize,1,4,arq);
 
    // Number of color used (NCL)
    // value = 0 for full color set
    fseek(arq,46,0);
    fread(&info.colours,1,4,arq);
 
    // Number of important color (NIC)
    // value = 0 means all collors important
    fseek(arq,50,0);
    fread(&info.impcolours,1,4,arq);
 
    return(info);
}
 
RGB** loadImage(FILE* arq, RGB** Matrix){
    int i,j;
    RGB tmp;
    long pos = 51;
 
    fseek(arq,0,0);
 
    for (i=0; i<height; i++){
        for (j=0; j<width; j++){
            pos+= 3;
            fseek(arq,pos,0);
            fread(&tmp,(sizeof(RGB)),1,arq);
            Matrix[i][j] = tmp;
        }
    }
    return(Matrix);
}
 
 
/* Global */
int height, widht;
 
 
/* in your main program you just call */
FILE* arq; /* the bitmap file 24 bits */
RGB** Matrix_aux, Matrix;
INFOHEADER info;
info = readInfo(FILE* arq);
height = info.height;
width = info.width;
 
Matrix_aux = createMatrix();
Matrix = loadImage(arq,Matrix_aux);