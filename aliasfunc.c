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

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
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
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(mydata, str));
	unset_alias(mydata, str);
	ret = add_node_end(&(mydata->alias), str, 0) == NULL;

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
	char *p = NULL, *a = NULL;

	if (!node)
		return (1);

	p = _strchr(node->str, '=');
	a = node->str;

	/* Print the name part of the alias */
	for (a = node->str; a <= p; a++)
		_putchar(*a);
	_putchar('\'');
	/* Print the value part of the alias */
	_puts(p + 1);
	_puts("'\n");

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
			print_alias(node_starts_with(mydata->alias,
			mydata->argv[i], '='));
		}
		i++;
	}
	return (0);
}
