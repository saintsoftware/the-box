

/*
	Manage the user local and with a database :
	- User Object (used in: standard games, social tool)
	- Local login
	- Database login
	- Files 
	   .users.txt - update uses localy before online.
*/

char user_name;
char user_password;
char user_mail;
int user_friends;
int user_characters;
char user_games[][];

debug = 0;

if(debug == 1){
    printf("File  'user.h' -  \n ", );
}
else if(debug == 2){
    printf("File  'user.h' -  \n  Variables : user '%s' password '%s' email %s\n",
            user_name, user_password, user_mail );
}

// ========== DECLARATION =================

struct passwd* password;

// ========== DEFINITION =================


void user_variables (){
	
	user_name = "";
	user_password = "";
	user_id = "";
	
	pwd = getpwuid (uid);
	ret = strdup (pwd->pw_name);
		
	if (ret == NULL)
	{
		lisys_error_set (ENOMEM, NULL);
		return NULL;
	}

	return ret;
	
}	

void user_auth (){
	
	if (user_password == NULL)
	{
		error_build();	
		error_set (errno, NULL);
		return NULL;
	}
	elseif(user_name == NULL){
		error_build();
		error_set (errno, NULL);
		return NULL;
	}
	
	error_set (ENOTSUP, NULL);
	return NULL;
}