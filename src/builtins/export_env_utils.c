/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:04:54 by vconesa-          #+#    #+#             */
/*   Updated: 2024/11/25 19:55:34 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**expand_environ(int *count, t_context *context)
{
	int		i;
	char	**new_environ;

	*count = 0;
	while (context->env[(*count)] != NULL)
		(*count)++;
	new_environ = safe_malloc(((*count) + 2) * sizeof(char *));
	i = 0;
	while (context->env[i])
	{
		new_environ[i] = ft_strdup(context->env[i]);
		i++;
	}
	new_environ[i] = NULL;
	return (new_environ);
}

char	**copy_environ(int *count, t_context *context)
{
	int		i;
	char	**env_copy;

	i = 0;
	*count = 0;
	while (context->env[*count] != NULL)
		(*count)++;
	env_copy = safe_malloc((*count + 1) * sizeof(char *));
	while (i < *count)
	{
		env_copy[i] = context->env[i];
		i++;
	}
	env_copy[*count] = NULL;
	return (env_copy);
}

static int	edit_variable(char *name, char *new_var, t_context *context)
{
	int	i;

	i = 0;
	while (context->env[i] != NULL)
	{
		if (ft_strncmp(context->env[i], name, ft_strlen(name)) == 0
			&& (context->env[i][ft_strlen(name)] == '='
			|| !context->env[i][ft_strlen(name)]))
		{
			free(context->env[i]);
			context->env[i] = ft_strdup(new_var);
			if (!context->env[i])
			{
				perror("Error duplicating string");
				return (0);
			}
			return (1);
		}
		i++;
	}
	return (0);
}

static char	*set_new_var(char *name, char *value)
{
	char	*new_var;
	size_t	len;

	if (value == NULL)
		len = ft_strlen(name) + 1;
	else
		len = ft_strlen(name) + ft_strlen(value) + 2;
	new_var = safe_malloc((sizeof(char) * len));
	ft_strlcpy(new_var, name, ft_strlen(name) + 1);
	if (value != NULL)
	{
		ft_strlcat(new_var, "=", ft_strlen(new_var) + 2);
		ft_strlcat(new_var, value, len);
	}
	return (new_var);
}

int	ft_setenv(char *name, char *value, t_context *context)
{
	char	**new_environ;
	int		count;
	char	*new_var;

	new_var = set_new_var(name, value);
	if (edit_variable(name, new_var, context))
	{
		free(new_var);
		return (0);
	}
	new_environ = expand_environ(&count, context);
	new_environ[count] = new_var;
	new_environ[count + 1] = NULL;
	free_env(context);
	context->env = new_environ;
	return (0);
}
