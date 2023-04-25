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
			_puts("$ ");
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

/**
 * find_builtin - finds a builtin command
 * @mydata: the parameter & return mydata struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(data_t *mydata)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _rexit},
		{"env", _menv},
		{"help", _help},
		{"history", _history},
		{"setenv", _msetenv},
		{"unsetenv", _munsetenv},
		{"cd", _cd},
		{"alias", _alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(mydata->argv[0], builtintbl[i].type) == 0)
		{
			mydata->line_count++;
			built_in_ret = builtintbl[i].func(mydata);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @mydata: the parameter & return mydata struct
 *
 * Return: void
 */
void find_cmd(data_t *mydata)
{
	char *path = NULL;
	int i, k;

	mydata->path = mydata->argv[0];
	if (mydata->linecount_flag == 1)
	{
		mydata->line_count++;
		mydata->linecount_flag = 0;
	}
	for (i = 0, k = 0; mydata->arg[i]; i++)
		if (!is_delim(mydata->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(mydata, _getenv(mydata, "PATH="), mydata->argv[0]);
	if (path)
	{
		mydata->path = path;
		fork_cmd(mydata);
	}
	else
	{
		if ((interactive(mydata) || _getenv(mydata, "PATH=")
			|| mydata->argv[0][0] == '/') && is_cmd(mydata, mydata->argv[0]))
			fork_cmd(mydata);
		else if (*(mydata->arg) != '\n')
		{
			mydata->status = 127;
			print_error(mydata, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @mydata: the parameter & return mydata struct
 *
 * Return: void
 */
void fork_cmd(data_t *mydata)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(mydata->path, mydata->argv, get_environ(mydata)) == -1)
		{
			free_data(mydata, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(mydata->status));
		if (WIFEXITED(mydata->status))
		{
			mydata->status = WEXITSTATUS(mydata->status);
			if (mydata->status == 126)
				print_error(mydata, "Permission denied\n");
		}
	}
}
