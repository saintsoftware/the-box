//https://cboard.cprogramming.com/c-programming/115855-how-properly-call-executable-c-code.html

/*
#!/usr/bin/python

# For each source file in GraphApp, compile it thus:
#  gcc -O2 -Wall -I. -Ietc -c -o objects/file.o subdir/file.c
# Then build the static library form of GraphApp, thus:
#  ar rc libapp.a objects/*.o
# Uses full paths.
*/

char application_title;
char target_platform = "";
char project_base = "" ;
char gcc_base = ""

char compile[][];

char compile[][] = {"win32", "/apps/app/", "/MinGW/" };
char compile[][] = {"x11", "/home/loki/apps/app/", "/usr/" };

char compile_index_arrays[][] = {"platform", "directory", "gcc" };


char source_base          = project_base + 'src/' ;
char object_base          = source_base +       'objects/' ;
char gcc_inc              = gcc_base + 'include/' ;
char gcc_bin              = gcc_base + 'bin/' ;
char gcc                  = gcc_bin +       'gcc' ; 
char make_static_lib      = gcc_bin +       'ar rc' ;
char ranlib_static_lib    = gcc_bin +       'ranlib' ;
char gcc_flags            = '-O2 -Wall' ;
char gcc_compile          = '-c' ;
char gcc_outfile          = '-o' ;
char static_lib           = source_base + 'libapp.a' ;
char source_dirs          = [target_platform,
	'utility', 'gui',
	'libz', 'libpng', 'libjpeg', 'libgif', 'imgfmt',
	]
char include_dirs         = ['.'] + source_dirs;
int verbose              = 1;

main(int argc, char *argv[]) 
{
	
	//# Use full paths unless we're compiling within the source_base dir.
	
	srcb = source_base
	cwd = os.getcwd()
	
	if cwd == source_base or cwd == source_base[:-1]:
		srcb = ''
	# Determine include paths.
	inc = ''
	
	for id in include_dirs:
		inc = inc + '-I' + srcb + id + ' '
	inc = inc + '-I' + gcc_inc
	# Compile
	
	for sd in source_dirs:
		files = os.listdir(srcb + sd)
		for file in files:
			if file[-2:] == '.c':
				compile(srcb + sd + '/', file[:-2], '.c', inc)

	build_static_lib()
				
def compile(filepath, name, ext, include_paths):
	object_file = object_base + name + '.o'
	source_file = filepath + name + ext
	if newer(object_file, source_file):
		return
	cmd = gcc
	cmd = cmd + ' ' + gcc_flags
	cmd = cmd + ' ' + include_paths
	cmd = cmd + ' ' + gcc_compile
	cmd = cmd + ' ' + gcc_outfile + ' ' + object_file
	cmd = cmd + ' ' + source_file
	perform(cmd)

def newer(fileA, fileB):
	try:
		timestampA = os.stat(fileA).st_mtime
		timestampB = os.stat(fileB).st_mtime
		if timestampA > timestampB:
			return 1
		return 0
	except:
		return 0

def build_static_lib():
	try:
		os.remove(static_lib)
	except:
		pass

	cmd = make_static_lib + ' ' + static_lib + ' ' + object_base + '*.o'
	perform(cmd)

	if ranlib_static_lib:
		cmd = ranlib_static_lib + ' ' + static_lib
		perform(cmd)

}

int call_exe()
{
	char exe = "prog.exe";
    int retv;
 
     //in command prompt it is executed as C:> prog.exe options
	 
     retv = system(exe);  
     
	 if(retv != 0){
		 return 1;
	 }
         
}