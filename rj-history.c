#include "rj-headers.h"

#define MAX_HISTORY 100

static char history[MAX_HISTORY][BUFSIZ];
static int history_count;

static void add_to_history(info_t *info)
{
	if (history_count >= MAX_HISTORY)
	{
		/* Shift all history entries up by one */
		for (int i = 1; i < MAX_HISTORY; i++)
		{
			strcpy(history[i - 1], history[i]);
		
		history_count = MAX_HISTORY - 1;
	}

	strcpy(history[history_count], cmd);
	history_count++;
}

int  *get_command_from_history(info_t *info)
{
	if (info < 1 || info > history_count)
	{
		return (NULL);
	}

	return (history[info - 1]);
}

static info_t *process_input(info_t *info)
{
	/* Process the command */
	char *cmd = input;
	static char *get_command_from_history(int info)
	char *arg = NULL;
	char *result = NULL;

	/* Check if input is a history command */
	if (cmd[0] == '!')
	{
		result = get_command_from_history(cmd);
		if (result == NULL)
		{
			printf("Command not found in history.\n");
			return (0);
		}
		else
		{
			strcpy(input, result);
			cmd = input;
		}
	}

	/* Split input into command and argument */
	arg = strchr(input, ' ');
	if (arg != NULL)
	{
		*arg = '\0';
		arg++;
	}

	/* Add the command to history */
	add_to_history(info->cmd);
	if (strcmp(cmd, "print") == 0)
	{
		print_info(info);
	}
	else if (strcmp(cmd, "set") == 0)
	{
		set_info(info, arg);
	}
	else if (strcmp(cmd, "help") == 0)
	{
		printf("Available commands:\n");
		printf("print - print information\n");
		printf("set <name> <value> - set information\n");
		printf("help - show available commands\n");
		printf("!n - recall nth command from history\n");
	}
	else
	{
		printf("Unknown command: %s\n", cmd);
	}

	return (info);
}

static void print_history(void)
{
	for (int i = 0; i < history_count; i++)
	{
		printf("%d: %s\n", i + 1, history[i]);
	}
}


