#include "shell.h"

/**
 * MAX_HISTORY - maximum number of commands
 * to store in history
 * history - array to store command history
 * history_count - current number of commands
 * stored in history
 *
 **/

char *history[MAX_HISTORY];
int history_count = 0;

/**
 * add_to_history - Adds a command to the command history.
 * @command: the command to be added to the history
 * Description: If the history is full, the oldest command is
 * removed to make room for the new command
 *
 **/
void add_to_history(char *command)
{
	/* If the history is full, remove the oldest command */
	if (history_count == MAX_HISTORY)
	{
		int i;

		free(history[0]);
		for (i = 1; i < history_count; i++)
		{
			history[i - 1] = history[i];
		}
		history_count--;
	}
	/* Add the new command to the end of the history */
	history[history_count] = strdup(command);
	history_count++;
}
/**
 * print_history - Prints the command history.
 * Description: Prints the command history with
 * their respective index
 *
 **/
void print_history()
{
	int i;

	for (i = 0; i < history_count; i++)
	{
		printf("%d: %s\n", i + 1, history[i]);
	}
}
/**
 * get_command_from_history - Retrieves a command from the
 * command history.
 * @n: the index of the command to be retrieved
 * Return: the command at the specified index, or NULL if
 * the index is out of range
 *
 **/
char *get_command_from_history(int n)
{
	if (n < 1 || n > history_count)
	{
		return (NULL);
	}
	return (history[n - 1]);
}
