#include "shell.h"

/**
 * hsh - main shell loop
 * @mydata: the parameter & return mydata struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(data_t *mydata, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_data(mydata);
		if (interactive(mydata))
			_puts("CyberShell$ ");
		_putchar(BUF_FLUSH);
		r = get_input(mydata);
		if (r != -1)
		{
			set_data(mydata, av);
			builtin_ret = find_builtin(mydata);
			if (builtin_ret == -1)
				find_cmd(mydata);
		}
		else if (interactive(mydata))
			_putchar('\n');
		free_data(mydata, 0);
	}
	write_history(mydata);
	free_data(mydata, 1);
	if (!interactive(mydata) && mydata->status)
		exit(mydata->status);
	if (builtin_ret == -2)
	{
		if (mydata->err_num == -1)
			exit(mydata->status);
		exit(mydata->err_num);
	}
	return (builtin_ret);
}
