#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @mydata: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(data_t *mydata, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		mydata->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		mydata->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		mydata->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @mydata: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(data_t *mydata, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (mydata->cmd_buf_type == CMD_AND)
	{
		if (mydata->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (mydata->cmd_buf_type == CMD_OR)
	{
		if (!mydata->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * _history - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @mydata: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _history(data_t *mydata)
{
	print_list(mydata->history);
	return (0);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @mydata: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(data_t *mydata)
{
	int i = 0;
	list_t *node;

	for (i = 0; mydata->argv[i]; i++)
	{
		if (mydata->argv[i][0] != '$' || !mydata->argv[i][1])
			continue;

		if (!_strcmp(mydata->argv[i], "$?"))
		{
			replace_string(&(mydata->argv[i]),
				_strdup(convert_number(mydata->status, 10, 0)));
			continue;
		}
		if (!_strcmp(mydata->argv[i], "$$"))
		{
			replace_string(&(mydata->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(mydata->env, &mydata->argv[i][1], '=');
		if (node)
		{
			replace_string(&(mydata->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&mydata->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
