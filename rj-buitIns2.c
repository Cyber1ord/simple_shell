#include "rj-headers.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	list_t *node = info->history;

	while (node != NULL)
	{
		printf("%d %s\n", node->data.index, node->str);
		node = node->next;
	}
	return (0);
}


/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p = strchr(str, '=');

	if (p == NULL)
		return (1);
	if (*++p == '\0')
		return (unset_alias(info, str));
	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}


/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p = strchr(str, '=');

	if (p == NULL)
		return (1);
	*p = '\0';
	int ret = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = '=';
	return (ret);
}



/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int i;
	char *p;

	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node != NULL)
		{
			print_list(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = strchr(info->argv[i], '=');
		if (p != NULL)
			set_alias(info, info->argv[i]);
		else
			print_list(node_starts_with(info->alias, info->argv[i], '='));
	}
	return (0);
}


/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	if (node != NULL)
	{
		printf("%s\n", node->str);
		return (0);
	}
	return (1);
}



