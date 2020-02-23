
/*
	Deriva do File
*/

while (++counter <= argc) {
printf("\nListing %s...\n", argv[counter-1]);
listdir(argv[counter-1]);
}