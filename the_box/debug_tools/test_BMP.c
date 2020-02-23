//https://www.daniweb.com/programming/software-development/threads/146692/how-to-display-a-image-in-c
//https://cboard.cprogramming.com/c-programming/50007-reading-bitmap-image.html
// https://codereview.stackexchange.com/questions/8213/bitmap-implementation

#include <alloc.h>
#include <conio.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>

#include "../application_structues/bitmap.h";
#include "../application_structues/path.h";

char images[5]; 
int loop;

void main()
{
	
int color;
int gd ;
int gm ;

gd = VGA ; 
gm = VGAHI;

/*
Type[2];          
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
*/

printf("%s \n File name");
printf("%s \n size", Size);
printf("%s \n reserved", Reserved);
printf("%s \n Offset", OffSet);
printf("%s \n Offset", headsize);
printf("%s \n Offset", Width);
printf("%s \n Offset", Height);
printf("%s \n Offset", Planes);
printf("%s \n Offset", BitsPerPixel);
printf("%s \n Compression", Compression);
printf("%s \n Compression", SizeImage);
printf("%s \n Compression", XPixelsPreMeter);
printf("%s \n Compression", YPixelsPreMeter);
printf("%s \n Compression", ColorsUsed);
printf("%s \n Compression", ColorsImportant);
 
initgraph(&gd, &gm, "");

//ShowBMP(0,0,"tune.bmp"); /* Enter File Name Here */

images = {"test.bmp", "test2.bmp", "test3.bmp"};
folder = "c:/documents/the_box/debug_tools";

#include "../labraries_stack/bitmap.c";

getch();
closegraph();

}