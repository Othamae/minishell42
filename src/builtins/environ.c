/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:16:09 by mac               #+#    #+#             */
/*   Updated: 2024/11/25 19:24:03 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	vash_env(t_context *context)
{
	char	**env;

	env = context->env;
	while (*env)
	{
		if (ft_strchr(*env, '='))
			printf("%s\n", *env);
		env++;
	}
	return (0);
}

static void	remove_env_var(t_context *context, char *arg)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = ft_strlen(arg);
	while (context->env[i])
	{
		if (ft_strncmp(context->env[i], arg, len) == 0
			&& (context->env[i][len] == '=' || !context->env[i][len]))
		{
			free(context->env[i]);
			j = i;
			while (context->env[j])
			{
				context->env[j] = context->env[j + 1];
				j++;
			}
			break ;
		}
		i++;
	}
}

int	vash_unset(char **args, t_context *context)
{
	int			k;

	k = 1;
	if (args[1] == NULL)
	{
		printf("Error: expected argument to unset\n");
		return (1);
	}
	while (args[k] != NULL)
	{
		remove_env_var(context, args[k]);
		k++;
	}
	return (0);
}
