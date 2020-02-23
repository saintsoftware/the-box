
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "variables.h"
#include "path.h"
#include "file.h"
#include "image.h"
#include "image_gif.h"

void print_gif_extension(FILE *file, GifExtension *ext)
{
	int i;

	fprintf(file, " GifExtension:\n");
	fprintf(file, "  marker = 0x%02X\n", ext->marker);
	for (i=0; i < ext->data_count; i++) {
		fprintf(file, "  data = ");
		print_gif_data(file, ext->data[i]);
	}
}

void print_gif_screen(FILE *file, GifScreen *screen)
{
	fprintf(file, " GifScreen:\n");
	fprintf(file, "  width      = %d\n", screen->width);
	fprintf(file, "  height     = %d\n", screen->height);

	fprintf(file, "  has_cmap   = %d\n", screen->has_cmap ? 1:0);
	fprintf(file, "  color_res  = %d\n", screen->color_res);
	fprintf(file, "  sorted     = %d\n", screen->sorted ? 1:0);
	fprintf(file, "  cmap_depth = %d\n", screen->cmap_depth);

	fprintf(file, "  bgcolour   = %02X\n", screen->bgcolour);
	fprintf(file, "  aspect     = %d\n", screen->aspect);

	if (screen->has_cmap) {
		print_gif_palette(file, screen->cmap);
	}
}

void print_gif_palette(FILE *file, GifPalette *cmap)
{
	int i;

	fprintf(file, "  GifPalette (length=%d):\n", cmap->length);
	for (i=0; i<cmap->length; i++) {
		fprintf(file, "   %02X = 0x", i);
		fprintf(file, "%02X", cmap->colours[i].red);
		fprintf(file, "%02X", cmap->colours[i].green);
		fprintf(file, "%02X\n", cmap->colours[i].blue);
	}
}

void print_gif_data(FILE *file, GifData *data)
{
	int i, ch, prev;
	int ch_printable, prev_printable;

	if (data) {
		fprintf(file, "(length=%d) [", data->byte_count);
		prev_printable = 1;
		for (i=0; i < data->byte_count; i++) {
			ch = data->bytes[i];
			ch_printable = isprint(ch) ? 1 : 0;

			if (ch_printable != prev_printable)
				fprintf(file, " ");

			if (ch_printable)
				fprintf(file, "%c", (char)ch);
			else
				fprintf(file, "%02X,", ch);

			prev = ch;
			prev_printable = isprint(prev) ? 1 : 0;
		}
		fprintf(file, "]\n");
	}
	else {
		fprintf(file, "[]\n");
	}
}

static void print_gif_picture_data(FILE *file, GifPicture *pic)
{
	int pixval, row, col;

	for (row = 0; row < pic->height; row++) {
	  fprintf(file, "   [");
	  for (col = 0; col < pic->width; col++) {
	    pixval = pic->data[row][col];
	    fprintf(file, "%02X", pixval);
	  }
	  fprintf(file, "]\n");
	}
}

static void print_gif_picture_header(FILE *file, GifPicture *pic)
{
	fprintf(file, " GifPicture:\n");
	fprintf(file, "  left       = %d\n", pic->left);
	fprintf(file, "  top        = %d\n", pic->top);
	fprintf(file, "  width      = %d\n", pic->width);
	fprintf(file, "  height     = %d\n", pic->height);

	fprintf(file, "  has_cmap   = %d\n", pic->has_cmap);
	fprintf(file, "  interlace  = %d\n", pic->interlace);
	fprintf(file, "  sorted     = %d\n", pic->sorted);
	fprintf(file, "  reserved   = %d\n", pic->reserved);
	fprintf(file, "  cmap_depth = %d\n", pic->cmap_depth);
}

void print_gif_picture(FILE *file, GifPicture *pic)
{
	print_gif_picture_header(file, pic);

	if (pic->has_cmap)
		print_gif_palette(file, pic->cmap);

	print_gif_picture_data(file, pic);
}

void print_gif_block(FILE *file, GifBlock *block)
{
	fprintf(file, " GifBlock (intro=0x%02X):\n", block->intro);
	if (block->pic)
		print_gif_picture(file, block->pic);
	if (block->ext)
		print_gif_extension(file, block->ext);
}

void print_gif(FILE *file, Gif *gif)
{
	int i;

	fprintf(file, "Gif header=%s\n", gif->header);
	print_gif_screen(file, gif->screen);
	for (i=0; i < gif->block_count; i++)
		print_gif_block(file, gif->blocks[i]);
	fprintf(file, "End of gif.\n\n");
}


int main(int argc, char *argv[])
{
	
}