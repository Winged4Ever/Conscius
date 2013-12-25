/*Syntax: */
int userLogin()
{
	char prompt;

	while (1 == 1)
	{
		/*TODO: Each time this loop begins, it should overwrite the line*/
		/*TODO: Turn off terminal's history of entered values*/
		printf("Username: ");
		fgets (prompt , 20 , stdin);
		/*If the player would like to exit the game without loggining in*/
		if (strcmp(prompt, "exit") == 0)
			{
				break;
			}
		/*If the player would like to create a new account*/
		if (strcmp(prompt, "create") == 0)
		{
			createAccount();
			continue;
		}
		/*If provided username do not exist*/
		if (checkUsername(&prompt) == FALSE)
		{
			terminalPrint(i1,"Ivalid username, try again");
			continue;
		}
		strcpy(username, prompt);
		/*If provided username exist*/
		while (1 == 1)
		{
			/*TODO: Each time this loop begins, it should overwrite the line*/
			/*TODO: stars instead of visible password*/
			printf("Password: ");
			fgets (prompt , 20 , stdin);
			if (strcmp(prompt, "exit") == 0)
				{
					break;
				}
			if (checkPassword(&prompt) == FALSE)
			{
				terminalPrint(i1,"Ivalid password, try again");
				continue;
			}
			return 0;
		}
	}
	return EXIT;
}
/*End of userLogin*/

/*Syntax: */
int checkUsername(char* username)
{
	int found;

	if (found == TRUE)
	{
		return TRUE;
	}
	return FALSE;
}
/*End of checkUsername*/

/*Syntax: */
int checkPassword(char* username)
{
	int found;

	if (found == TRUE)
	{
		return TRUE;
	}
	return FALSE;
}

/*Syntax: */
void createAccount()
{
	/*TODO: Exclude the usage of words : exit, create*/

}
/*End of createAccount*/

/*This function will print things in the terminal*/
/*Syntax: terminalPrint(place, "string");*/
void f_terminalPrint(char *where, char *string)
{
	/*Hearing area*/
	if (strcmp(where, "@") == 0)
	{

	}
	/*First line of input center*/
	if (strcmp(where, "i1") == 0)
	{

	}
}
/*End of f_terminalPrint1*/
