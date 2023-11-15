#include "shell.h"

char **_copyenv(void);
void free_env(void);
char **_findenv(const char *var);

/**
 * _copyenv - Creates a copy of the environment.
 *
 * Return: If an error occurs - NULL.
 *         O/w - a double pointer to the new copy.
 */
char **_copyenv(void)
{
	char **new_enviro_;
	size_t size;
	int index;

	for (size = 0; enviro_[size]; size++)
		;

	new_enviro_ = malloc(sizeof(char *) * (size + 1));
	if (!new_enviro_)
		return (NULL);

	for (index = 0; enviro_[index]; index++)
	{
		new_enviro_[index] = malloc(_strlen(enviro_[index]) + 1);

		if (!new_enviro_[index])
		{
			for (index--; index >= 0; index--)
				free(new_enviro_[index]);
			free(new_enviro_);
			return (NULL);
		}
		_strcpy(new_enviro_[index], enviro_[index]);
	}
	new_enviro_[index] = NULL;

	return (new_enviro_);
}

/**
 * free_env - Frees the the environment copy.
 */
void free_env(void)
{
	int index;

	for (index = 0; enviro_[index]; index++)
		free(enviro_[index]);
	free(enviro_);
}

/**
 * _findenv - Gets an environmental variable from the PATH.
 * @var: The name of the environmental variable to get.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char **_findenv(const char *var)
{
	int index, len;

	len = _strlen(var);
	for (index = 0; enviro_[index]; index++)
	{
		if (_strncmp(var, enviro_[index], len) == 0)
			return (&enviro_[index]);
	}

	return (NULL);
}

