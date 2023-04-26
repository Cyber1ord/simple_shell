#include "shell.h"

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @mydata: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(data_t *mydata)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(mydata->alias, mydata->argv[0], '=');
		if (!node)
			return (0);
		free(mydata->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		mydata->argv[0] = p;
	}
	return (1);
}

/**
 * unset_alias - sets alias to string
 * @mydata: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(data_t *mydata, char *str)
{
	char *p;
	char c;
	int ret;

	p = str;
	while (*p && *p != '=')
		p++;
	if (*p == '\0')
		return (1);
	c = *p;
	*p = '\0';
	ret = delete_node_at_index(&(mydata->alias),
			get_node_index(mydata->alias, node_starts_with(mydata->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @mydata: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(data_t *mydata, char *str)
{
	char *p = str;
	int index;
	int ret;
	char *alias;

	while (*p != '\0' && *p != '=')
	{
		p++;
	}
	if (*p == '\0')
	{
		return (1);
	}
	if (*++p == '\0')
	{
		return (unset_alias(mydata, str));
	}

	alias = malloc(strlen(str) + 1);
	strcpy(alias, str);
	alias[p - str - 1] = '\0';

	index = get_node_index(mydata->alias, node_starts_with(mydata->alias, alias, -1));
	delete_node_at_index(&(mydata->alias), index);

	while (*p != '\0')
	{
		p++;
	}
	*p = '\0';

	ret = add_node_end(&(mydata->alias), str, 0) == NULL;
	*p = '=';

	return (ret);
}


/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p, *a;

	if (!node)
		return (1);

	p = _strchr(node->str, '=');
	a = node->str;

	/* Print the name part of the alias */
	while (a <= p)
		_putchar(*a++);

	_putchar('\'');

	/* Print the value part of the alias */
	while (*p)
		_putchar(*p++);

	_putchar('\'');
	_putchar('\n');

	return (0);
}


/**
 * _alias - mimics the alias builtin (man alias)
 * @mydata: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _alias(data_t *mydata)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (mydata->argc == 1)
	{
		node = mydata->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	i = 1;
	while (mydata->argv[i])
	{
		p = _strchr(mydata->argv[i], '=');
		if (p)
		{
			set_alias(mydata, mydata->argv[i]);
		}
		else
		{
			node = node_starts_with(mydata->alias, mydata->argv[i], '=');
			if (node)
			{
				print_alias(node);
			}
			else
			{
				print_error(mydata, "alias: ");
				_eputs(mydata->argv[i]);
				_eputs(": not found\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}
