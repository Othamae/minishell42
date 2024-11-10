/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:04:54 by vconesa-          #+#    #+#             */
/*   Updated: 2024/11/10 15:07:54 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**expand_environ(char **environ, int size, int *count)
{
	int		i;
	char	**env_copy;

	*count = 0;
	while (environ[(*count)] != NULL)
		(*count)++;
	env_copy = malloc(((*count) + size + 1) * sizeof(char *));
	if (!env_copy)
		return (NULL);
	i = 0;
	while (i < (*count))
	{
		env_copy[i] = environ[i];
		i++;
	}
	while (i < ((*count) + size))
	{
		env_copy[i] = NULL;
		i++;
	}
	env_copy[(*count) + size] = NULL;
	return (env_copy);
}

char	**copy_environ(char **environ, int *count)
{
	int		i;
	char	**env_copy;

	i = 0;
	*count = 0;
	while (environ[*count] != NULL)
		(*count)++;
	env_copy = malloc((*count + 1) * sizeof(char *));
	if (!env_copy)
		return (NULL);
	while (i < *count)
	{
		env_copy[i] = environ[i];
		i++;
	}
	env_copy[*count] = NULL;
	return (env_copy);
}

void	print_sorted_env(char **environ)
{
	char	**env_copy;
	int		count;
	int		i;
	char	*equal_sign;

	env_copy = copy_environ(environ, &count);
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

int	edit_variable(char *name, char *new_var, char ***env_copy)
{
	int	i;

	i = 0;
	while ((*env_copy)[i] != NULL)
	{
		if (ft_strncmp((*env_copy)[i], name, ft_strlen(name)) == 0 &&
			((*env_copy)[i][ft_strlen(name)] == '='
				|| !(*env_copy)[i][ft_strlen(name)]))
		{
			free((*env_copy)[i]);
			(*env_copy)[i] = new_var;
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_setenv(char *name, char *value, char ***environ)
{
	char	**env_copy;
	size_t	len;
	int		count;
	char	*new_var;

	len = ft_strlen(name) + ft_strlen(value) + 2;
	env_copy = expand_environ(*environ, len, &count);
	new_var = (char *)malloc((sizeof(char) * len));
	if (!new_var)
		return (1);
	ft_strlcpy(new_var, name, ft_strlen(name) + 1);
	ft_strlcat(new_var, "=", ft_strlen(new_var) + 2);
	ft_strlcat(new_var, value, len);
	if (edit_variable(name, new_var, &env_copy))
	{
		free(*environ);
		*environ = env_copy;
		return (0);
	}
	env_copy[count] = new_var;
	env_copy[count + 1] = NULL;
	free(*environ);
	*environ = env_copy;
	return (0);
}
