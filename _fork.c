#include "shell.h"

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
/**
 * cd_next - Changes the current working directory to the next directory
 *           specified in mydata->argv or CDPATH, if it exists.
 *
 * @mydata: Pointer to the data structure containing command arguments and
 *          environment variables.
 *
 * Return: 0 on success, 1 on failure.
 */
int cd_next(data_t *mydata)
{
	char *dir_copy;
	char *dir_part;
	char *path;
	char buffer[1024];
	char *dir = mydata->argv[1] ? mydata->argv[1] : _getenv(mydata, "CDPATH");

	if (!dir)
	{
		print_error(mydata, "cd: missing argument\n");
		return (1);
	}
	if (chdir(dir) == -1)
	{
		path = _getenv(mydata, "CDPATH");
		if (!path)
		{
			print_error(mydata, "cd: cannot change directory to ");
			_eputs(dir);
			_eputchar('\n');
			return (1);
		}
		dir_copy = strdup(dir);
		dir_part = strtok(dir_copy, "/");
		while (dir_part)
		{
			snprintf(buffer, sizeof(buffer), "%s/%s", path, dir_part);
			if (chdir(buffer) != -1)
			{
				dir = buffer;
				break;
			}
			dir_part = strtok(NULL, "/");
		}
		free(dir_copy);
		if (chdir(dir) == -1)
		{
			print_error(mydata, "cd: cannot change directory to ");
			_eputs(dir);
			_eputchar('\n');
			return (1);
		}
	}
	setenv("OLDPWD", getcwd(buffer, sizeof(buffer)), 1);
	return (0);
}
