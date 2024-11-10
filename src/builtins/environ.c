/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:16:09 by mac               #+#    #+#             */
/*   Updated: 2024/11/10 15:08:19 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	vash_env(void)
{
	extern char	**environ;
	char		**env;

	env = environ;
	while (*env)
	{
		if (ft_strchr(*env, '='))
			printf("%s\n", *env);
		env++;
	}
	return (0);
}

static void	remove_env_var(char **environ, char *arg)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = ft_strlen(arg);
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], arg, len) == 0
			&& (environ[i][len] == '=' || !environ[i][len]))
		{
			j = i;
			while (environ[j] != NULL)
			{
				environ[j] = environ[j + 1];
				j++;
			}
			break ;
		}
		i++;
	}
}

int	vash_unset(char **args)
{
	extern char	**environ;
	int			k;

	k = 1;
	if (args[1] == NULL)
	{
		printf("Error: expected argument to unset\n");
		return (1);
	}
	while (args[k] != NULL)
	{
		remove_env_var(environ, args[k]);
		k++;
	}
	return (0);
}

// int vash_unset(char **args)
// {
// 	extern char **environ;
// 	int i;
// 	int j;
// 	int k;
// 	int len;

// 	if (args[1] == NULL)
// 	{
// 		printf("Error: expected argument to unset\n");
// 		return 1;
// 	}
// 	k = 1;
// 	while (args[k] != NULL)
// 	{
// 		i = 0;
// 		len = ft_strlen(args[k]);
// 		while (environ[i] != NULL)
// 		{
// 			if (ft_strncmp(environ[i], args[k],
				//len) == 0 && environ[i][len] == '=')
// 			{
// 				j = i;
// 				while (environ[j] != NULL)
// 				{
// 					environ[j] = environ[j + 1];
// 					j++;
// 				}
// 				break;
// 			}
// 			i++;
// 		}
// 		k++;
// 	}
// 	return 0;
// }
