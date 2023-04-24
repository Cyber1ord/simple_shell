#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @mydata: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(data_t *mydata)
{
	if (!mydata->environ || mydata->env_changed)
	{
		mydata->environ = list_to_strings(mydata->env);
		mydata->env_changed = 0;
	}

	return (mydata->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @mydata: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(data_t *mydata, char *var)
{
	list_t *node = mydata->env;
	char *p;
	size_t i = 0;

	if (!node || !var)
		return (0);

	do {
		p = starts_with(node->str, var);
		if (p && *p == '=') {
			mydata->env_changed = delete_node_at_index(&(mydata->env), i);
			i = 0;
			node = mydata->env;
			continue;
		}
		node = node->next;
		i++;
	} while (node);

	return (mydata->env_changed);
}


/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @mydata: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(data_t *mydata, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = mydata->env;

	do
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			mydata->env_changed = 1;
			return (0);
		}
		node = node->next;
	} while (node);

	add_node_end(&(mydata->env), buf, 0);
	free(buf);
	mydata->env_changed = 1;
	return (0);
}


/**
 * is_cmd - determines if a file is an executable command
 * @mydata: the mydata struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(data_t *mydata, char *path)
{
	struct stat st;

	(void)mydata;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

