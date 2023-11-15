#include "shell.h"

int shellcustom_env(char **args, char __attribute__((__unused__)) **front);
int shellcustom_setenv(char **args, char __attribute__((__unused__)) **front);
int shellcustom_unsetenv(char **args, char __attribute__((__unused__)) **front);

/**
 * shellcustom_env - Prints the current environment.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *	   Otherwise - 0.
 *
 * Description: Prints one variable per line in the
 *              format 'variable'='value'.
 */
int shellcustom_env(char **args, char __attribute__((__unused__)) **front)
{
	int index;
	char nc = '\n';

	if (!enviro_)
		return (-1);

	for (index = 0; enviro_[index]; index++)
	{
		write(STDOUT_FILENO, enviro_[index], _strlen(enviro_[index]));
		write(STDOUT_FILENO, &nc, 1);
	}

	(void)args;
	return (0);
}

/**
 * shellcustom_setenv - Changes or adds an environmental variable to the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the name of the new or existing PATH variable.
 *              args[2] is the value to set the new or changed variable to.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shellcustom_setenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var = NULL, **new_enviro_, *new_value;
	size_t size;
	int index;

	if (!args[0] || !args[1])
		return (create_error(args, -1));

	new_value = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_value)
		return (create_error(args, -1));
	_strcpy(new_value, args[0]);
	_strcat(new_value, "=");
	_strcat(new_value, args[1]);

	env_var = _findenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (size = 0; enviro_[size]; size++)
		;

	new_enviro_ = malloc(sizeof(char *) * (size + 2));
	if (!new_enviro_)
	{
		free(new_value);
		return (create_error(args, -1));
	}

	for (index = 0; enviro_[index]; index++)
		new_enviro_[index] = enviro_[index];

	free(enviro_);
	enviro_ = new_enviro_;
	enviro_[index] = new_value;
	enviro_[index + 1] = NULL;

	return (0);
}

/**
 * shellcustom_unsetenv - Deletes an environmental variable from the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the PATH variable to remove.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shellcustom_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var, **new_enviro_;
	size_t size;
	int index, index2;

	if (!args[0])
		return (create_error(args, -1));
	env_var = _findenv(args[0]);
	if (!env_var)
		return (0);

	for (size = 0; enviro_[size]; size++)
		;

	new_enviro_ = malloc(sizeof(char *) * size);
	if (!new_enviro_)
		return (create_error(args, -1));

	for (index = 0, index2 = 0; enviro_[index]; index++)
	{
		if (*env_var == enviro_[index])
		{
			free(*env_var);
			continue;
		}
		new_enviro_[index2] = enviro_[index];
		index2++;
	}
	free(enviro_);
	enviro_ = new_enviro_;
	enviro_[size - 1] = NULL;

	return (0);
}
