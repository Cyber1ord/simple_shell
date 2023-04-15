#include "rj-headers.h"

/**
 * cd - changes to the directory given by the user or the parent directory
 *
 * @info: data relevant (environ)
 *
 * Return: no return
 */
void cd(info_t *info)
{
	char pwd[PATH_MAX], *dir, *cp_pwd;
	int res;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, info);

	dir = info->args[1];
	if (!dir || dir[0] == '\0')
		dir = _getenv("HOME", info->_environ);

	if (!dir || dir[0] == '\0')
	{
		info->status = 1;
		return;
	}

	if (dir[0] == '-')
	{
		char *oldpwd = _getenv("OLDPWD", info->_environ);
		if (!oldpwd)
			info->status = 1;
			return;
		}
		dir = oldpwd;
	}

	res = chdir(dir);
	if (res == -1)
	{
		get_error(info, 2);
		info->status = 1;
		return;
	}

	getcwd(pwd, sizeof(pwd));
	set_env("PWD", pwd, info);
	info->status = 0;
	free(cp_pwd);
}

