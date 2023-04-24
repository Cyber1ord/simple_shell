#include "shell.h"

/**
 * _menv - prints the current environment
 * @mydata: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _menv(data_t *mydata)
{
	print_list_str(mydata->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @mydata: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(data_t *mydata, const char *name)
{
	list_t *node = mydata->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _msetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @mydata: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _msetenv(data_t *mydata)
{
	if (mydata->argc != 3)
	{
		_eputs("Invalid number of arguements\n");
		return (1);
	}
	if (_setenv(mydata, mydata->argv[1], mydata->argv[2]))
		return (0);
	return (1);
}

/**
 * _munsetenv - Remove an environment variable
 * @mydata: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _munsetenv(data_t *mydata)
{
	int i;

	if (mydata->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= mydata->argc; i++)
		_unsetenv(mydata, mydata->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @mydata: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(data_t *mydata)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	mydata->env = node;
	return (0);
}
