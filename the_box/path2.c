
/**

 * Concatenates the provided paths, adding path separator characters
 * whenever needed.
 *
 * \param path First path component.
 * \param ... NULL terminated list of path components.
 * \return A new string or NULL.
 */


char path_size(){

	/* Calculate the length. */

	last = total? path[total - 1] : ' ';
	va_start (args, path);

	while ((ptr = va_arg (args, char*)))
	{
		if ((len = strlen (ptr)))
		{
			if (last != '/' && *ptr != '/')
				total++;
			total += len;
			last = ptr[len - 1];
		}
	}

	va_end (args);
}

char* path_concatenate ()
{

	/* Calculate the length. */

	last = total? path[total - 1] : ' ';
	va_start (args, path);

	while ((ptr = va_arg (args, char*)))
	{
		if ((len = strlen (ptr)))
		{
			if (last != '/' && *ptr != '/')
				total++;
			total += len;
			last = ptr[len - 1];
		}
	}

	va_end (args);

	/* Allocate a new string. */

	self = lisys_malloc (total + 1);

	if (self == NULL)
	{
		lisys_error_set (ENOMEM, "not enough memory to construct path");
		return NULL;
	}

	/* Concatenate the elements. */

	strcpy (self, path); //

	last = total? path[total - 1] : ' ';
	va_start (args, path);

	while ((ptr = va_arg (args, char*)))
	{
		if ((len = strlen (ptr)))
		{
			if (last != '/' && *ptr != '/')
				self[total++] = '/';
			strcpy (self + total, ptr);
			total += len;
			last = ptr[len - 1];
		}
	}

	va_end (args);

	return self;
}


/**
 *
 * In addition to any ordinary string being appended to the path as such and a
 * NULL argument terminating the path, the following special instructions are
 * recognized:
 *
 * \li \c LISYS_PATH_BASENAME Appends the base name of the next string.
 * \li \c LISYS_PATH_PATHNAME Appends the path name of the next string.
 * \li \c LISYS_PATH_SEPARATOR Appends a path separator if one isn't present already.
 * \li \c LISYS_PATH_STRIPEXT Removes an extension from the path if one is present.
 * \li \c LISYS_PATH_STRIPEXTS Removes all extensions from the path.
 * \li \c LISYS_PATH_STRIPLAST Removes the last path component.
 *
 * \param format Path format instruction.
 * \param ... Variable array of path format instructions.
 * \return Path string or NULL.
 */

char* path_format (){

	const char* arg;
	va_list args;

	/* Allocate buffer. */

	pos = 0;
	cap = 64;
	self = lisys_malloc (cap);

	if (self == NULL)
	{
		lisys_error_set (ENOMEM, "not enough memory to construct path");
		return NULL;
	}
	self[0] = '\0';

	/* Fill buffer. */

	va_start (args, format);
	for (error = last = 0 ; format != NULL ; format = va_arg (args, char*))
	{
		/* Identify format code. */

		if (format == LISYS_PATH_BASENAME)
		{
			/* Append base name of the next string. */

			arg = va_arg (args, char*);
			tmp = strrchr (arg, '/');
			if (tmp != NULL)
				arg = tmp + 1;
			len = strlen (arg);
		}
		else if (format == LISYS_PATH_PATHNAME)
		{
			/* Append path name of the next string. */

			arg = va_arg (args, char*);
			if (*arg == '/' && last == '/')
				arg++;
			tmp = strrchr (arg, '/');
			len = tmp? tmp - arg : strlen (arg);
		}
		else if (format == LISYS_PATH_SEPARATOR)
		{
			/* Append separator if not duplicate. */

			arg = (last != '/')? "/" : "";
			len = (last != '/')? 1 : 0;
		}
		else if (format == LISYS_PATH_STRIPEXT)
		{
			/* Strip extension. */

			for (tmp = self + pos - 1 ; tmp > self ; tmp--)
			{
				if (*tmp == '/' || *tmp == '.')
					break;
			}
			if (tmp > self && tmp[0] == '.' && tmp[-1] != '/')
			{
				pos = tmp - self;
				last = tmp[-1];
			}
			continue;
		}
		else if (format == PATH_STRIPEXTS)
		{
			/* Strip all extensions. */
			for (tmp = self + pos - 1 ; tmp > self ; tmp--)
			{
				if (*tmp == '/')
					break;
				if (*tmp == '.' && tmp[-1] != '/')
				{
					pos = tmp - self;
					last = tmp[-1];
				}
			}
			continue;
		}
		else if (format == PATH_STRIPLAST)
		{
			/* Strip last component. */
			while (1)
			{
				for (tmp = self + pos - 1 ; *tmp != '/' && tmp > self ; tmp--)
					;
				if (tmp > self)
				{
					if (pos > 0)
						last = self[pos - 1];
					else
						last = '\0';
					if (tmp == self + pos - 1)
					{
						pos--;
						continue;
					}
					pos = tmp - self;
				}
				break;
			}
			continue;
		}
		else
		{
			/* Append format as an ordinary string. */

			arg = format;
			len = strlen (arg);
		}

		/* Resize buffer. */

		if (cap <= pos + len)
		{
			while (cap <= pos + len)
				cap <<= 1;
			tmp = lisys_realloc (self, cap);
			if (tmp == NULL)
			{
				error = 1;
				break;
			}
			self = tmp;
		}

		/* Append to buffer. */

		strncpy (self + pos, arg, len);
		pos += len;
		last = arg[len - 1];
	}
	va_end (args);
	self[pos] = '\0';

	/* Check for errors. */

	if (error){

		lisys_error_set (ENOMEM, "not enough memory to construct path");
		lisys_free (self);
		return NULL;
	}

	/* Shrink buffer. */

	tmp = lisys_realloc (self, pos + 1);
	if (tmp != NULL)
		self = tmp;

	return self;
}

static void file_scan_save_directory (LIScrArgs* args)
{

	/**
		Gets the home directory.
	 * If no home directory is specified, the current
	 * working directory is returned instead.
	 * \return New string or NULL if out of memory.
	 */

	/* Construct the path. */

	module = liscr_script_get_userdata (args->script, LIEXT_SCRIPT_FILE);

	if (!liscr_args_geti_string (args, 0, &path))
		return;
	if (strstr (path, ".."))
		return;

	for (i = 0 ; i < strlen (path) ; i++)
	{
		if ((path[i] < 'a' || path[i] > 'z') && (path[i] < '0' || path[i] > '9') &&
		    (path[i] != '/' && path[i] != '.' && path[i] != '-' && path[i] != '_'))
			return;
	}

	path_abs = lisys_path_concat (module->program->paths->module_data_save, path, NULL);

	/* Scan the directory. */

	dir = lisys_dir_open (path_abs);
	lisys_free (path_abs);

	if (dir == NULL)
		return;
	lisys_dir_set_sorter (dir, lisys_dir_sorter_alpha);

	if (!lisys_dir_scan (dir))
	{
		lisys_dir_free (dir);
		return;
	}

	/* Return the file names. */

	liscr_args_set_output (args, LISCR_ARGS_OUTPUT_TABLE_FORCE);

	count = lisys_dir_get_count (dir);

	for (i = 0 ; i < count ; i++)
	{
		name = lisys_dir_get_name (dir, i);
		if (name[0] != '.')
			liscr_args_seti_string (args, name);
	}

	lisys_dir_free (dir);
}

char * paths_get_home ()
{

	char* home;

	home = getenv ("HOME");

	if (home != NULL){
		return string_dump  (home);
	}

	return string_dump  (".");

}


char* paths_get_data_home (){

	/**
	 * \brief Gets the home data directory.
	 *
	 * Follows the XDG Base Directory Specification:
	 * http://www.freedesktop.org/Standards/basedir-spec
	 *
	 * \return New string or NULL.
	 */

	dir = getenv ("XDG_DATA_HOME");
	if (dir != NULL && dir[0] != '\0')
		return lisys_string_dup  (dir);
	tmp = lisys_paths_get_home ();
	if (tmp == NULL)
		return NULL;
	ret = lisys_path_concat (tmp, ".local/share", NULL);
	lisys_free (tmp);

	return ret;

}

/**
 * \brief Gets the home config directory.
 *
 * Follows the XDG Base Directory Specification:
 * http://www.freedesktop.org/Standards/basedir-spec
 *
 * \return New string or NULL.
 */

char* paths_get_config_home (){

	char* ret;
	char* tmp;
	const char* dir;

	dir = getenv ("XDG_CONFIG_HOME");

	if (dir != NULL && dir[0] != '\0')
		return lisys_string_dup  (dir);
	tmp = lisys_paths_get_home ();
	if (tmp == NULL)
		return NULL;
	ret = lisys_path_concat (tmp, ".config", NULL);
	lisys_free (tmp);

	return ret;
}

/**
 * \brief Gets the home cache directory.
 *
 * Follows the XDG Base Directory Specification:
 * http://www.freedesktop.org/Standards/basedir-spec
 *
 * \return New string or NULL.
 */

char* lisys_paths_get_cache_home ()
{

	char* ret;
	char* tmp;
	const char* dir;

	dir = getenv ("XDG_CACHE_HOME");
	if (dir != NULL && dir[0] != '\0')
		return lisys_string_dup  (dir);
	tmp = lisys_paths_get_home ();
	if (tmp == NULL)
		return NULL;
	ret = lisys_path_concat (tmp, ".cache", NULL);
	lisys_free (tmp);

	return ret;

}

/**
 * \brief Gets the global data directory.
 *
 * Follows the XDG Base Directory Specification:
 * http://www.freedesktop.org/Standards/basedir-spec
 *
 * \param path Relative path being searched for.
 * \return New string or NULL.
 */

char* paths_get_data_global (const char* path){

#ifdef __WIN32__
	return NULL;
#else

	/* Get the list of global data directories. */

	dirs = getenv ("XDG_DATA_DIRS");
	if (dirs == NULL || dirs[0] == '\0')
		return NULL;

	dup = string_dump  (dirs);
	if (dup == NULL)
		return NULL;

	/* Loop through all directories. */
	ptr = start = dup;
	ret = NULL;
	last = 0;
	while (1)
	{
		/* Search for the delimiter. */
		last = (*ptr == '\0');
		if (*ptr != ':' && !last)
		{
			ptr++;
			continue;
		}
		*ptr = '\0';

		/* Test if the path is valid. */
		ret = lisys_path_concat (start, path, NULL);
		if (ret != NULL)
		{
			if (lisys_filesystem_access (ret, LISYS_ACCESS_READ))
				break;
			lisys_free (ret);
			ret = NULL;
		}

		/* Check if more candidates exist. */
		if (last)
			break;
		ptr++;
		start = ptr;
	}

	/* Return the result or NULL. */
	lisys_free (dup);
	return ret;
#endif
}


#endif


/*Gets the file name without the path component.*/


char* path_basename (const char* path){
	char * ptr;

	ptr = strrchr (path, '/');

	if (ptr == NULL){
		return private_strdup (path);
	}

	return private_strdup (ptr + 1);
}

int validate_path_extension (const char* path, ){

	/* Check for the length. */

	if (path_length < extension_length + 1){
		return 0;
	}

	/* Check for the period. */

	if (path[path_length - extension_length - 1] != '.'){
		return 0;
	}

	/* Check for the extension string. */

	if (strcmp (path + path_length - extension_length, ext)){

		return 0;
	}

	return 1;
}


/* brief Gets the file name from a path.*/

char* path_filename (const char* path){

	const char* ptr;

	ptr = strrchr (path, '/');
	if (ptr == NULL)
		return private_strdup (path);

	return private_strdup (ptr + 1);
}

/* brief Gets the extension from a path.*/

char* path_file_ext (const char* path){

	const char* ptr0;
	const char* ptr1;

	ptr0 = strrchr (path, '.');
	ptr1 = strrchr (path, '/');

	if (ptr0 == NULL){
		return private_strdup ("");
	}

	if (ptr1 != NULL && ptr0 < ptr1){
		return private_strdup ("");
	}

	return private_strdup (ptr0 + 1);
}

/**
 * \brief Gets the base path name from a path.
 * \param path Path string.
 * \return New string or NULL.
 */

char* path_pathname (const char* path){

	char* ret;

	ptr = strrchr (path, '/');

	if (ptr == NULL){
		return private_strdup (".");
	}

	if (ptr == path){
		return private_strdup ("/");
	}

	ret = lisys_malloc (ptr - path + 1);

	if (ret == NULL){
		return NULL;
	}

	strncpy (ret, path, ptr - path);
	ret[ptr - path] = '\0';

	return ret;
}

