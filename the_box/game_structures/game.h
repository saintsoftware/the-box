
char lenght = "256";

if(save == true){
	
	int models = 0;
	int level = 0;
	int equipment = 0;
	int skills = 0;
	int spells = 0;
	int user;
	
	FILE * fp;
   
   fp = fopen ("c:\\temp\\1.c","w"); /* open the file for writing*/ // If does not exist create
   
   for(counter_1 = 0; counter_1 < 10; counter_1++){ /* write 10 lines of text into the file stream*/
       fprintf (fp, "This is line %d\n", i + 1);
   }
 
	fclose (fp);/* close the file*/
	save = false;
}