/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:23:19 by mac               #+#    #+#             */
/*   Updated: 2024/11/25 19:47:17 by vconesa-         ###   ########.fr       */
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

static int	set_env_variable(t_context *context, char *name, char *value)
{
	if (ft_setenv(name, value, context) != 0)
	{
		perror("Error: failed to set environment variable");
		return (1);
	}
	return (0);
}

void	print_sorted_env(t_context *context)
{
	char	**env_copy;
	int		count;
	int		i;
	char	*equal_sign;

	env_copy = copy_environ(&count, context);
	ft_qsort(env_copy, count, sizeof(char *), compare_strings);
	i = 0;
	while (i < count)
	{
		equal_sign = ft_strchr(env_copy[i], '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			printf("declare -x %s=\"%s\"\n", env_copy[i], equal_sign + 1);
			*equal_sign = '=';
		}
		else
			printf("declare -x %s\n", env_copy[i]);
		i++;
	}
	free(env_copy);
}

int	vash_export(char **args, t_context *context)
{
	char	*equal_sign;
	char	*name;
	char	*value;

	if (args[1] == NULL || only_spaces(args[1]))
	{
		print_sorted_env(context);
		return (0);
	}
	if (validate_input(args[1]))
		return (1);
	equal_sign = ft_strchr(args[1], '=');
	if (equal_sign == NULL)
		return (set_env_variable(context, args[1], NULL));
	else
	{
		*equal_sign = '\0';
		name = args[1];
		value = equal_sign + 1;
		return (set_env_variable(context, name, value));
	}
}
