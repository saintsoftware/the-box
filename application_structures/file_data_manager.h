
/*
	Deriva do File
	The Box Data Manager, costume xml/jason format
*/


data_manager(char type){
	
	if(FILE_pointer != null){
		break;
	}

	if(type == "projects"){
		
	}

	char string[] = "strtok needs to be called several times to split a string";
	int string_size = strlen(string);
	char delim[] = ";";

	char *ptr = strtok(string, delim);

	while(ptr != NULL)
	{
		printf("'%s'\n", ptr);
		ptr = strtok(NULL, delim);
	}

	/* This loop will show that there are zeroes in the str after tokenizing */

	for (int i = 0; i < size_string; i++)
	{
		printf("%d ", string[i] ); /* Convert the character to integer, in this case the character's ASCII equivalent */
	}
	
	printf("\n");

	while (FILE_pointer){
		
	}

	while (++counter <= argc) {
		printf("\nListing %s...\n", argv[counter-1]);
		listdir(argv[counter-1]);
	}
}

