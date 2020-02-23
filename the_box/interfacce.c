#include <alloc.h>
#include <conio.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>


// ========== DECLARATION =================

extern int image_color;
extern int image_VGA;
extern int image_VGAHI;


/*  GENERIC VARIABLES */

char file_name = "test.bmp";

int color;
int gd , gm ;
	gd = VGA ; gm = VGAHI;
 
extern char bmp_Type[2];           //File type. Set to "BM".
extern unsigned long bmp_Size;     //Size in BYTES of the file.
extern unsigned long bmp_Reserved;      //Reserved. Set to zero.
extern unsigned long image_OffSet;   //Offset to the data.
extern unsigned long image_headsize; //Size of rest of header. Set to 40.
extern unsigned long image_Width;     //Width of bitmap in pixels.
extern unsigned long Height;     //  Height of bitmap in pixels.
extern unsigned int  Planes;    //Number of Planes. Set to 1.
extern unsigned int  BitsPerPixel;       //Number of Bits per pixels.
extern unsigned long Compression;   //Compression. Usually set to 0.
extern unsigned long SizeImage;  //Size in bytes of the bitmap.
extern unsigned long XPixelsPreMeter;     //Horizontal pixels per meter.
extern unsigned long YPixelsPreMeter;     //Vertical pixels per meter.
extern unsigned long ColorsUsed;   //Number of colors used.
extern unsigned long ColorsImportant;  //Number of "important" colors. 
 
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
 
int ShowBMP(int x, int y, char* FileName){
	
    int b, a;
    BMP Obj;
 
    unsigned char* Datas;
    int in=0;
    unsigned char c=0;
    
    file = fopen(FileName, "rb");
    
	if(!fp){
		printf("Error : Unable to open file ..");
		exit(0);
    }
 
    fread(&Obj, sizeof(Obj), 1, fp);
    
	if(Obj.BitsPerPixel !=4 )  // This isn't a 16 color bmp we can read;
    {
		fclose(fp);
		printf("Error : File format not supported ..");
		exit(0);
    };
	
    fseek(fp,Obj.OffSet,SEEK_SET);
	
    Datas = (unsigned char*) calloc(Obj.Width/2+1, sizeof(unsigned char));
    
	for(b=Obj.Height; b >= 0; b--)
    {
		fread(Datas, sizeof(unsigned char), Obj.Width/2, fp);
		c=0;
		in=0;
		
		 for(a=0;a<=Obj.Width;a+=2)
		 {
			 c = (Datas[in] | 0x00) >>4;
			 putpixel(a+x,b+y,c);
			 c = (Datas[in] | 0xF0) & 0x0F;
			 putpixel(a+1+x,b+y,c);
			 in++;
		 }
    }
	
    free (Datas);
    fclose(fp);
    return 1;
	
}

void main()
{
	int color;
	int gd , gm ;
	gd = VGA ; gm = VGAHI;
	 
	initgraph(&gd,&gm,"");
	
	ShowBMP(0,0,"tune.bmp"); /* Enter File Name Here */
	
	getch();
	closegraph();
}