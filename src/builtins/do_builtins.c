/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:24:34 by mac               #+#    #+#             */
/*   Updated: 2024/11/09 14:05:17 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_builtins(char **args)
{
	if (ft_strncmp(args[0], "cd", 3) == 0)
		vash_cd(args);
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(args[0], "env", 4) == 0)
		vash_env();
	else if (ft_strncmp(args[0], "export", 7) == 0)
		vash_export(args);
	else if (ft_strncmp(args[0], "setenv", 7) == 0)
		vash_env();
	else if ((ft_strncmp(args[0], "unset", 6) == 0)
		|| (ft_strncmp(args[0], "unsetenv", 9) == 0))
		vash_unset(args);
	else
		return (0);
	return (1);
}

int	free_line(char *line, int value)
{
	free(line);
	return (value);
}

int	do_builtins(char *buff)
{
	int		i;
	char	*token;
	char	*args[64];
	char	*line;

	line = ft_strdup(buff);
	i = 0;
	token = ft_strtok(line, " ");
	while (token != NULL)
	{
		args[i++] = token;
		token = ft_strtok(NULL, " ");
	}
	args[i] = NULL;
	if (args[0] == NULL)
		return (free_line(line, 0));
	if (ft_strncmp(args[0], "exit", 5) == 0)
	{
		free(line);
		exit(0);
	}
	if (check_builtins(args))
		return (free_line(line, 1));
	return (free_line(line, 0));
}

// *********************
// old do builtins incase something breaks

// int do_builtins(char *buff)
// {
// 	int i;
// 	char *token;
// 	char *args[64];
// 	char *line;

// 	line = ft_strdup(buff);
// 	i = 0;
// 	token = ft_strtok(line, " ");
// 	while (token != NULL)
// 	{
// 		args[i++] = token;
// 		token = ft_strtok(NULL, " ");
// 	}
// 	args[i] = NULL;
// 	if (args[0] == NULL)
// 	{
// 		free(line);
// 		return (0);
// 	}
// 	if (ft_strncmp(args[0], "exit", 5) == 0)
// 	{
// 		free(line);
// 		exit(0);
// 	}
// 	if (ft_strncmp(args[0], "cd", 3) == 0)
// 	 	vash_cd(args);
// 	else if (ft_strncmp(args[0], "pwd",4) == 0)
// 		ft_pwd();
// 	else if (ft_strncmp(args[0], "env",4) == 0)
// 		vash_env();
// 	else if ((ft_strncmp(args[0], "export",7) == 0)
		//|| ft_strncmp(args[0], "setenv",7) == 0)
// 	{
// 		if (args[1] == NULL && (ft_strncmp(args[0], "setenv",7) != 0))
// 			vash_env();
// 		else
// 			vash_export(args);
// 	}
// 	else if ((ft_strncmp(args[0], "unset",6) == 0)
		//|| (ft_strncmp(args[0], "unsetenv", 9) == 0))
// 		vash_unset(args);
// 	else
// 	{
// 		free(line);
// 		return (0);
// 	}
// 	free(line);
// 	return (1);
// }
