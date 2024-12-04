/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:00:52 by mac               #+#    #+#             */
/*   Updated: 2024/12/04 10:05:52 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_getenv(const char *name, char **env)
{
	size_t	len;
	int		i;

	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (&env[i][len + 1]);
		i++;
	}
	return (NULL);
}

void	handle_env_var(char *arg, char *old_str, int *j, t_context *context)
{
	char	*env_var_name;
	char	*env_var_value;

	env_var_name = arg + 1;
	env_var_value = ft_getenv(env_var_name, context->env);
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

void	handle_d_quoted_env(char *arg, char *old_str, int *j, t_context *cont)
{
	char	*env_var_value;
	char	*env_var_name;

	env_var_name = arg + 2;
	env_var_name[strlen(env_var_name) - 1] = '\0';
	env_var_value = ft_getenv(env_var_name, cont->env);
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

void	handle_s_quoted_env(char *arg, char *old_str, int *j, t_context *cont)
{
	char	*env_var_value;
	char	*env_var_name;

	env_var_name = arg + 3;
	env_var_name[strlen(env_var_name) - 2] = '\0';
	env_var_value = ft_getenv(env_var_name, cont->env);
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
