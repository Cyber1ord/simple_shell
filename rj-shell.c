#include "rj-headers.h"

/**
 *main - Simple shell project by Raphael and Joseph
 *
 *
 *Return:  return 0 (success)
 */

int main(void)
{

	char *pathbuffer = NULL;
	char *copy = NULL;
	char *buffer = NULL;
	char *PATH = NULL;
	char **argv;
	int exitstatus = 0;

	/* init_shell(); */
	signal(SIGINT, SIG_IGN);
	PATH = _getenv("PATH");
	if (PATH == NULL)
		return (EXIT_FAILURE);
	while (1)
	{
		argv = NULL;
		prompt();
		buffer = _read();
		if (*buffer != '\0')
		{
			argv = _strtoken(buffer);
			if (argv == NULL)
			{
				free(buffer);
				continue;
			}
			pathbuffer = _pathbuffer(argv, PATH, copy);
			if (checkbuiltins(argv, buffer, exitstatus) == 1)
				continue;
			exitstatus = _forkprocess(argv, buffer, pathbuffer);
		}
		else
			free(buffer);
	}

	return (EXIT_SUCCESS);
}
