// https://www.dreamincode.net/forums/topic/123767-compress-files-example/
// https://cboard.cprogramming.com/c-programming/127815-how-compress-data-binary-file.html


/*
	Temporary Data Tool
	
	Functionality : add torents, list torrents, anda management torrents
	
	Add mensages from text tool
	
	- Tool Object to abstract tools interface and manage variables and functions better
	-Menu 
	-Files (web_page, user)
	
	inherit: 
	- tool.h, used : information_index_converter(),
	- file.h, used : FILE_pointer, file_path, file, 
	- user.h
	
	Used :
	- 
	
*/

int time_donwloaded;
int file_size;
char file_type;
char orignal_post_user;
char users_with_file;
char users_sharing_file;
char compression;
bool share_file = 0;

#include <stdio.h>
#include <zlib.h>
#include <limits.h> /* for PATH_MAX */
 

int compressFile(FILE *in, const char * const outFileName)
{

   /* Buffer to hold data read */

   char buf[BUFSIZ] = { 0 };
   size_t bytes_read = 0;

   gzFile *out = gzopen(outFileName, "wb");

   if (!out)
   {

      /* Handle error */

      fprintf(stderr, "Unable to open %s for writing\n", outFileName);

      return -1;

   }

 
   bytes_read = fread(buf, 1, BUFSIZ, in);

   while (bytes_read > 0)
   {

      int bytes_written = gzwrite(out, buf, bytes_read);

      if (bytes_written == 0)

      {

         int err_no = 0;

         fprintf(stderr, "Error during compression: %s", gzerror(out, &err_no))\

;

         gzclose(out);

         return -1;

      }

      bytes_read = fread(buf, 1, BUFSIZ, in);

   }

   gzclose(out);

   return 0;

}


int main(void)
{

   char outFileName[PATH_MAX] = { 0 };
   FILE *fp = fopen(__FILE__, "r");

   if (fp)
   {

      sprintf(outFileName, "%s.gz", __FILE__);

      if (compressFile(fp, outFileName) != 0)
      {

         fclose(fp);
         return -1;

      }

      fclose(fp);

   }

   return 0;

}
