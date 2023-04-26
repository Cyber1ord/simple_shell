#include "shell.h"

/**
 * _rexit - exits the shell
 * @mydata: Pointer to a structure containing potential arguments
 *  Return: 2 if there is an exit argument, otherwise -2
 */
int _rexit(data_t *mydata)
{
	char *endptr;
	int exitcode;

	if (!mydata->argv[1])
	{
		mydata->err_num = -1;
		return (-2);
	}
	exitcode = strtol(mydata->argv[1], &endptr, 10);
	if (*endptr != '\0')
	{
		mydata->status = 2;
		print_error(mydata, "Invalid number: ");
		_eputs(mydata->argv[1]);
		_eputchar('\n');
		return (1);
	}
	mydata->err_num = exitcode;
	mydata->status = (exitcode % 256);
	return (0);

}


/**
 * _help - Prints help information about available shell commands
 * @mydata: Structure containing potential arguments
 * Return: Always 0
 *
 **/
int _help(data_t *mydata)
{
	char **arg_array = mydata->argv;
	int i = 0;

	_puts("help call works. Function not yet implemented \n");

	while (arg_array[i] != NULL)
	{
		if (0)
			_puts(arg_array[i]);
		i++;
	}

	return (0);
}


/**
 * bfree - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	int freed = 0;

	while (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		freed = 1;
	}
	return (freed);
}
