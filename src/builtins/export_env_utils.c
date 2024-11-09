/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:04:54 by vconesa-          #+#    #+#             */
/*   Updated: 2024/11/09 20:00:22 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
