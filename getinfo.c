#include "shell.h"

/**
 * clear_data - initializes data_t struct
 * @mydata: struct address
 */
void clear_data(data_t *mydata)
{
	mydata->arg = NULL;
	mydata->argv = NULL;
	mydata->path = NULL;
	mydata->argc = 0;
}

/**
 * set_data - initializes data_t struct
 * @mydata: struct address
 * @av: argument vector
 */
void set_data(data_t *mydata, char **av)
{
	int i = 0;

	mydata->fname = av[0];
	if (mydata->arg)
	{
		mydata->argv = strtow(mydata->arg, " \t");
		if (!mydata->argv)
		{

			mydata->argv = malloc(sizeof(char *) * 2);
			if (mydata->argv)
			{
				mydata->argv[0] = _strdup(mydata->arg);
				mydata->argv[1] = NULL;
			}
		}
		for (i = 0; mydata->argv && mydata->argv[i]; i++)
			;
		mydata->argc = i;

		replace_alias(mydata);
		replace_vars(mydata);
	}
}

/**
 * free_data - frees data_t struct fields
 * @mydata: struct address
 * @all: true if freeing all fields
 */
void free_data(data_t *mydata, int all)
{
	ffree(mydata->argv);
	mydata->argv = NULL;
	mydata->path = NULL;
	switch (all) {
	case 1:
		if (!mydata->cmd_buf)
			free(mydata->arg);
		if (mydata->env)
			free_list(&(mydata->env));
		if (mydata->history)
			free_list(&(mydata->history));
		if (mydata->alias)
			free_list(&(mydata->alias));
		ffree(mydata->environ);
			mydata->environ = NULL;
		bfree((void **)mydata->cmd_buf);
		if (mydata->readfd > 2)
			close(mydata->readfd);
		_putchar(BUF_FLUSH);
		break;
	default:
		break;
}

}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - finds this cmd in the PATH string
 * @mydata: the mydata struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(data_t *mydata, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
    return (NULL);

if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
{
    if (is_cmd(mydata, cmd))
        return (cmd);
}

do
{
    if (!pathstr[i] || pathstr[i] == ':')
    {
        path = dup_chars(pathstr, curr_pos, i);
        if (!*path)
            _strcat(path, cmd);
        else
        {
            _strcat(path, "/");
            _strcat(path, cmd);
        }
        if (is_cmd(mydata, path))
            return (path);
        if (!pathstr[i])
            break;
        curr_pos = i;
    }
    i++;
} while (1);

return (NULL);

}
