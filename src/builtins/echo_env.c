/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:00:52 by mac               #+#    #+#             */
/*   Updated: 2024/11/09 12:20:22 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_env_var(char *arg, char *old_str, int *j)
{
	char	*env_var_name;
	char	*env_var_value;

	env_var_name = arg + 1;
	env_var_value = getenv(env_var_name);
	if (env_var_value)
	{
		while (*env_var_value != '\0')
			old_str[(*j)++] = *(env_var_value++);
	}
	else
	{
		while (*arg != '\0')
			old_str[(*j)++] = *(arg++);
	}
}

void	handle_double_quoted_env_var(char *arg, char *old_str, int *j)
{
	char	*env_var_value;
	char	*env_var_name;

	env_var_name = arg + 2;
	env_var_name[strlen(env_var_name) - 1] = '\0';
	env_var_value = getenv(env_var_name);
	if (env_var_value)
	{
		while (*env_var_value != '\0')
			old_str[(*j)++] = *(env_var_value++);
	}
	else
	{
		old_str[(*j)++] = '"';
		while (*arg != '\0')
			old_str[(*j)++] = *(arg++);
		old_str[(*j)++] = '"';
	}
}

void	handle_single_quoted_env_var(char *arg, char *old_str, int *j)
{
	char	*env_var_value;
	char	*env_var_name;

	env_var_name = arg + 3;
	env_var_name[strlen(env_var_name) - 2] = '\0';
	env_var_value = getenv(env_var_name);
	if (env_var_value)
	{
		while (*env_var_value != '\0')
			old_str[(*j)++] = *(env_var_value++);
		old_str[*j] = '\0';
		write(1, "'", 1);
		write(1, old_str, ft_strlen(old_str));
		write(1, "'\n", 2);
		exit(0);
	}
	else
	{
		old_str[(*j)++] = '"';
		while (*arg != '\0')
			old_str[(*j)++] = *(arg++);
		old_str[(*j)++] = '"';
	}
}
