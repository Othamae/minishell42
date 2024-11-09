/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:23:19 by mac               #+#    #+#             */
/*   Updated: 2024/11/09 13:00:16 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	validate_input(char *arg)
{
	if (ft_strstr(arg, "==") != NULL)
	{
		printf("Error: invalid format, '==' found\n");
		return (1);
	}
	if (count_char(arg, '\'') > 2 || count_char(arg, '"') > 2)
	{
		printf("Error: invalid format, quotes appear too many times\n");
		return (1);
	}
	return (0);
}

static int	update_existing_env_var(char **environ, char *name)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], name, strlen(name)) == 0
			&& environ[i][strlen(name)] == '=')
		{
			environ[i] = malloc(strlen(name) + 1);
			if (!environ[i])
			{
				perror("Error: memory allocation failed");
				return (1);
			}
			strcpy(environ[i], name);
			return (0);
		}
		i++;
	}
	return (-1);
}

static int	add_new_env_var(char **environ, char *name)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
	{
		i++;
	}
	environ[i] = malloc(strlen(name) + 1);
	if (!environ[i])
	{
		perror("Error: memory allocation failed");
		return (1);
	}
	strcpy(environ[i], name);
	environ[i + 1] = NULL;
	return (0);
}

static int	set_environment_variable(char **environ, char *name, char *value)
{
	if (value == NULL)
	{
		if (update_existing_env_var(environ, name) == 0)
		{
			return (0);
		}
		return (add_new_env_var(environ, name));
	}
	else
	{
		if (setenv(name, value, 1) != 0)
		{
			perror("Error: failed to set environment variable");
			return (1);
		}
	}
	return (0);
}

int	vash_export(char **args)
{
	char		*equal_sign;
	char		*name;
	char		*value;
	extern char	**environ;

	if (args[1] == NULL)
		vash_env();
	if (validate_input(args[1]))
		return (1);
	equal_sign = ft_strchr(args[1], '=');
	if (equal_sign == NULL)
	{
		return (set_environment_variable(environ, args[1], "''"));
	}
	else
	{
		*equal_sign = '\0';
		name = args[1];
		value = equal_sign + 1;
		return (set_environment_variable(environ, name, value));
	}
}

// int vash_export(char **args)
// {
// 	extern char **environ;
// 	int i = 0;
// 	char *new_exp;
// 	char *equal_sign;
// 	char *value_part;
// 	int len = ft_strlen(args[1]);

// 	if (ft_strstr(args[1], "==") != NULL)
// 	{
// 		printf("Error: invalid format, '==' found\n");
// 		return 1;
// 	}
// 	if (count_char(args[1], '\'') > 2 || count_char(args[1], '"') > 2)
// 	{
// 		printf("Error: invalid format, quotes appear too many times\n");
// 		return 1;
// 	}
// 	equal_sign = strchr(args[1], '=');

// 	if (equal_sign == NULL)
// 	{
// 		new_exp = malloc(len + 1);
// 		if (!new_exp)
// 		{
// 			perror("Error: memory allocation failed");
// 			return 1;
// 		}
// 		strcpy(new_exp, args[1]);

// 		while (environ[i] != NULL)
// 		{
// 			if (ft_strncmp(environ[i], new_exp, len) == 0
// 			&& environ[i][len] == '\0')
// 			{
// 				return 0;
// 			}
// 			i++;
// 		}

// 		environ[i] = new_exp;
// 		environ[i + 1] = NULL;

// 		return 0;
// 	}
// 	new_exp = malloc(len + 1);
// 	if (!new_exp)
// 	{
// 		perror("Error: memory allocation failed");
// 		return 1;
// 	}
// 	value_part = equal_sign + 1;
// 	if ((*value_part == '\'' && value_part[ft_strlen(value_part) - 1] == '\'')
// 			|| (*value_part == '"'
// 			&& value_part[ft_strlen(value_part) - 1] == '"'))
// 	{
// 		value_part[ft_strlen(value_part) - 1] = '\0';
// 		value_part++;
// 	}
// 	strncpy(new_exp, args[1], equal_sign - args[1] + 1);
// 	strcpy(new_exp + (equal_sign - args[1] + 1), value_part);
// 	while (environ[i] != NULL)
// 	{
// 		if (strncmp(environ[i], new_exp, equal_sign - args[1]) == 0)
// 		{
// 			environ[i] = new_exp;
// 			return 0;
// 		}
// 		i++;
// 	}
// 	environ[i] = new_exp;
// 	environ[i + 1] = NULL;
// 	return 0;
// }
