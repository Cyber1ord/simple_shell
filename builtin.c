#include "shell.h"

/**
 * _rexit - exits the shell
 * @mydata: Pointer to a structure containing potential arguments
 *  Return: 2 if there is an exit argument, otherwise -2
 */
int _rexit(data_t *mydata)
{
	int exitcheck;

	if (mydata->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = _erratoi(mydata->argv[1]);
		if (exitcheck == -1)
		{
			mydata->status = 2;
			print_error(mydata, "Invalid number: ");
			_eputs(mydata->argv[1]);
			_eputchar('\n');
			return (1);
		}
		mydata->err_num = _erratoi(mydata->argv[1]);
		return (-2);
	}
	mydata->err_num = -1;
	return (-2);
}

/**
 * _cd - changes the current directory of the process
 * @mydata: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _cd(data_t *mydata)
{
    char *s, *dir, buffer[1024];
    int chdir_ret;

    s = getcwd(buffer, 1024);
    if (!s)
    {
        _puts("TODO: >>getcwd failure emsg here<<\n");
    }

    if (!mydata->argv[1])
    {
        dir = _getenv(mydata, "HOME=");
        if (!dir)
        {
            dir = _getenv(mydata, "PWD=");
        }

        while (dir && *dir && *dir == ' ')
        {
            dir++;
        }

        chdir_ret = chdir(dir);
    }
    else if (_strcmp(mydata->argv[1], "-") == 0)
    {
        dir = _getenv(mydata, "OLDPWD=");
        if (!dir)
        {
            _puts(s);
            _putchar('\n');
            return (1);
        }

        while (dir && *dir && *dir == ' ')
        {
            dir++;
        }

        _puts(dir);
        _putchar('\n');

        chdir_ret = chdir(dir);
    }
    else
    {
        dir = mydata->argv[1];

        while (dir && *dir && *dir == ' ')
        {
            dir++;
        }

        chdir_ret = chdir(dir);
    }

    if (chdir_ret == -1)
    {
        print_error(mydata, "can't cd to ");
        _eputs(dir);
        _eputchar('\n');
    }
    else
    {
        _setenv(mydata, "OLDPWD", _getenv(mydata, "PWD="));
        _setenv(mydata, "PWD", getcwd(buffer, 1024));
    }

    return (0);
}


/**
 * _help - changes the current directory of the process
 * @mydata: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _help(data_t *mydata)
{
	char **arg_array = mydata->argv;
	int i = 0;

	_puts("help call works. Function not yet implemented \n");
	
	while (arg_array[i] != NULL)
	{
		if (0)
			_puts(arg_array[i]); /* temp att_unused workaround */
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


