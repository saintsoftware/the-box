

// https://www.quora.com/How-can-I-display-image-in-C
// https://www.programiz.com/c-programming/c-dynamic-memory-allocation
// https://overiq.com/c-programming-101/the-calloc-function-in-c/

//http://gigi.nullneuron.net/gigilabs/loading-images-in-sdl2-with-sdl_image/

// https://www.lemoda.net/c/

// ========== DECLERATION =================

// context structure is our basic context used by all images, so it

char images[]; 

*img_buffer;
*img_buffer_end; 
*img_buffer_original; 
*img_buffer_original_end;
int read_from_callbacks;
int buflen;
int img_n, 
int img_out_n;
buffer_start[128];
uint32 img_width;
uint32 img_height;
io_callbacks io;
void *io_user_data;

int row;

static int vertically_flip_on_load = 0;

int bits_per_channel;
int num_channels;
int channel_order;

int ORDER_RGB; 
int ORDER_BGR;

int (*read)  (void *user,char *data,int size);   // fill 'data' with 'size' bytes.  return number of bytes actually read
void (*skip)  (void *user,int n);                 // skip the next 'n' bytes, or 'unget' the last -n bytes if negative
int (*eof)   (void *user);                       // returns nonzero if we are at end of file/data


const *buffer; 
int len; 
int *output_width; //-- outputs image width in pixels
int *output_height; //-- outputs image height in pixels
int *y; 
int *channels_in_file; 
int desired_channels;

const *clbk;
void *user;

char image_Type[2];           //File type. Set to "BM".
unsigned long image_Size;     //Size in BYTES of the file.
unsigned long image_Reserved;      //Reserved. Set to zero.
unsigned long image_Offet;   //Offset to the data.
unsigned long image_headsize; //Size of rest of header. Set to 40.
unsigned long image_Width;     //Width of bitmap in pixels.
unsigned long image_Height;     //  Height of bitmap in pixels.
unsigned int  image_Planes;    //Number of Planes. Set to 1.
unsigned int  image_BitsPerPixel;       //Number of Bits per pixels.
unsigned long image_Compression;   //Compression. Usually set to 0.
unsigned long image_SizeImage;  //Size in bytes of the bitmap.
unsigned long image_XPixelsPreMeter;     //Horizontal pixels per meter.
unsigned long image_YPixelsPreMeter;     //Vertical pixels per meter.
unsigned long image_ColorsUsed;   //Number of colors used.
unsigned long image_ColorsImportant;  //Number of "important" colors.
int image_color;
int image_gd ; //gd = VGA ;
int image_gm ;  gm = VGAHI;

int image_VGA;
int image_buffer;
extern int image_VGAHI;
int compression_level = 0;
int image_quality = 0 ;

extern uint8_t* src;
extern uint8_t* dst;

extern uint8_t ;
extern uint16_t;
extern uint32_t;
extern uint64_t;

image_default = 0, // only used for desired_channels
image_grey       = 1,
image_grey_alpha = 2,
image_rgb        = 3,
image_rgb_alpha  = 4

image_SCAN_load=0,
image_SCAN_type,
image_SCAN_header

typedef unsigned char stbi_uc;
typedef unsigned short stbi_us;

/*
 *  ImageReader call-backs:
 */

typedef int (*ImageMessageFunc) (ImageReader *reader, char *message);
typedef int (*ImageProgressFunc)(ImageReader *reader);

/*
 *  Image Lists:
 */

ImageList * app_new_image_list(void);
void	app_del_image_list(ImageList *imglist);
void	app_append_to_image_list(ImageList *imglist, Image *img);


/*
 *  Image Readers:
 */

enum ImageReaderState {
	STOPPED         = 0,    /* at start or end of processing */
	STARTING,               /* creating data structures */
	DITHERING,              /* now dithering to a palette */
	RENDERING,              /* processing lines of pixels */
	IMAGE_ERROR     = -1    /* an error has happened */
};

enum ImageFormat {
	PNG_FORMAT      = 1,    /* Portable Network Graphics */
	JPEG_FORMAT     = 2,    /* Joint Photographic Experts Group */
	GIF_FORMAT      = 3,    /* Graphic Interchange Format */
	GA_H_FORMAT     = 4,    /* GraphApp header image file format */
	UNKNOWN_FORMAT  = -1
};

ImageReader * app_new_image_reader(void);
void          app_del_image_reader(ImageReader *reader);

Image * read_image(const char *filename, int required_depth);
Image * read_image_file(FILE *file, int required_depth);
Image * read_image_memory(const byte *memsrc, int memsize, int required_depth);
Image * read_image_progressively(ImageReader *reader);
int     find_image_format(FILE *file);
int    find_image_format_in_memory(byte *memsrc, int memsize);


int     app_write_image(Image *img, const char *filename);
int     app_write_image_at(Image *img, const char *filename, int dpi, int interlace);



 typedef struct Image          Image;
  typedef struct ImageList      ImageList;
  typedef struct ImageReader    ImageReader;

  struct Image {
	int             depth;              /* 8 (indexed), 32 (direct) */
	int             width;              /* in pixels */
	int             height;             /* in pixels */
	int             cmap_size;          /* indexed list of colours */
	Colour *        cmap;
	byte **         data8;              /* indexed 8-bit data, or */
	Colour **       data32;             /* direct 32-bit data */
  };

  struct ImageList {
	int             num_images;         /* list of images */
	Image **        images;
  };

  struct ImageReader {
	char *              filename;           /* user-given fields */
	FILE *              file;               /* file to read from */
	byte *              memsrc;             /* memory source to read from */
	int                 memsize;            /* byte size of memory source */
	Palette *           src_pal;            /* dither to this palette */
	int                 max_cmap_size;      /* only use this many colours */
	int                 required_depth;     /* 8 or 32 */

	ImageMessageFunc    message_func;       /* to report some problem */
	ImageProgressFunc   error_func;         /* if error occurs, tidy up */
	ImageProgressFunc   startup_func;       /* called before starting */
	ImageProgressFunc   after_dither_func;  /* called after dithering */
	ImageProgressFunc   progress_func;      /* called after each line */
	ImageProgressFunc   rendering_func;     /* called after each line */
	ImageProgressFunc   success_func;       /* called after success */
	void *              user_data;          /* user-defined data */

	int                 state;              /* DITHERING, RENDERING etc */
	int                 bytes_read;         /* header bytes read already */
	int                 stage;              /* 1 <= stage <= max_stages */
	int                 max_stages;         /* total stages to happen */
	int                 row;                /* 0 <= row < height, random */
	int                 rows_done;          /* 0,1,2,...,height, ordered */
	int                 row_height;         /* height of current stage */
	int                 width;              /* in pixels */
	int                 height;             /* in pixels */
	byte **             data8;              /* implies palette */
	Colour **           data32;             /* implies no palette */
	Palette *           pal;                /* if data8 used */
  };

/*
 *  Images:
 */

Image *	app_new_image(int width, int height, int depth);
void	app_del_image(Image *img);

Rect	app_get_image_area(const Image *img);
Rect	app_get_image_rect(const Image *img);

Image *	app_copy_image(const Image *img);
void	app_set_image_cmap(Image *img, int cmap_size, Colour *cmap);

int 	app_image_has_transparent_pixels(const Image *img);

Image *	app_image_convert_32_to_8(const Image *img);
Image *	app_image_convert_8_to_32(const Image *img);
void	app_image_sort_palette(Image *img);
Image *	app_scale_image(const Image *src, Rect dr, Rect sr);

int 	app_draw_image(Graphics *g, Rect dr, Image *img, Rect sr);
int 	app_draw_image_monochrome(Graphics *g, Rect dr, Image *src, Rect sr);
int 	app_draw_image_greyscale(Graphics *g, Rect dr, Image *src, Rect sr);
int 	app_draw_image_darker(Graphics *g, Rect dr, Image *src, Rect sr);
int 	app_draw_image_brighter(Graphics *g, Rect dr, Image *src, Rect sr);

int 	app_image_find_colour(const Image *img, Colour col);

Bitmap *app_image_to_bitmap(Window *win, Image *img);
Image *	app_bitmap_to_image(Bitmap *bmp);

static void stbi__refill_buffer(stbi__context *s)
{
   int n = (s->io.read)(s->io_user_data,(char*)s->buffer_start,s->buflen);
   
   if (n == 0) {
	   
      // at end of file, treat same as if from memory, but need to handle case
      // where s->img_buffer isn't pointing to safe memory, e.g. 0-byte file
      s->read_from_callbacks = 0;
      s->img_buffer = s->buffer_start;
      s->img_buffer_end = s->buffer_start+1;
      *s->img_buffer = 0;
   } 
   else {
      s->img_buffer = s->buffer_start;
      s->img_buffer_end = s->buffer_start + n;
   }
}



static int stbi__getn(stbi__context *s, stbi_uc *buffer, int n)
{
   if (s->io.read) {
      int blen = (int) (s->img_buffer_end - s->img_buffer);
      if (blen < n) {
         int res, count;

         memcpy(buffer, s->img_buffer, blen);

         count = (s->io.read)(s->io_user_data, (char*) buffer + blen, n - blen);
         res = (count == (n-blen));
         s->img_buffer = s->img_buffer_end;
         return res;
      }
   }

   if (s->img_buffer+n <= s->img_buffer_end) {
      memcpy(buffer, s->img_buffer, n);
      s->img_buffer += n;
      return 1;
   } else
      return 0;
}

static int stbi__get16be(stbi__context *s)
{
   int z = stbi__get8(s);
   return (z << 8) + stbi__get8(s);
}

static stbi__uint32 stbi__get32be(stbi__context *s)
{
   stbi__uint32 z = stbi__get16be(s);
   return (z << 16) + stbi__get16be(s);
}

#if defined(STBI_NO_BMP) && defined(STBI_NO_TGA) && defined(STBI_NO_GIF)
// nothing
#else
static int stbi__get16le(stbi__context *s)
{
   int z = stbi__get8(s);
   return z + (stbi__get8(s) << 8);
}
#endif

#ifndef STBI_NO_BMP
static stbi__uint32 stbi__get32le(stbi__context *s)
{
   stbi__uint32 z = stbi__get16le(s);
   return z + (stbi__get16le(s) << 16);
}
#endif

#define STBI__BYTECAST(x)  ((stbi_uc) ((x) & 255))  // truncate int to byte without warnings

// STB


static void private_init_blit_rects (
	const LIImgImage*   dstimg,
	const LIImgImage*   srcimg,
	const LIMatRectInt* dst,
	const LIMatRectInt* src,
	LIMatRectInt*       dst1,
	LIMatRectInt*       src1
);




/*****************************************************************************/

/**
 * \brief Creates a new empty image.
 * \return New image or NULL.
 */

Image* image_new (){

	Image* self;

	self = lisys_calloc (1, sizeof (Image));

	if (self == NULL){
		return NULL;
	}

	return self;
}

/**
 * \brief Loads an image from a file.
 * \param path Path to the image file.
 * \return New image or NULL.
 */

Image* image_new_from_file (const char* path){

	Image* self;

	self = image_new ();

	if (self == NULL)
		return NULL;
	if (!liimg_image_load_png (self, path) && !liimg_image_load_dds (self, path)){

		image_free (self);
		return NULL;
	}

	return self;
}

/**
 * \brief Creates a copy of the image.
 * \param image Image.
 * \return New image or NULL.
 */

LIImgImage* liimg_image_new_from_image (
	const LIImgImage* image)
{
	LIImgImage* self;

	self = lisys_calloc (1, sizeof (LIImgImage));
	if (self == NULL)
		return NULL;
	self->width = image->width;
	self->height = image->height;
	if (self->width && self->height)
	{
		self->pixels = lisys_malloc (4 * self->width * self->height * sizeof (uint8_t));
		if (self->pixels == NULL)
		{
			lisys_free (self);
			return NULL;
		}
		memcpy (self->pixels, image->pixels, 4 * self->width * self->height * sizeof (uint8_t));
	}

	return self;
}

/**
 * \brief Frees the image.
 * \param self Image.
 */

void liimg_image_free (LIImgImage* self)
{
	lisys_free (self->pixels);
	lisys_free (self);
}

/**
 * \brief Alters the color of the image in the HSV color space.
 * \param self Image.
 * \param hue_add Amount to add to hue. The hue range is [0,1].
 * \param sat_add Amount to add to saturation. The saturation range is [0,1].
 * \param val_add Amount to add to value. The value range is [0,1].
 */

void liimg_image_add_hsv (
	LIImgImage* self,
	float       hue_add,
	float       sat_add,
	float       val_add)
{
	uint8_t* dst;
	LIImgColor rgb;
	LIImgColorHSV hsv;

	for (y = 0 ; y < self->height ; y++)
	{
		for (x = 0 ; x < self->width ; x++)
		{
			/* Get the pixel. */
			dst = self->pixels + 4 * (x + y * self->width);

			/* Perform the HSV modification. */
			rgb.r = dst[0];
			rgb.g = dst[1];
			rgb.b = dst[2];
			liimg_color_rgb_to_hsv (&rgb, &hsv);
			hsv.h = fmodf (hsv.h + hue_add, 1.0f);
			hsv.s = LIMAT_CLAMP (hsv.s + sat_add, 0.0f, 1.0f);
			hsv.v = LIMAT_CLAMP (hsv.v + val_add, 0.0f, 1.0f);
			liimg_color_hsv_to_rgb (&hsv, &rgb);

			/* Replace the old pixel. */
			dst[0] = rgb.r;
			dst[1] = rgb.g;
			dst[2] = rgb.b;
		}
	}
}

/**
 * \brief Adds HSV color with V channel weighting.
 * \param self Image.
 * \param hue_add Amount to add to hue. The hue range is [0,1].
 * \param sat_add Amount to add to saturation. The saturation range is [0,1].
 * \param val_add Amount to add to value. The value range is [0,1].
 * \param val_range Value ranged affected by weighting.
 */

void liimg_image_add_hsv_weightv (
	LIImgImage* self,
	float       hue_add,
	float       sat_add,
	float       val_add,
	float       val_range)
{
	int x;
	int y;
	float w;
	uint8_t* dst;
	LIImgColor rgb;
	LIImgColorHSV hsv;

	for (y = 0 ; y < self->height ; y++)
	{
		for (x = 0 ; x < self->width ; x++)
		{
			/* Get the pixel. */
			dst = self->pixels + 4 * (x + y * self->width);

			/* Calculate the HSV color. */
			rgb.r = dst[0];
			rgb.g = dst[1];
			rgb.b = dst[2];
			liimg_color_rgb_to_hsv (&rgb, &hsv);

			/* Calculate the weight. */
			if (hsv.v < val_range)
				w = limat_smoothstep (hsv.v, 0.0f, val_range);
			else if (1.0f - hsv.v < val_range)
				w = limat_smoothstep (1.0f - hsv.v, 0.0f, val_range);
			else
				w = 1.0f;

			/* Perform the HSV modification. */
			hsv.h = fmodf (hsv.h + hue_add, 1.0f);
			hsv.s = LIMAT_CLAMP (hsv.s + w * sat_add, 0.0f, 1.0f);
			hsv.v = LIMAT_CLAMP (hsv.v + w * val_add, 0.0f, 1.0f);
			liimg_color_hsv_to_rgb (&hsv, &rgb);

			/* Replace the old pixel. */
			dst[0] = rgb.r;
			dst[1] = rgb.g;
			dst[2] = rgb.b;
		}
	}
}

/**
 * \brief Allocates or reallocates the pixels.
 * \param self Image.
 * \param w Width.
 * \param h Height.
 * \return One on success. Zero otherwise.
 */

int liimg_image_alloc (
	LIImgImage* self,
	int         w,
	int         h)
{
	void* tmp;
	if (w && h)
	{
		tmp = lisys_calloc (1, 4 * w * h);
		if (tmp == NULL)
			return 0;
		self->width = w;
		self->height = h;
		self->pixels = tmp;
	}
	else
	{
		lisys_free (self->pixels);
		self->width = w;
		self->height = h;
		self->pixels = NULL;
	}

	return 1;
}

/**
 * \brief Blits another image over this one.
 * \param self Image.
 * \param image Image.
 * \param dst_rect Destination rectangle. NULL for default.
 * \param src_rect Source rectangle. NULL for default.
 */

void liimg_image_blit (
	LIImgImage*         self,
	LIImgImage*         image,
	const LIMatRectInt* dst_rect,
	const LIMatRectInt* src_rect)
{
	int x;
	int y;
	int a1;
	int a2;
	uint8_t* src;
	uint8_t* dst;
	LIMatRectInt src1;
	LIMatRectInt dst1;

	private_init_blit_rects (self, image, dst_rect, src_rect, &dst1, &src1);
	for (y = 0 ; y < src1.height ; y++)
	{
		for (x = 0 ; x < src1.width ; x++)
		{
			src = image->pixels + 4 * ((x + src1.x) + (y + src1.y) * image->width);
			dst = self->pixels + 4 * ((x + dst1.x) + (y + dst1.y) * self->width);
			a1 = src[3];
			a2 = 256 - a1;
			dst[0] = (src[0] * a1 + dst[0] * a2) >> 8;
			dst[1] = (src[1] * a1 + dst[1] * a2) >> 8;
			dst[2] = (src[2] * a1 + dst[2] * a2) >> 8;
			dst[3] = LIMAT_MIN (255, dst[3] + a1);
		}
	}
}

/**
 * \brief Blits an HSV altered image over this one.
 * \param self Image.
 * \param image Image.
 * \param dst_rect Destination rectangle. NULL for default.
 * \param src_rect Source rectangle. NULL for default.
 * \param hue_add Amount to add to hue. The hue range is [0,1].
 * \param sat_add Amount to add to saturation. The saturation range is [0,1].
 * \param val_add Amount to add to value. The value range is [0,1].
 */
void liimg_image_blit_hsv_add (
	LIImgImage*         self,
	LIImgImage*         image,
	const LIMatRectInt* dst_rect,
	const LIMatRectInt* src_rect,
	float               hue_add,
	float               sat_add,
	float               val_add)
{
	int x;
	int y;
	int a1;
	int a2;
	uint8_t* src;
	uint8_t* dst;
	LIImgColor rgb;
	LIImgColorHSV hsv;
	LIMatRectInt src1;
	LIMatRectInt dst1;

	private_init_blit_rects (self, image, dst_rect, src_rect, &dst1, &src1);
	for (y = 0 ; y < src1.height ; y++)
	{
		for (x = 0 ; x < src1.width ; x++)
		{
			/* Get the pixels. */
			src = image->pixels + 4 * ((x + src1.x) + (y + src1.y) * image->width);
			dst = self->pixels + 4 * ((x + dst1.x) + (y + dst1.y) * self->width);

			/* Perform the HSV modification. */
			rgb.r = src[0];
			rgb.g = src[1];
			rgb.b = src[2];
			liimg_color_rgb_to_hsv (&rgb, &hsv);
			hsv.h = fmodf (hsv.h + hue_add, 1.0f);
			hsv.s = LIMAT_CLAMP (hsv.s + sat_add, 0.0f, 1.0f);
			hsv.v = LIMAT_CLAMP (hsv.v + val_add, 0.0f, 1.0f);
			liimg_color_hsv_to_rgb (&hsv, &rgb);

			/* Blit to the destination image. */
			a1 = src[3];
			a2 = 256 - a1;
			dst[0] = (rgb.r * a1 + dst[0] * a2) >> 8;
			dst[1] = (rgb.g * a1 + dst[1] * a2) >> 8;
			dst[2] = (rgb.b * a1 + dst[2] * a2) >> 8;
			dst[3] = LIMAT_MIN (255, dst[3] + a1);
		}
	}
}

/**
 * \brief Blits an HSV altered image over this one, using V channel weighting.
 * \param self Image.
 * \param image Image.
 * \param dst_rect Destination rectangle. NULL for default.
 * \param src_rect Source rectangle. NULL for default.
 * \param hue_add Amount to add to hue. The hue range is [0,1].
 * \param sat_add Amount to add to saturation. The saturation range is [0,1].
 * \param val_add Amount to add to value. The value range is [0,1].
 * \param val_range Value ranged affected by weighting.
 */

void liimg_image_blit_hsv_add_weightv (
	LIImgImage*         self,
	LIImgImage*         image,
	const LIMatRectInt* dst_rect,
	const LIMatRectInt* src_rect,
	float               hue_add,
	float               sat_add,
	float               val_add,
	float               val_range)
{
	int x;
	int y;
	int a1;
	int a2;
	float w;
	uint8_t* src;
	uint8_t* dst;
	LIImgColor rgb;
	LIImgColorHSV hsv;
	LIMatRectInt src1;
	LIMatRectInt dst1;

	private_init_blit_rects (self, image, dst_rect, src_rect, &dst1, &src1);
	for (y = 0 ; y < src1.height ; y++)
	{
		for (x = 0 ; x < src1.width ; x++)
		{
			/* Get the pixels. */
			src = image->pixels + 4 * ((x + src1.x) + (y + src1.y) * image->width);
			dst = self->pixels + 4 * ((x + dst1.x) + (y + dst1.y) * self->width);

			/* Calculate the HSV color. */
			rgb.r = src[0];
			rgb.g = src[1];
			rgb.b = src[2];
			liimg_color_rgb_to_hsv (&rgb, &hsv);

			/* Calculate the weight. */
			if (hsv.v < val_range)
				w = limat_smoothstep (hsv.v, 0.0f, val_range);
			else if (1.0f - hsv.v < val_range)
				w = limat_smoothstep (1.0f - hsv.v, 0.0f, val_range);
			else
				w = 1.0f;

			/* Perform the HSV modification. */
			hsv.h = fmodf (hsv.h + hue_add, 1.0f);
			hsv.s = LIMAT_CLAMP (hsv.s + w * sat_add, 0.0f, 1.0f);
			hsv.v = LIMAT_CLAMP (hsv.v + w * val_add, 0.0f, 1.0f);
			liimg_color_hsv_to_rgb (&hsv, &rgb);

			/* Blit to the destination image. */
			a1 = src[3];
			a2 = 256 - a1;
			dst[0] = (rgb.r * a1 + dst[0] * a2) >> 8;
			dst[1] = (rgb.g * a1 + dst[1] * a2) >> 8;
			dst[2] = (rgb.b * a1 + dst[2] * a2) >> 8;
			dst[3] = LIMAT_MIN (255, dst[3] + a1);
		}
	}
}

/**
 * \brief Fills the image.
 * \param self Image.
 * \param color Color.
 */
void liimg_image_fill (
	LIImgImage*       self,
	const LIImgColor* color)
{
	int i;
	int n;
	uint8_t* pixel;

	n = 4 * self->width * self->height;
	for (i = 0 ; i < n ; i += 4)
	{
		pixel = self->pixels + i;
		pixel[0] = color->r;
		pixel[1] = color->g;
		pixel[2] = color->b;
		pixel[3] = color->a;
	}
}

/**
 * \brief Loads the image from a DDS file.
 * \param self Image.
 * \param path Path to the file.
 * \return Nonzero on success.
 */
int liimg_image_load_dds (
	LIImgImage* self,
	const char* path)
{
	int type;
	void* pixels;
	FILE* file;
	LIImgDDS dds;
	LIImgDDSFormat fmt;
	LIImgDDSLevel lvl;

	/* Read header. */
	file = fopen (path, "rb");
	if (file == NULL)
		return 0;
	if (!liimg_dds_read_header (&dds, file))
	{
		fclose (file);
		return 0;
	}
	fmt = dds.info;

	/* Read pixels. */
	if (!liimg_dds_read_level (&dds, file, 0, &lvl))
	{
		fclose (file);
		return 0;
	}
	fclose (file);

	/* Uncompress pixels. */
	pixels = lisys_calloc (1, 4 * lvl.width * lvl.height);
	if (pixels == NULL)
		return 0;
	switch (fmt.type)
	{
		case DDS_TYPE_DXT1: type = 1; break;
		case DDS_TYPE_DXT3: type = 3; break;
		case DDS_TYPE_DXT5: type = 5; break;
		default:
			type = 0;
			break;
	}
	if (type)
	{
#ifdef HAVE_SQUISH
		liimg_compress_uncompress (lvl.data, lvl.width, lvl.height, type, pixels);
#else
		lisys_error_set (EINVAL, "loading compressed textures requires libsquish");
		lisys_free (pixels);
		return 0;
#endif
	}
	else
		memcpy (pixels, lvl.data, 4 * lvl.width * lvl.height);
	lisys_free (lvl.data);

	/* Use the new pixels. */
	lisys_free (self->pixels);
	self->pixels = pixels;
	self->width = lvl.width;
	self->height = lvl.height;

	return 1;
}

/**
 * \brief Loads the image from a PNG file.
 * \param self Image.
 * \param path Path to the file.
 * \return Nonzero on success.
 */
int liimg_image_load_png (
	LIImgImage* self,
	const char* path)
{
	return liimg_png_load (path, &self->width, &self->height, &self->pixels);
}

/**
 * \brief Replaces the contents of the image with that of another.
 * \param self Image.
 * \param image Image.
 * \return One on success. Zero otherwise.
 */
int liimg_image_replace (
	LIImgImage*       self,
	const LIImgImage* image)
{
	void* pixels = NULL;

	if (image->width && image->height)
	{
		pixels = lisys_malloc (4 * image->width * image->height * sizeof (uint8_t));
		if (pixels == NULL)
			return 0;
		memcpy (pixels, image->pixels, 4 * image->width * image->height * sizeof (uint8_t));
	}
	lisys_free (self->pixels);
	self->pixels = pixels;
	self->width = image->width;
	self->height = image->height;

	return 1;
}

/**
 * \brief Creates an uncompressed DDS file.
 * \param self Image.
 * \param path Path to the file.
 * \return Nonzero on success.
 */
int liimg_image_save_rgba (
	LIImgImage* self,
	const char* path)
{
	int w;
	int h;
	FILE* file;
	LIImgDDS dds;

	/* Create a DDS file. */
	file = fopen (path, "wb");
	if (file == NULL)
	{
		lisys_error_set (EIO, NULL);
		return 0;
	}
	liimg_dds_init_rgba (&dds, self->width, self->height, 0); /* FIXME: No mipmaps. */
	liimg_dds_write_header (&dds, file);

	/* Write each mipmap level. */
	w = self->width;
	h = self->height;
	while (w || h)
	{
		w = w? w : 1;
		h = h? h : 1;
		liimg_dds_write_level (&dds, file, 0, self->pixels, 4 * w * h);
		w >>= 1;
		h >>= 1;
		break; /* FIXME: No mipmaps. */
	}
	fclose (file);

	return 1;
}

/**
 * \brief Creates an S3TC/DXT5 compressed DDS file.
 *
 * \warning Does in-place modifications to the image during mipmap generation,
 * destroying the old pixel data and setting the size of the image to 1x1.
 *
 * \param self Image.
 * \param path Path to the file.
 * \return Nonzero on success.
 */
int liimg_image_save_s3tc (
	LIImgImage* self,
	const char* path)
{
#ifdef HAVE_SQUISH
	int w;
	int h;
	int maps;
	int size;
	FILE* file;
	char* bytes;
	LIImgDDS dds;

	/* Allocate buffers. */
	bytes = lisys_malloc (4 * self->width * self->height);
	if (bytes == NULL)
		return 0;

	/* Get mipmap count. */
	w = self->width;
	h = self->height;
	size = w > h? w : h;
	for (maps = 0 ; size ; size >>= 1)
		maps++;

	/* Create a DDS file. */
	file = fopen (path, "wb");
	if (file == NULL)
	{
		lisys_error_set (EIO, NULL);
		lisys_free (bytes);
		return 0;
	}
	size = liimg_compress_storage (self->width, self->height, 5);
	liimg_dds_init_s3tc (&dds, self->width, self->height, size, maps);
	liimg_dds_write_header (&dds, file);

	/* Write each mipmap level. */
	while (maps--)
	{
		liimg_compress_compress (self->pixels, w, h, 5, bytes);
		liimg_dds_write_level (&dds, file, 0, bytes, liimg_compress_storage (w, h, 5));
		w >>= 1;
		h >>= 1;
		w = w? w : 1;
		h = h? h : 1;
		liimg_image_shrink_half (self);
	}
	lisys_free (bytes);
	fclose (file);

	return 1;
#else
	lisys_error_set (EINVAL, "saving compressed textures requires libsquish");
	return 0;
#endif
}

/**
 * \brief Shinks the image to half of the original size.
 *
 * Uses a fast in-place algorithm for shrinking the image. The resulting image
 * is half of the original size and has width and height of at least one so it
 * can be used as the next mipmap level of the original image.
 *
 * \param self Image.
 */
void liimg_image_shrink_half (
	LIImgImage* self)
{
	int x;
	int y;
	int len;
	unsigned char tmp[16];
	unsigned char* dst;
	unsigned char* src0;
	unsigned char* src1;

	dst = self->pixels;
	src0 = self->pixels;
	if (self->width > 1 && self->height > 1)
	{
		len = 4 * self->width;
		src1 = src0 + len;
		for (y = 0 ; y < self->height ; y += 2)
		{
			for (x = 0 ; x < self->width ; x += 2)
			{
				tmp[0] = *(src0++) >> 2;
				tmp[1] = *(src0++) >> 2;
				tmp[2] = *(src0++) >> 2;
				tmp[3] = *(src0++) >> 2;
				tmp[4] = *(src0++) >> 2;
				tmp[5] = *(src0++) >> 2;
				tmp[6] = *(src0++) >> 2;
				tmp[7] = *(src0++) >> 2;
				tmp[8] = *(src1++) >> 2;
				tmp[9] = *(src1++) >> 2;
				tmp[10] = *(src1++) >> 2;
				tmp[11] = *(src1++) >> 2;
				tmp[12] = *(src1++) >> 2;
				tmp[13] = *(src1++) >> 2;
				tmp[14] = *(src1++) >> 2;
				tmp[15] = *(src1++) >> 2;
				*(dst++) = tmp[0] + tmp[4] + tmp[8] + tmp[12];
				*(dst++) = tmp[1] + tmp[5] + tmp[9] + tmp[13];
				*(dst++) = tmp[2] + tmp[6] + tmp[10] + tmp[14];
				*(dst++) = tmp[3] + tmp[7] + tmp[11] + tmp[15];
			}
			src0 += len;
			src1 += len;
		}
		self->width = self->width >> 1;
		self->height = self->height >> 1;
	}
	else if (self->width > 1 || self->height > 1)
	{
		len = 2 * self->width * self->height;
		while (len--)
		{
			tmp[0] = *(src0++) >> 1;
			tmp[1] = *(src0++) >> 1;
			tmp[2] = *(src0++) >> 1;
			tmp[3] = *(src0++) >> 1;
			tmp[4] = *(src0++) >> 1;
			tmp[5] = *(src0++) >> 1;
			tmp[6] = *(src0++) >> 1;
			tmp[7] = *(src0++) >> 1;
			*(dst++) = tmp[0] + tmp[4];
			*(dst++) = tmp[1] + tmp[5];
			*(dst++) = tmp[2] + tmp[6];
			*(dst++) = tmp[3] + tmp[7];
		}
		if (self->width > 1)
			self->width = self->width >> 1;
		else
			self->height = self->height >> 1;
	}
}

/**
 * \brief Gets the color of the pixel.
 * \param self Image.
 * \param x X coordinate.
 * \param y Y coordinate.
 * \return Color.
 */
LIImgColor liimg_image_get_pixel (
	const LIImgImage* self,
	int               x,
	int               y)
{
	LIImgColor color;
	const uint8_t* pixel;

	pixel = self->pixels + 4 * (x + y * self->width);
	color.r = pixel[0];
	color.g = pixel[1];
	color.b = pixel[2];
	color.a = pixel[3];

	return color;
}

/**
 * \brief Sets the color of the pixel.
 * \param self Image.
 * \param x X coordinate.
 * \param y Y coordinate.
 * \param color Color.
 */
void liimg_image_set_pixel (
	LIImgImage*       self,
	int               x,
	int               y,
	const LIImgColor* color)
{
	uint8_t* pixel;

	pixel = self->pixels + 4 * (x + y * self->width);
	pixel[0] = color->r;
	pixel[1] = color->g;
	pixel[2] = color->b;
	pixel[3] = color->a;
}

/*****************************************************************************/

static void private_init_blit_rects (
	const LIImgImage*   dstimg,
	const LIImgImage*   srcimg,
	const LIMatRectInt* dst,
	const LIMatRectInt* src,
	LIMatRectInt*       dst1,
	LIMatRectInt*       src1)
{
	int max_w;
	int max_h;

	/* Initialize the rectangles. */
	if (dst == NULL)
	{
		dst1->x = 0;
		dst1->y = 0;
		dst1->width = dstimg->width;
		dst1->height = dstimg->height;
	}
	else
		*dst1 = *dst;
	if (src == NULL)
	{
		src1->x = 0;
		src1->y = 0;
		src1->width = srcimg->width;
		src1->height = srcimg->height;
	}
	else
		*src1 = *src;

	/* Clip the top-left destination corner. */
	if (dst1->x < 0)
	{
		src1->x -= dst1->x;
		src1->width += dst1->x;
		dst1->x = 0;
	}
	if (dst1->y < 0)
	{
		src1->y -= dst1->y;
		src1->height += dst1->y;
		dst1->y = 0;
	}

	/* Clip the top-left source corner. */
	if (src1->x < 0)
	{
		dst1->x -= src1->x;
		dst1->width += src1->x;
		src1->x = 0;
	}
	if (src1->y < 0)
	{
		dst1->y -= src1->y;
		dst1->height += src1->y;
		src1->y = 0;
	}

	/* Clip the bottom-right destination corner. */
	max_w = dstimg->width - dst1->x;
	max_h = dstimg->height - dst1->y;
	if (dst1->width > max_w)
	{
		src1->width -= (dst1->width - max_w);
		dst1->width = max_w;
	}
	if (dst1->height > max_h)
	{
		src1->height -= (dst1->height - max_h);
		dst1->height = max_h;
	}

	/* Clip the bottom-right source corner. */
	max_w = srcimg->width - src1->x;
	max_h = srcimg->height - src1->y;
	if (src1->width > max_w)
	{
		dst1->width -= (src1->width - max_w);
		src1->width = max_w;
	}
	if (src1->height > max_h)
	{
		dst1->height -= (src1->height - max_h);
		src1->height = max_h;
	}

	/* Restrict to the smaller rectangle. */
	src1->width = LIMAT_MIN (src1->width, dst1->width);
	src1->height = LIMAT_MIN (src1->height, dst1->height);
	dst1->width = src1->width;
	dst1->height = src1->height;
}

/** @} */
/** @} */


/*
	#define STB_DEFINE
	#define STB_IMAGE_IMPLEMENTATION
	#define STBI_ASSERT(x) //before the #include to avoid using assert.h.
    #define STBI_MALLOC  // to avoid using malloc,realloc,free
	#define STBI_REALLOC
	#define STBI_FREE
	#define STBI_VERSION 1

	//#define STBI_MALLOC(sz)           malloc(sz)
    //#define STBI_REALLOC(p,newsz)     realloc(p,newsz)
    //#define STBI_FREE(p)              free(p)

	//#define STBI_NO_STDIO //#include <stdio.h>

	#define STBI_INCLUDE_STB_IMAGE_H
	#define STBI_NO_LINEAR//#include <math.h>  // ldexp, pow
	#define STBI_NO_HDR //#include <math.h>  // ldexp, pow
	//#define STBI_ASSERT //#include <assert.h>
	//#define STBI_ASSERT(x) assert(x)

	//define STBI_ONLY_JPEG
	//define STBI_ONLY_PNG
	//define STBI_ONLY_BMP
	//define STBI_ONLY_PSD
	//define  STBI_ONLY_TGA
//        STBI_ONLY_GIF
//        STBI_ONLY_HDR
//        STBI_ONLY_PIC
//        STBI_ONLY_PNM   (.ppm and .pgm)


	#define STBI_NEON

	#ifdef __cplusplus
		extern "C" {
	#endif

	#ifdef __cplusplus
	}
	#endif

	#if defined(STBI_MALLOC) && defined(STBI_FREE) && (defined(STBI_REALLOC) || defined(STBI_REALLOC_SIZED))
	// ok
	#elif !defined(STBI_MALLOC) && !defined(STBI_FREE) && !defined(STBI_REALLOC) && !defined(STBI_REALLOC_SIZED)
	// ok
	#else
		#error "Must define all or none of STBI_MALLOC, STBI_FREE, and STBI_REALLOC (or STBI_REALLOC_SIZED)."
	#endif

	//#ifndef STBI_MALLOC

	//#endif

	#ifndef STBI_REALLOC_SIZED
		#define STBI_REALLOC_SIZED(p,oldsz,newsz) STBI_REALLOC(p,newsz)
	#endif

	#ifdef STB_IMAGE_STATIC
		#define STBIDEF static
	#else
		#define STBIDEF extern
	#endif

	// assume GCC or Clang on ARM targets
	#define STBI_SIMD_ALIGN(type, name) type name __attribute__((aligned(16)))

	#ifndef STBI_SIMD_ALIGN
	#define STBI_SIMD_ALIGN(type, name) type name
	#endif

	int wdith,height, bits;

    unsigned_char_pointer = image_load(filename, &x, &y, &n, 0);


//    // ... x = width, y = height, n = # 8-bit components per pixel ...
//    // ... replace '0' with '1'..'4' to force that many components per pixel
//    // ... but 'n' will always be the number that it would have been if you said 0

   image_free(data);



#ifndef STBI_INCLUDE_STB_IMAGE_H


// Limitations:
//    - no 12-bit-per-channel JPEG
//    - no JPEGs with arithmetic coding
//    - GIF always returns *comp=4

//
// Standard parameters:
//    int *x                 
//    int *y                 
//    int *channels_in_file  -- outputs # of image components in image file
//    int desired_channels   -- if non-zero, # of image components requested in result
//
// The return value from an image loader is an 'unsigned char *' which points
// to the pixel data, or NULL on an allocation failure or if the image is
// corrupt or invalid. The pixel data consists of *y scanlines of *x pixels,
// with each pixel consisting of N interleaved 8-bit components; the first
// pixel pointed to is top-left-most in the image. There is no padding between
// image scanlines or between pixels, regardless of format. The number of
// components N is 'desired_channels' if desired_channels is non-zero, or
// *channels_in_file otherwise. If desired_channels is non-zero,
// *channels_in_file has the number of components that _would_ have been
// output otherwise. E.g. if you set desired_channels to 4, you will always
// get RGBA output, but you can check *channels_in_file to see if it's trivially
// opaque because e.g. there were only 3 channels in the source image.
//
// An output image with N components has the following components interleaved
// in this order in each pixel:
//
//     N=#comp     components
//       1           grey
//       2           grey, alpha
//       3           red, green, blue
//       4           red, green, blue, alpha
//
// If image loading fails for any reason, the return value will be NULL,
// and *x, *y, *channels_in_file will be unchanged. The function
// stbi_failure_reason() can be queried for an extremely brief, end-user
// unfriendly explanation of why the load failed. Define STBI_NO_FAILURE_STRINGS
// to avoid compiling these strings at all, and STBI_FAILURE_USERMSG to get slightly
// more user-friendly ones.
//
// Paletted PNG, BMP, GIF, and PIC images are automatically depalettized.
//
// ===========================================================================
//
// I/O callbacks
//
// I/O callbacks allow you to read from arbitrary sources, like packaged
// files or some other source. Data read from callbacks are processed
// through a small internal buffer (currently 128 bytes) to try to reduce
// overhead.
//
// The three functions you must define are "read" (reads some bytes of data),
// "skip" (skips some bytes of data), "eof" (reports if the stream is at the end).
//
// ===========================================================================
//
// SIMD support
//
// The JPEG decoder will try to automatically use SIMD kernels on x86 when
// supported by the compiler. For ARM Neon support, you must explicitly
// request it.
//
// (The old do-it-yourself SIMD API is no longer supported in the current
// code.)
//
// On x86, SSE2 will automatically be used when available based on a run-time
// test; if not, the generic C versions are used as a fall-back. On ARM targets,
// the typical path is to have separate builds for NEON and non-NEON devices
// (at least this is true for iOS and Android). Therefore, the NEON support is
// toggled by a build flag: define STBI_NEON to get NEON loops.
//
// If for some reason you do not want to use any of SIMD code, or if
// you have issues compiling it, you can disable it entirely by
// defining STBI_NO_SIMD.
//
// ===========================================================================
//
// HDR image support   (disable by defining STBI_NO_HDR)
//
// stb_image now supports loading HDR images in general, and currently
// the Radiance .HDR file format, although the support is provided
// generically. You can still load any file through the existing interface;
// if you attempt to load an HDR file, it will be automatically remapped to
// LDR, assuming gamma 2.2 and an arbitrary scale factor defaulting to 1;
// both of these constants can be reconfigured through this interface:
//
//     stbi_hdr_to_ldr_gamma(2.2f);
//     stbi_hdr_to_ldr_scale(1.0f);
//
// (note, do not use _inverse_ constants; stbi_image will invert them
// appropriately).
//
// Additionally, there is a new, parallel interface for loading files as
// (linear) floats to preserve the full dynamic range:
//
//    float *data = stbi_loadf(filename, &x, &y, &n, 0);
//
// If you load LDR images through this interface, those images will
// be promoted to floating point values, run through the inverse of
// constants corresponding to the above:
//
//     stbi_ldr_to_hdr_scale(1.0f);
//     stbi_ldr_to_hdr_gamma(2.2f);
//
// Finally, given a filename (or an open file or memory block--see header
// file for details) containing image data, you can query for the "most
// appropriate" interface to use (that is, whether the image is HDR or
// not), using:
//
//     stbi_is_hdr(char *filename);
//
// ===========================================================================
//
// iPhone PNG support:
//
// By default we convert iphone-formatted PNGs back to RGB, even though
// they are internally encoded differently. You can disable this conversion
// by by calling stbi_convert_iphone_png_to_rgb(0), in which case
// you will always just get the native iphone "format" through (which
// is BGR stored in RGB).
//
// Call stbi_set_unpremultiply_on_load(1) as well to force a divide per
// pixel to remove any premultiplied alpha *only* if the image file explicitly
// says there's premultiplied data (currently only happens in iPhone images,
// and only if iPhone convert-to-rgb processing is on).
//
// ===========================================================================
//
//   - If you use STBI_NO_PNG (or _ONLY_ without PNG), and you still
//     want the zlib decoder to be available, #define STBI_SUPPORT_ZLIB
//





//
// load image by filename, open file, or memory buffer
/

////////////////////////////////////
//
// 8-bits-per-channel interface
//

IDEF i_uc *stbi_load_from_memory   (stbi_uc           const *buffer, int len   , int *x, int *y, int *channels_in_file, int desired_channels);

IDEF i_uc *stbi_load_from_callbacks(stbi_io_callbacks const *clbk  , void *user, int *x, int *y, int *channels_in_file, int desired_channels);



#ifndef STBI_NO_STDIO
STBIDEF stbi_uc *stbi_load            (char const *filename, int *x, int *y, int *channels_in_file, int desired_channels);
STBIDEF stbi_uc *stbi_load_from_file  (FILE *f, int *x, int *y, int *channels_in_file, int desired_channels);
// for stbi_load_from_file, file pointer is left pointing immediately after image
#endif

////////////////////////////////////
//
// 16-bits-per-channel interface
//

STBIDEF stbi_us *stbi_load_16_from_memory   (stbi_uc const *buffer, int len, int *x, int *y, int *channels_in_file, int desired_channels);
STBIDEF stbi_us *stbi_load_16_from_callbacks(stbi_io_callbacks const *clbk, void *user, int *x, int *y, int *channels_in_file, int desired_channels);

////////////////////////////////////
//
// float-per-channel interface
//

#ifndef STBI_NO_LINEAR
   STBIDEF float *loadf_from_memory     (stbi_uc const *buffer, int len, int *x, int *y, int *channels_in_file, int desired_channels);
   STBIDEF float *loadf_from_callbacks  (stbi_io_callbacks const *clbk, void *user, int *x, int *y,  int *channels_in_file, int desired_channels);

#endif

#ifndef STBI_NO_HDR
   STBIDEF void   i_hdr_to_ldr_gamma(float gamma);
   STBIDEF void   i_hdr_to_ldr_scale(float scale);
#endif // STBI_NO_HDR

#ifndef STBI_NO_LINEAR
   STBIDEF void   stbi_ldr_to_hdr_gamma(float gamma);
   STBIDEF void   stbi_ldr_to_hdr_scale(float scale);
#endif // STBI_NO_LINEAR

// stbi_is_hdr is always defined, but always returns false if STBI_NO_HDR
STBIDEF int    stbi_is_hdr_from_callbacks(stbi_io_callbacks const *clbk, void *user);
STBIDEF int    stbi_is_hdr_from_memory(stbi_uc const *buffer, int len);
#ifndef STBI_NO_STDIO
STBIDEF int      stbi_is_hdr          (char const *filename);
STBIDEF int      stbi_is_hdr_from_file(FILE *f);
#endif // STBI_NO_STDIO


// get a VERY brief reason for failure
// NOT THREADSAFE
STBIDEF const char *i_failure_reason  (void);

// free the loaded image -- this is just free()
STBIDEF void     image_free      (void *retval_from_stbi_load);

// get image dimensions & components without fully decoding
DEF int info_from_memory(stbi_uc const *buffer, int len, int *x, int *y, int *comp);
DEF int info_from_callbacks(stbi_io_callbacks const *clbk, void *user, int *x, int *y, int *comp);
DEF int is_16_bit_from_memory(stbi_uc const *buffer, int len);
DEF int is_16_bit_from_callbacks(stbi_io_callbacks const *clbk, void *user);


// for image formats that explicitly notate that they have premultiplied alpha,
// we just return the colors as stored in the file. set this flag to force
// unpremultiplication. results are undefined if the unpremultiply overflow.

STBIDEF void set_unpremultiply_on_load(int flag_true_if_should_unpremultiply);

// indicate whether we should process iphone images back to canonical format,
// or just pass them through "as-is"

STBIDEF void convert_iphone_png_to_rgb(int flag_true_if_should_convert);

// flip the image vertically, so the first pixel in the output array is the bottom left
STBIDEF void set_flip_vertically_on_load(int flag_true_if_should_flip);

// ZLIB client - used by PNG, available for other purposes

STBIDEF char *zlib_decode_malloc_guesssize(const char *buffer, int len, int initial_size, int *outlen);
STBIDEF char *zlib_decode_malloc_guesssize_headerflag(const char *buffer, int len, int initial_size, int *outlen, int parse_header);
STBIDEF char *zlib_decode_malloc(const char *buffer, int len, int *outlen);
STBIDEF int   zlib_decode_buffer(char *obuffer, int olen, const char *ibuffer, int ilen);

STBIDEF char *zlib_decode_noheader_malloc(const char *buffer, int len, int *outlen);
STBIDEF int   zlib_decode_noheader_buffer(char *obuffer, int olen, const char *ibuffer, int ilen);


#ifndef _MSC_VER
   #ifdef __cplusplus
	#define inline inline
   #else
	#define inline
   #endif
#else
   #define inline __forceinline
#endif


#ifdef _MSC_VER

typedef unsigned short uint16;
typedef   signed short int16;
typedef unsigned int   uint32;
typedef   signed int   int32;

#else
	//#include <stdint.h> 
typedef uint16_t uint16;
typedef int16_t  int16;
typedef uint32_t uint32;
typedef int32_t  int32;
#endif

// should produce compiler error if size is wrong

typedef unsigned char validate_uint32[sizeof(uint32) == 4 ? 1 : -1];

#ifdef _MSC_VER
#define STBI_NOTUSED(v)  (void)(v)
#else
#define STBI_NOTUSED(v)  (void)sizeof(v)
#endif

#ifdef _MSC_VER
#define STBI_HAS_LROTL
#endif

#ifdef STBI_HAS_LROTL
   #define stbi_lrot(x,y)  _lrotl(x,y)
#else
   #define stbi_lrot(x,y)  (((x) << (y)) | ((x) >> (32 - (y))))
#endif



// x86/x64 detection
#if defined(__x86_64__) || defined(_M_X64)
#define X64_TARGET
#elif defined(__i386) || defined(_M_IX86)
#define X86_TARGET
#endif

#if defined(__GNUC__) && defined(STBI__X86_TARGET) && !defined(__SSE2__) && !defined(STBI_NO_SIMD)
// gcc doesn't support sse2 intrinsics unless you compile with -msse2,
// which in turn means it gets to use SSE2 everywhere. This is unfortunate,
// but previous attempts to provide the SSE2 functions with runtime
// detection caused numerous issues. The way architecture extensions are
// exposed in GCC/Clang is, sadly, not really suited for one-file libs.
// New behavior: if compiled with -msse2, we use SSE2 without any
// detection; if not, we don't use it at all.
#define STBI_NO_SIMD
#endif

#if defined(__MINGW32__) && defined(STBI__X86_TARGET) && !defined(STBI_MINGW_ENABLE_SSE2) && !defined(STBI_NO_SIMD)
// Note that __MINGW32__ doesn't actually mean 32-bit, so we have to avoid STBI__X64_TARGET
//
// 32-bit MinGW wants ESP to be 16-byte aligned, but this is not in the
// Windows ABI and VC++ as well as Windows DLLs don't maintain that invariant.
// As a result, enabling SSE2 on 32-bit MinGW is dangerous when not
// simultaneously enabling "-mstackrealign".
//
//
// So default to no SSE2 on 32-bit MinGW. If you've read this far and added
// -mstackrealign to your build settings, feel free to #define STBI_MINGW_ENABLE_SSE2.
#define STBI_NO_SIMD
#endif

#if !defined(STBI_NO_SIMD) && (defined(STBI__X86_TARGET) || defined(STBI__X64_TARGET))
#define STBI_SSE2
//#include <emmintrin.h>

#ifdef _MSC_VER

#if _MSC_VER >= 1400  // not VC6
//#include <intrin.h> // __cpuid

static int cpu_id3(void)
{
   int info[4];
   __cpuid(info,1);
   return info[3];
}

#else

static int cpu_id3(void)
{
   int res;
   __asm {
      mov  eax,1
      cpuid
      mov res, edx
   }
   return res;
}

#endif

#define STBI_SIMD_ALIGN(type, name) __declspec(align(16)) type name

static int stbi__sse2_available(void)
{
   int info3 = stbi__cpuid3();
   return ((info3 >> 26) & 1) != 0;
}
#else // assume GCC-style if not VC++

#define STBI_SIMD_ALIGN(type, name) type name __attribute__((aligned(16)))

static int sse2_available(void)
{
   // If we're even attempting to compile this on GCC/Clang, that means
   // -msse2 is on, which means the compiler is allowed to use SSE2
   // instructions at will, and so are we.
   return 1;
}

#endif

///////////////////////////////////////////////


static void refill_buffer(stbi__context *s);

// initialize a memory-decode context
static void start_mem(stbi__context *s, stbi_uc const *buffer, int len)
{
   s->io.read = NULL;
   s->read_from_callbacks = 0;
   s->img_buffer = s->img_buffer_original = (stbi_uc *) buffer;
   s->img_buffer_end = s->img_buffer_original_end = (stbi_uc *) buffer+len;
}

// initialize a callback-based context

static void start_callbacks(stbi__context *s, stbi_io_callbacks *c, void *user)
{
   s->io = *c;
   s->io_user_data = user;
   s->buflen = sizeof(s->buffer_start);
   s->read_from_callbacks = 1;
   s->img_buffer_original = s->buffer_start;
   refill_buffer(s);
   s->img_buffer_original_end = s->img_buffer_end;
}



static void rewind(stbi__context *s)
{
   // conceptually rewind SHOULD rewind to the beginning of the stream,
   // but we just rewind to the beginning of the initial buffer, because
   // we only use it after doing 'test', which only ever looks at at most 92 bytes
   
   s->img_buffer = s->img_buffer_original;
   s->img_buffer_end = s->img_buffer_original_end;
}


// stbi__err - error
// stbi__errpf - error returning pointer to float
// stbi__errpuc - error returning pointer to unsigned char

#ifdef STBI_NO_FAILURE_STRINGS
   #define stbi__err(x,y)  0
#elif defined(STBI_FAILURE_USERMSG)
   #define stbi__err(x,y)  stbi__err(y)
#else
   #define stbi__err(x,y)  stbi__err(x)
#endif

#define stbi__errpf(x,y)   ((float *)(size_t) (stbi__err(x,y)?NULL:NULL))
#define stbi__errpuc(x,y)  ((unsigned char *)(size_t) (stbi__err(x,y)?NULL:NULL))

STBIDEF void image_free(void *retval_from_stbi_load)
{
   STBI_FREE(retval_from_stbi_load);
}

#ifndef STBI_NO_LINEAR
static float   *ldr_to_hdr(stbi_uc *data, int x, int y, int comp);
#endif





STBIDEF void stbi_set_flip_vertically_on_load(int flag_true_if_should_flip)
{
    stbi__vertically_flip_on_load = flag_true_if_should_flip;
}

static void *load_main(stbi__context *s, int *x, int *y, int *comp, int req_comp, stbi__result_info *ri, int bpc)
{
   memset(ri, 0, sizeof(*ri)); // make sure it's initialized if we add new fields
   ri->bits_per_channel = 8; // default is 8 so most paths don't have to be changed
   ri->channel_order = STBI_ORDER_RGB; // all current input & output are this, but this is here so we can add BGR order
   ri->num_channels = 0;

   #ifndef NO_JPEG
   if (stbi__jpeg_test(s)) return stbi__jpeg_load(s,x,y,comp,req_comp, ri);
   #endif
   #ifndef NO_PNG
   if (stbi__png_test(s))  return stbi__png_load(s,x,y,comp,req_comp, ri);
   #endif
   #ifndef NO_BMP
   if (stbi__bmp_test(s))  return stbi__bmp_load(s,x,y,comp,req_comp, ri);
   #endif
   #ifndef NO_GIF
   if (stbi__gif_test(s))  return stbi__gif_load(s,x,y,comp,req_comp, ri);
   #endif
   #ifndef NO_PSD
   if (stbi__psd_test(s))  return stbi__psd_load(s,x,y,comp,req_comp, ri, bpc);
   #endif
   #ifndef NO_PIC
   if (stbi__pic_test(s))  return stbi__pic_load(s,x,y,comp,req_comp, ri);
   #endif
   #ifndef NO_PNM
   if (stbi__pnm_test(s))  return stbi__pnm_load(s,x,y,comp,req_comp, ri);
   #endif

   #ifndef NO_HDR
   if (stbi__hdr_test(s)) {
      float *hdr = stbi__hdr_load(s, x,y,comp,req_comp, ri);
      return stbi__hdr_to_ldr(hdr, *x, *y, req_comp ? req_comp : *comp);
   }
   #endif

   #ifndef NO_TGA
   // test tga last because it's a crappy test!
   if (stbi__tga_test(s))
      return stbi__tga_load(s,x,y,comp,req_comp, ri);
   #endif

   return stbi__errpuc("unknown image type", "Image not of any known type, or corrupt");
}

static stbi_uc *stbi__convert_16_to_8(stbi__uint16 *orig, int w, int h, int channels)
{
   int i;
   int img_len = w * h * channels;
   stbi_uc *reduced;

   reduced = (stbi_uc *) stbi__malloc(img_len);
   
   if (reduced == NULL) {
		return stbi__errpuc("outofmem", "Out of memory");
   }
	   
   for (i = 0; i < img_len; ++i){
	  reduced[i] = (stbi_uc)((orig[i] >> 8) & 0xFF); // top half of each byte is sufficient approx of 16->8 bit scaling 
   }
     
   STBI_FREE(orig);
   return reduced;
}

static stbi__uint16 *stbi__convert_8_to_16(stbi_uc *orig, int w, int h, int channels)
{
   int i;
   int img_len = w * h * channels;
   stbi__uint16 *enlarged;

   enlarged = (stbi__uint16 *) stbi__malloc(img_len*2);
   if (enlarged == NULL) return (stbi__uint16 *) stbi__errpuc("outofmem", "Out of memory");

   for (i = 0; i < img_len; ++i)
      enlarged[i] = (stbi__uint16)((orig[i] << 8) + orig[i]); // replicate to high and low byte, maps 0->0, 255->0xffff

   STBI_FREE(orig);
   return enlarged;
}

static void vertical_flip(void *image, int w, int h, int bytes_per_pixel)
{
   
   size_t bytes_per_row = (size_t)w * bytes_per_pixel;
   stbi_uc temp[2048];
   stbi_uc *bytes = (stbi_uc *)image;

   for (row = 0; row < (h>>1); row++) {
      stbi_uc *row0 = bytes + row*bytes_per_row;
      stbi_uc *row1 = bytes + (h - row - 1)*bytes_per_row;
      // swap row0 with row1
      size_t bytes_left = bytes_per_row;
      while (bytes_left) {
         size_t bytes_copy = (bytes_left < sizeof(temp)) ? bytes_left : sizeof(temp);
         memcpy(temp, row0, bytes_copy);
         memcpy(row0, row1, bytes_copy);
         memcpy(row1, temp, bytes_copy);
         row0 += bytes_copy;
         row1 += bytes_copy;
         bytes_left -= bytes_copy;
      }
   }
}

static void stbi__vertical_flip_slices(void *image, int w, int h, int z, int bytes_per_pixel)
{
   int slice;
   int slice_size = w * h * bytes_per_pixel;

   stbi_uc *bytes = (stbi_uc *)image;
   for (slice = 0; slice < z; ++slice) {
      stbi__vertical_flip(bytes, w, h, bytes_per_pixel); 
      bytes += slice_size; 
   }
}

static unsigned char *stbi__load_and_postprocess_8bit(stbi__context *s, int *x, int *y, int *comp, int req_comp)
{
   stbi__result_info ri;
   void *result = stbi__load_main(s, x, y, comp, req_comp, &ri, 8);

   if (result == NULL)
      return NULL;

   if (ri.bits_per_channel != 8) {
      STBI_ASSERT(ri.bits_per_channel == 16);
      result = stbi__convert_16_to_8((stbi__uint16 *) result, *x, *y, req_comp == 0 ? *comp : req_comp);
      ri.bits_per_channel = 8;
   }

   // @TODO: move stbi__convert_format to here

   if (stbi__vertically_flip_on_load) {
      int channels = req_comp ? req_comp : *comp;
      stbi__vertical_flip(result, *x, *y, channels * sizeof(stbi_uc));
   }

   return (unsigned char *) result;
}

static stbi__uint16 *stbi__load_and_postprocess_16bit(stbi__context *s, int *x, int *y, int *comp, int req_comp)
{
   stbi__result_info ri;
   void *result = stbi__load_main(s, x, y, comp, req_comp, &ri, 16);

   if (result == NULL)
      return NULL;

   if (ri.bits_per_channel != 16) {
      STBI_ASSERT(ri.bits_per_channel == 8);
      result = stbi__convert_8_to_16((stbi_uc *) result, *x, *y, req_comp == 0 ? *comp : req_comp);
      ri.bits_per_channel = 16;
   }

   // @TODO: move stbi__convert_format16 to here
   // @TODO: special case RGB-to-Y (and RGBA-to-YA) for 8-bit-to-16-bit case to keep more precision

   if (stbi__vertically_flip_on_load) {
      int channels = req_comp ? req_comp : *comp;
      stbi__vertical_flip(result, *x, *y, channels * sizeof(stbi__uint16));
   }

   return (stbi__uint16 *) result;
}

#if !defined(STBI_NO_HDR) || !defined(STBI_NO_LINEAR)
static void stbi__float_postprocess(float *result, int *x, int *y, int *comp, int req_comp)
{
   if (stbi__vertically_flip_on_load && result != NULL) {
      int channels = req_comp ? req_comp : *comp;
      stbi__vertical_flip(result, *x, *y, channels * sizeof(float));
   }
}
#endif



STBIDEF stbi_us *stbi_load_16_from_memory(stbi_uc const *buffer, int len, int *x, int *y, int *channels_in_file, int desired_channels)
{
   stbi__context s;
   stbi__start_mem(&s,buffer,len);
   return stbi__load_and_postprocess_16bit(&s,x,y,channels_in_file,desired_channels);
}

STBIDEF stbi_us *stbi_load_16_from_callbacks(stbi_io_callbacks const *clbk, void *user, int *x, int *y, int *channels_in_file, int desired_channels)
{
   stbi__context s;
   stbi__start_callbacks(&s, (stbi_io_callbacks *)clbk, user);
   return stbi__load_and_postprocess_16bit(&s,x,y,channels_in_file,desired_channels);
}

STBIDEF stbi_uc *stbi_load_from_memory(stbi_uc const *buffer, int len, int *x, int *y, int *comp, int req_comp)
{
   stbi__context s;
   stbi__start_mem(&s,buffer,len);
   return stbi__load_and_postprocess_8bit(&s,x,y,comp,req_comp);
}

STBIDEF stbi_uc *stbi_load_from_callbacks(stbi_io_callbacks const *clbk, void *user, int *x, int *y, int *comp, int req_comp)
{
   stbi__context s;
   stbi__start_callbacks(&s, (stbi_io_callbacks *) clbk, user);
   return stbi__load_and_postprocess_8bit(&s,x,y,comp,req_comp);
}


#ifndef STBI_NO_LINEAR
static float *stbi__loadf_main(stbi__context *s, int *x, int *y, int *comp, int req_comp)
{
	
   unsigned char *data;
  
  #ifndef STBI_NO_HDR
   if (stbi__hdr_test(s)) {
      stbi__result_info ri;
      float *hdr_data = stbi__hdr_load(s,x,y,comp,req_comp, &ri);
      if (hdr_data)
         stbi__float_postprocess(hdr_data,x,y,comp,req_comp);
      return hdr_data;
   }
   
   #endif
   
   data = stbi__load_and_postprocess_8bit(s, x, y, comp, req_comp);
   
   if (data)
      return stbi__ldr_to_hdr(data, *x, *y, req_comp ? req_comp : *comp);
   return stbi__errpf("unknown image type", "Image not of any known type, or corrupt");
}

STBIDEF float *stbi_loadf_from_memory(stbi_uc const *buffer, int len, int *x, int *y, int *comp, int req_comp)
{
   stbi__context s;
   stbi__start_mem(&s,buffer,len);
   return stbi__loadf_main(&s,x,y,comp,req_comp);
}

STBIDEF float *stbi_loadf_from_callbacks(stbi_io_callbacks const *clbk, void *user, int *x, int *y, int *comp, int req_comp)
{
   stbi__context s;
   stbi__start_callbacks(&s, (stbi_io_callbacks *) clbk, user);
   return stbi__loadf_main(&s,x,y,comp,req_comp);
}



#endif // !STBI_NO_LINEAR

// these is-hdr-or-not is defined independent of whether STBI_NO_LINEAR is
// defined, for API simplicity; if STBI_NO_LINEAR is defined, it always
// reports false!

STBIDEF int stbi_is_hdr_from_memory(stbi_uc const *buffer, int len)
{
   #ifndef STBI_NO_HDR
   stbi__context s;
   stbi__start_mem(&s,buffer,len);
   return stbi__hdr_test(&s);
   #else
   STBI_NOTUSED(buffer);
   STBI_NOTUSED(len);
   return 0;
   #endif
}

#ifndef STBI_NO_STDIO

STBIDEF int      stbi_is_hdr          (char const *filename)
{
   FILE *f = stbi__fopen(filename, "rb");
   int result = 0;
   if (f) {
      result = stbi_is_hdr_from_file(f);
      fclose(f);
   }
   return result;
}

STBIDEF int stbi_is_hdr_from_file(FILE *f)
{
   #ifndef STBI_NO_HDR
   long pos = ftell(f);
   int res;
   stbi__context s;
   stbi__start_file(&s,f);
   res = stbi__hdr_test(&s);
   fseek(f, pos, SEEK_SET);
   return res;
   #else
   STBI_NOTUSED(f);
   return 0;
   #endif
}
#endif // !STBI_NO_STDIO

STBIDEF int      stbi_is_hdr_from_callbacks(stbi_io_callbacks const *clbk, void *user)
{
   #ifndef STBI_NO_HDR
   stbi__context s;
   stbi__start_callbacks(&s, (stbi_io_callbacks *) clbk, user);
   return stbi__hdr_test(&s);
   #else
   STBI_NOTUSED(clbk);
   STBI_NOTUSED(user);
   return 0;
   #endif
}

#ifndef STBI_NO_LINEAR
static float stbi__l2h_gamma=2.2f, stbi__l2h_scale=1.0f;

STBIDEF void   stbi_ldr_to_hdr_gamma(float gamma) { stbi__l2h_gamma = gamma; }
STBIDEF void   stbi_ldr_to_hdr_scale(float scale) { stbi__l2h_scale = scale; }
#endif

static float stbi__h2l_gamma_i=1.0f/2.2f, stbi__h2l_scale_i=1.0f;

STBIDEF void   stbi_hdr_to_ldr_gamma(float gamma) { stbi__h2l_gamma_i = 1/gamma; }
STBIDEF void   stbi_hdr_to_ldr_scale(float scale) { stbi__h2l_scale_i = 1/scale; }




//////////////////////////////////////////////////////////////////////////////
//
//  generic converter from built-in img_n to req_comp
//    individual types do this automatically as much as possible (e.g. jpeg
//    does all cases internally since it needs to colorspace convert anyway,
//    and it never has alpha, so very few cases ). png can automatically
//    interleave an alpha=255 channel, but falls back to this for other cases
//
//  assume data buffer is malloced, so malloc a new one and free that one
//  only failure mode is malloc failing

static stbi_uc stbi__compute_y(int r, int g, int b)
{
   return (stbi_uc) (((r*77) + (g*150) +  (29*b)) >> 8);
}

static unsigned char *stbi__convert_format(unsigned char *data, int img_n, int req_comp, unsigned int x, unsigned int y)
{
   int i,j;
   unsigned char *good;

   if (req_comp == img_n) return data;
   STBI_ASSERT(req_comp >= 1 && req_comp <= 4);

   good = (unsigned char *) stbi__malloc_mad3(req_comp, x, y, 0);
   if (good == NULL) {
      STBI_FREE(data);
      return stbi__errpuc("outofmem", "Out of memory");
   }

   for (j=0; j < (int) y; ++j) {
      unsigned char *src  = data + j * x * img_n   ;
      unsigned char *dest = good + j * x * req_comp;

      #define STBI__COMBO(a,b)  ((a)*8+(b))
      #define STBI__CASE(a,b)   case STBI__COMBO(a,b): for(i=x-1; i >= 0; --i, src += a, dest += b)
      // convert source image with img_n components to one with req_comp components;
      // avoid switch per pixel, so use switch per scanline and massive macros
      switch (STBI__COMBO(img_n, req_comp)) {
         STBI__CASE(1,2) { dest[0]=src[0], dest[1]=255;                                     } break;
         STBI__CASE(1,3) { dest[0]=dest[1]=dest[2]=src[0];                                  } break;
         STBI__CASE(1,4) { dest[0]=dest[1]=dest[2]=src[0], dest[3]=255;                     } break;
         STBI__CASE(2,1) { dest[0]=src[0];                                                  } break;
         STBI__CASE(2,3) { dest[0]=dest[1]=dest[2]=src[0];                                  } break;
         STBI__CASE(2,4) { dest[0]=dest[1]=dest[2]=src[0], dest[3]=src[1];                  } break;
         STBI__CASE(3,4) { dest[0]=src[0],dest[1]=src[1],dest[2]=src[2],dest[3]=255;        } break;
         STBI__CASE(3,1) { dest[0]=stbi__compute_y(src[0],src[1],src[2]);                   } break;
         STBI__CASE(3,2) { dest[0]=stbi__compute_y(src[0],src[1],src[2]), dest[1] = 255;    } break;
         STBI__CASE(4,1) { dest[0]=stbi__compute_y(src[0],src[1],src[2]);                   } break;
         STBI__CASE(4,2) { dest[0]=stbi__compute_y(src[0],src[1],src[2]), dest[1] = src[3]; } break;
         STBI__CASE(4,3) { dest[0]=src[0],dest[1]=src[1],dest[2]=src[2];                    } break;
         default: STBI_ASSERT(0);
      }
      #undef STBI__CASE
   }

   STBI_FREE(data);
   return good;
}

static stbi__uint16 stbi__compute_y_16(int r, int g, int b)
{
   return (stbi__uint16) (((r*77) + (g*150) +  (29*b)) >> 8);
}

static stbi__uint16 *stbi__convert_format16(stbi__uint16 *data, int img_n, int req_comp, unsigned int x, unsigned int y)
{
   int i,j;
   stbi__uint16 *good;

   if (req_comp == img_n) return data;
   STBI_ASSERT(req_comp >= 1 && req_comp <= 4);

   good = (stbi__uint16 *) stbi__malloc(req_comp * x * y * 2);
   if (good == NULL) {
      STBI_FREE(data);
      return (stbi__uint16 *) stbi__errpuc("outofmem", "Out of memory");
   }

   for (j=0; j < (int) y; ++j) {
      stbi__uint16 *src  = data + j * x * img_n   ;
      stbi__uint16 *dest = good + j * x * req_comp;

      #define STBI__COMBO(a,b)  ((a)*8+(b))
      #define STBI__CASE(a,b)   case STBI__COMBO(a,b): for(i=x-1; i >= 0; --i, src += a, dest += b)
      // convert source image with img_n components to one with req_comp components;
      // avoid switch per pixel, so use switch per scanline and massive macros
      switch (STBI__COMBO(img_n, req_comp)) {
         STBI__CASE(1,2) { dest[0]=src[0], dest[1]=0xffff;                                     } break;
         STBI__CASE(1,3) { dest[0]=dest[1]=dest[2]=src[0];                                     } break;
         STBI__CASE(1,4) { dest[0]=dest[1]=dest[2]=src[0], dest[3]=0xffff;                     } break;
         STBI__CASE(2,1) { dest[0]=src[0];                                                     } break;
         STBI__CASE(2,3) { dest[0]=dest[1]=dest[2]=src[0];                                     } break;
         STBI__CASE(2,4) { dest[0]=dest[1]=dest[2]=src[0], dest[3]=src[1];                     } break;
         STBI__CASE(3,4) { dest[0]=src[0],dest[1]=src[1],dest[2]=src[2],dest[3]=0xffff;        } break;
         STBI__CASE(3,1) { dest[0]=stbi__compute_y_16(src[0],src[1],src[2]);                   } break;
         STBI__CASE(3,2) { dest[0]=stbi__compute_y_16(src[0],src[1],src[2]), dest[1] = 0xffff; } break;
         STBI__CASE(4,1) { dest[0]=stbi__compute_y_16(src[0],src[1],src[2]);                   } break;
         STBI__CASE(4,2) { dest[0]=stbi__compute_y_16(src[0],src[1],src[2]), dest[1] = src[3]; } break;
         STBI__CASE(4,3) { dest[0]=src[0],dest[1]=src[1],dest[2]=src[2];                       } break;
         default: STBI_ASSERT(0);
      }
      #undef STBI__CASE
   }

   STBI_FREE(data);
   return good;
}

#ifndef STBI_NO_LINEAR
static float   *stbi__ldr_to_hdr(stbi_uc *data, int x, int y, int comp)
{
   int i,k,n;
   float *output;
   if (!data) return NULL;
   output = (float *) stbi__malloc_mad4(x, y, comp, sizeof(float), 0);
   if (output == NULL) { STBI_FREE(data); return stbi__errpf("outofmem", "Out of memory"); }
   // compute number of non-alpha components
   if (comp & 1) n = comp; else n = comp-1;
   for (i=0; i < x*y; ++i) {
      for (k=0; k < n; ++k) {
         output[i*comp + k] = (float) (pow(data[i*comp+k]/255.0f, stbi__l2h_gamma) * stbi__l2h_scale);
      }
      if (k < comp) output[i*comp + k] = data[i*comp+k]/255.0f;
   }
   STBI_FREE(data);
   return output;
}
#endif


static int info_main(stbi__context *s, int *x, int *y, int *comp)
{
	
   #ifndef STBI_NO_JPEG
	if (stbi__jpeg_info(s, x, y, comp)) return 1;
   #endif

   #ifndef STBI_NO_PNG
   if (stbi__png_info(s, x, y, comp))  return 1;
   #endif

   #ifndef STBI_NO_GIF
   if (stbi__gif_info(s, x, y, comp))  return 1;
   #endif

   #ifndef STBI_NO_BMP
   if (stbi__bmp_info(s, x, y, comp))  return 1;
   #endif

   #ifndef STBI_NO_PSD
   if (stbi__psd_info(s, x, y, comp))  return 1;
   #endif

   #ifndef STBI_NO_PIC
   if (stbi__pic_info(s, x, y, comp))  return 1;
   #endif

   #ifndef STBI_NO_PNM
   if (stbi__pnm_info(s, x, y, comp))  return 1;
   #endif

   #ifndef STBI_NO_HDR
   if (stbi__hdr_info(s, x, y, comp))  return 1;
   #endif

   // test tga last because it's a crappy test!
   #ifndef STBI_NO_TGA
   if (stbi__tga_info(s, x, y, comp))
       return 1;
   #endif
   
   return error("unknown image type", "Image not of any known type, or corrupt");
}

static int stbi__is_16_main(stbi__context *s)
{
   #ifndef STBI_NO_PNG
   if (stbi__png_is16(s))  return 1;
   #endif

   #ifndef STBI_NO_PSD
   if (stbi__psd_is16(s))  return 1;
   #endif

   return 0;
}

#ifndef STBI_NO_STDIO
STBIDEF int stbi_info(char const *filename, int *x, int *y, int *comp)
{
    FILE *f = stbi__fopen(filename, "rb");
    int result;
    if (!f) return stbi__err("can't fopen", "Unable to open file");
    result = stbi_info_from_file(f, x, y, comp);
    fclose(f);
    return result;
}

STBIDEF int stbi_info_from_file(FILE *f, int *x, int *y, int *comp)
{
   int r;
   stbi__context s;
   long pos = ftell(f);
   stbi__start_file(&s, f);
   r = stbi__info_main(&s,x,y,comp);
   fseek(f,pos,SEEK_SET);
   return r;
}

STBIDEF int stbi_is_16_bit(char const *filename)
{
    FILE *f = stbi__fopen(filename, "rb");
    int result;
    if (!f) return stbi__err("can't fopen", "Unable to open file");
    result = stbi_is_16_bit_from_file(f);
    fclose(f);
    return result;
}

STBIDEF int stbi_is_16_bit_from_file(FILE *f)
{
   int r;
   stbi__context s;
   long pos = ftell(f);
   stbi__start_file(&s, f);
   r = stbi__is_16_main(&s);
   fseek(f,pos,SEEK_SET);
   return r;
}
#endif // !STBI_NO_STDIO

STBIDEF int stbi_info_from_memory(stbi_uc const *buffer, int len, int *x, int *y, int *comp)
{
   stbi__context s;
   stbi__start_mem(&s,buffer,len);
   return stbi__info_main(&s,x,y,comp);
}

STBIDEF int stbi_info_from_callbacks(stbi_io_callbacks const *c, void *user, int *x, int *y, int *comp)
{
   stbi__context s;
   stbi__start_callbacks(&s, (stbi_io_callbacks *) c, user);
   return stbi__info_main(&s,x,y,comp);
}

STBIDEF int stbi_is_16_bit_from_memory(stbi_uc const *buffer, int len)
{
   stbi__context s;
   stbi__start_mem(&s,buffer,len);
   return stbi__is_16_main(&s);
}

STBIDEF int stbi_is_16_bit_from_callbacks(stbi_io_callbacks const *c, void *user)
{
   stbi__context s;
   stbi__start_callbacks(&s, (stbi_io_callbacks *) c, user);
   return stbi__is_16_main(&s);
}

#endif // STB_IMAGE_IMPLEMENTATION





